import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

FILEPATH = "/home/lygram/Documents/Uni/Proj/M5StackTelemetry/testSamples"
data = np.load(f"{FILEPATH}/AMG/amg_results.pkl",
               allow_pickle=True)

avgData = [np.mean(data[i, :, :]) for i in range(len(data))]
plt.figure(figsize=[18, 18])
plt.plot(avgData)
plt.title("AVG Test, mean result of all pixels.")
plt.ylabel("Sensor return value")
plt.xlabel("time")
plt.savefig(f"{FILEPATH}/amg_avg.png")
plt.close()
avgData_dt = [avgData[i+1] - avgData[i] for i in range(len(avgData) -1)]
plt.title("AMG average defferential data, indicative of sample rate")
plt.ylabel("Sensor return value / time")
plt.xlabel("time")
plt.plot(avgData_dt)
plt.savefig(f"{FILEPATH}/amg_avg_df_dt.png")
plt.close()

fig, ax = plt.subplots(8, 8, figsize=[28,18])
fig.suptitle("AMG graphs for each pixel")
fig.tight_layout()
for i in range(8):
    for j in range(8):
        ax[j][i].plot(data[:, i, j])
fig.savefig(f"{FILEPATH}/amg_pix.png")
plt.close(fig)

data = np.load(f"{FILEPATH}/ToF/latest/pkl_walk_2m_test2.pkl",
               allow_pickle=True)
data2 = np.load(f"{FILEPATH}/ToF/latest/pkl_close_far_hand.pkl",\
                allow_pickle=True)

avgData = [np.mean(data[i, :, :]) for i in range(len(data))]
plt.plot(avgData)
plt.title("TOF test, mean result of all pixels in walk test")
plt.ylabel("Sensor return value")
plt.xlabel("time")
plt.savefig(f"{FILEPATH}/tof_avg.png")
plt.close()

fig, ax = plt.subplots(8, 8, figsize=[28,18])
fig.suptitle("TOF graphs for each pixel, walk test")
fig.tight_layout()
for i in range(8):
    for j in range(8):
        ax[j][i].plot(data[:, i, j])
        ax[j][i].set_ylim(0, 2000)
fig.savefig(f"{FILEPATH}/tof_pix.png")
plt.close(fig)

avgData = [np.mean(data2[i, :, :]) for i in range(len(data2))]
plt.plot(avgData)
plt.title("TOF test, mean result of all pixels in hand test")
plt.ylabel("Sensor return value")
plt.xlabel("time")
plt.savefig(f"{FILEPATH}/tof_hand_avg.png")
avgData_dt = [avgData[i+1] - avgData[i] for i in range(len(avgData) -1)]
plt.close()
plt.title("TOF average defferential data, indicative of sample rate")
plt.ylabel("Sensor return value / time")
plt.xlabel("time")
plt.plot(avgData_dt)
plt.savefig(f"{FILEPATH}/tof_hand_avg_df_dt.png")
plt.close()

fig, ax = plt.subplots(8, 8, figsize=[28,18])
fig.suptitle("TOF graphs for each pixel, hand test")
fig.tight_layout()
for i in range(8):
    for j in range(8):
        ax[j][i].plot(data2[:, i, j])
        #ax[j][i].set_ylim(0, 2000)
fig.savefig(f"{FILEPATH}/tof_hand_pix.png")
plt.close(fig)

files_imu = os.listdir(f"{FILEPATH}/IMU")

for filename in files_imu:
    data = np.load(f"{FILEPATH}/IMU/{filename}",
                   allow_pickle=True)
    plt.plot(data)
    plt.title(f"Test name: {filename}")
    plt.xlabel("time")
    plt.ylabel("Sensor return value")
    plt.savefig(f"{FILEPATH}/{filename}_test.png")
    plt.close()
    
for filename in files_imu:
    data = np.load(f"{FILEPATH}/IMU/{filename}",
                   allow_pickle=True)
    fig, ax = plt.subplots(3, 1, figsize=[28, 18])
    for i in range(3):
        ax[i].plot(data[:,i])
    fig.suptitle(f"Test name: {filename}")
    filename = filename[:-4]
    fig.savefig(f"{FILEPATH}/{filename}_test_sepaxis.png")
    plt.close(fig)