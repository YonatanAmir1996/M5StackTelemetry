import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import RectBivariateSpline

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

from CLI.M5Telemetry import M5Telemetry

if __name__ == '__main__':
    M5Telemetry(plot_amg=True).plot_amg(0.05)
