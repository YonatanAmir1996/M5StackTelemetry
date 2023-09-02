import os
import sys
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

from CLI.M5Telemetry import M5Telemetry

if __name__ == '__main__':
    M5Telemetry(plot_amg=True).plot_amg(plot_delay_in_seconds=0.01, min_temprature_show=10, max_temprature_show=40)
