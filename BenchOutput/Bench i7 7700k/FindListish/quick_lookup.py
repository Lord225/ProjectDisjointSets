import pandas as pd
import glob
import os
import matplotlib.pyplot as plt

path = ""
csv_files = glob.glob(os.path.join(path, "*.csv"))

frames = dict()

for file in csv_files:
    name, _ = os.path.splitext(os.path.basename(file))

    frames[name] = pd.read_csv(file).sort_values("X")

for name, frame in frames.items():
    plt.plot(frame["X"], frame["Y"], label=name)
plt.legend()
plt.grid()
plt.show()