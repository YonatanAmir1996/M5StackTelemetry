import os
import sys
import threading
import queue
import numpy as np
from scipy.ndimage import label
import tkinter as tk
from tkinter import font

# Determine the root directory based on the current file's location
# and append it to the system's path list to ensure correct module imports.
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)
from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e


class ToFVisualizer:

    def __init__(self):
        self.threshold_in_mm = 10
        self.min_size = 4
        self.thread_running = True  # Flag to keep track of thread running status

        self.interface = M5Telemetry()
        self.root = tk.Tk()
        self.root.title("ToF GUI")
        self.root.geometry('450x800')
        self.root.configure(bg="#f0f0f0")

        self.output_was_used = False
        self.status_queue = queue.Queue()

        self.setup_gui()

        self.logic_thread = threading.Thread(target=self.logic_loop)
        self.logic_thread.daemon = True
        self.logic_thread.start()

        self.gui_loop()

    def setup_gui(self):
        top_frame = tk.Frame(self.root, bg="#f0f0f0")
        top_frame.pack(pady=20)
        title_label = tk.Label(top_frame, text="ToF presenter", font=("Arial", 18, "bold"), bg="#f0f0f0")
        title_label.pack()
        status_title_label = tk.Label(top_frame, text="Status:", font=("Arial", 12), bg="#f0f0f0")
        status_title_label.pack(pady=20)
        matrix_frame = tk.Frame(self.root)
        matrix_frame.pack(pady=20)
        self.labels = self.create_matrix_labels(matrix_frame, np.zeros((8, 8), dtype=np.uint16))
        self.status_label = tk.Label(self.root, text="", font=("Arial", 12), bg="#f0f0f0")
        self.status_label.pack(pady=20)
        # Bind the shutdown method to the window's close button
        self.root.protocol("WM_DELETE_WINDOW", self.shutdown)

    def create_matrix_labels(self, root, matrix):
        labels = []
        custom_font = font.Font(size=10, weight="bold")
        for i in range(matrix.shape[0]):
            row_labels = []
            for j in range(matrix.shape[1]):
                label = tk.Label(root, text="", font=custom_font, width=5, height=2, relief="solid", borderwidth=1, padx=5,
                                 pady=5)
                label.grid(row=i, column=j, padx=2, pady=2)
                row_labels.append(label)
            labels.append(row_labels)
        return labels

    def color_gradient(self, value, threshold):
        ratio = value / threshold
        blue = min(255, max(0, int(255 * (1 - ratio))))
        red = min(255, max(0, 255 - blue))
        return f"#{red:02x}00{blue:02x}"

    def update_matrix_display(self, labels, matrix, threshold):
        for i in range(matrix.shape[0]):
            for j in range(matrix.shape[1]):
                cell_value = matrix[i, j]
                labels[i][j].config(text=str(cell_value))
                labels[i][j].config(bg=self.color_gradient(cell_value, threshold))

    def sample_tof(self):
        with threading.Lock():
            self.interface.update_values([Device_e.TOF])

    def has_large_connected_area(self, matrix, threshold):
        binary_matrix = np.where(matrix < threshold, 1, 0)
        labeled_matrix, num_features = label(binary_matrix)
        for i in range(1, num_features + 1):
            size = (labeled_matrix == i).sum()
            if size >= self.min_size:
                return True
        return False

    def logic_loop(self):
        while self.thread_running:
            if not self.output_was_used:
                self.sample_tof()
                if self.has_large_connected_area(self.interface.tof.mm_distances, self.threshold_in_mm):
                    self.interface.command_set_motor(50)
                    self.output_was_used = True
            else:
                self.sample_tof()
                if not self.has_large_connected_area(self.interface.tof.mm_distances, self.threshold_in_mm):
                    self.interface.command_set_motor(0)
                    self.output_was_used = False

            status_text = "Output ON" if self.output_was_used else "Output OFF"
            # Clear the queue before putting new data
            while not self.status_queue.empty():
                self.status_queue.get_nowait()

            self.status_queue.put((status_text, np.array(self.interface.tof.mm_distances_avg, dtype=np.uint16)))

    def gui_loop(self):
        self.update_gui()
        self.root.mainloop()

    def update_gui(self):
        try:
            status_text, matrix_data = self.status_queue.get_nowait()
            self.status_label.config(text=status_text)
            self.update_matrix_display(self.labels, matrix_data, self.threshold_in_mm)
        except queue.Empty:
            pass
        self.root.after(100, self.update_gui)

    def shutdown(self):
        """Gracefully shut down the application."""
        self.thread_running = False  # Signal to the thread to stop
        self.logic_thread.join()  # Wait for the thread to finish
        self.root.destroy()  # Close the GUI


if __name__ == '__main__':
    ToFVisualizer()