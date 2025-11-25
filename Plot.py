import matplotlib.pyplot as plt
import numpy as np

# -----------------------------
# Experimental Data
# -----------------------------
activities = np.array([1000, 2000, 4000, 6000, 8000, 10000, 20000, 40000, 60000, 100000])
measured_time = np.array([0.00004364, 0.00008881, 0.00023091, 0.00029668, 0.00041843,
                          0.00054577, 0.00121161, 0.00225800, 0.00344359, 0.00658249])

# -----------------------------
# Expected O(n log n) Runtime
# -----------------------------
expected_time = (activities * np.log2(activities)) / (activities[-1] * np.log2(activities[-1]))
expected_time *= measured_time[-1]  # Scale to match final measured value

# -----------------------------
# Plotting
# -----------------------------
plt.figure(figsize=(9, 6))
plt.plot(activities, measured_time, 'bo-', label='Measured Activity Selection (Greedy)')
plt.plot(activities, expected_time, 'r--', label='Expected O(n log n)')

plt.title('Activity Selection Problem: Measured vs Expected Runtime')
plt.xlabel('Number of Activities (n)')
plt.ylabel('Average Runtime (seconds)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
