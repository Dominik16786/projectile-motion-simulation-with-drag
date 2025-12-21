import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.cm import get_cmap
import glob

def read_trajectory_file(filename):
    t, x, y = [], [], []
    with open(filename, 'r') as f:
        for line in f:
            if line.startswith('#') or not line.strip():
                continue
            vals = line.split()
            t.append(float(vals[0]))
            x.append(float(vals[1]))
            y.append(float(vals[2]))
    return np.array(t), np.array(x), np.array(y)

files = sorted(glob.glob("trajectory_theta_*.txt"))
trajectories = [read_trajectory_file(f) for f in files]
colors = get_cmap("viridis")(np.linspace(0,1,len(trajectories)))

final_x = [x[-1] for _, x, _ in trajectories]
fairest_index = np.argmax(final_x)

fig, ax = plt.subplots(figsize=(10,6))
xmax = max(final_x)*1.1
ymax = max([np.max(y) for _, _, y in trajectories])*1.2
ax.set_xlim(0, xmax)
ax.set_ylim(0, ymax)
ax.set_xlabel("x (m)")
ax.set_ylabel("y (m)")
ax.set_title("Projectile Trajectories with Fairest Highlighted")
ax.grid(True, linestyle='--', alpha=0.5)

lines = []
points = []

for i in range(len(trajectories)):
    if i == fairest_index:
        line, = ax.plot([], [], color='red', lw=3, label="Fairest trajectory")
        point, = ax.plot([], [], 'ro')
    else:
        line, = ax.plot([], [], color=colors[i], lw=1)
        point, = ax.plot([], [], 'o', color=colors[i])
    lines.append(line)
    points.append(point)

def init():
    for line, point in zip(lines, points):
        line.set_data([], [])
        point.set_data([], [])
    return lines + points

def update(frame):
    for i, (t, x, y) in enumerate(trajectories):
        if frame < len(x):
            lines[i].set_data(x[:frame], y[:frame])
            points[i].set_data([x[frame]], [y[frame]])
        else:
            lines[i].set_data(x, y)
            points[i].set_data([x[-1]], [y[-1]])
    return lines + points

max_frames = max([len(x) for _, x, _ in trajectories])
ani = animation.FuncAnimation(fig, update, frames=max_frames, init_func=init,
                              interval=20, blit=True, repeat=False)
plt.legend()
plt.tight_layout()
plt.show()
