import subprocess
import matplotlib.pyplot as plt
import numpy as np
import re
from tqdm import tqdm

# Run the C++ program


def run_cpp_program(min_diff):
    result = subprocess.run(
        ["./MergesortMulti", str(min_diff)], stdout=subprocess.PIPE, check=True)
    output = result.stdout.decode('utf-8')
    match = re.search(r'\d+\.\d+', output)  # 匹配浮点数
    return float(match.group(0))


min_diff_log = np.linspace(3, 15, 400)
min_diff_values = np.power(2, min_diff_log)
time = []

for min_diff in tqdm(min_diff_values):
    time.append(run_cpp_program(int(min_diff)))

# Plot the results
plt.plot(min_diff_log, time)
plt.xlabel('Minimum difference')
plt.ylabel('Time (s)')
plt.show()
