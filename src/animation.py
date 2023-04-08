import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

if __name__ == "__main__":
    # read data with pandas and convert it to a numpy array
    count_particles = 40
    df = pd.read_csv(r'/home/marco/Projekte/ParticleSwarmOptimization/data/output.csv', sep=";", header=None)
    coordinate_array = df.to_numpy()
    length = int((coordinate_array.shape[0]+1)/count_particles)

    # create a scatter plot for the  function to visualize the particle swarm optimization process
    fig, ax = plt.subplots()
    x = np.arange(-10.0, 10.0, 0.1)
    y = np.arange(-10.0, 10.0, 0.1)
    x_function, y_function = np.meshgrid(x, y)
    f_function =  np.power(x_function - 2.0, 2.0) + np.power(y_function + 4.0, 2.0)

    def animate(i):
        '''
        Animation function
        '''
        ax.clear()
        ax.scatter(x_function, y_function, f_function, c=f_function, alpha=0.1)
        start = count_particles*i
        end = count_particles*i + count_particles
        current_coordinate_array = coordinate_array[start:end, :]
        x = current_coordinate_array[:, 0]
        y = current_coordinate_array[:, 1]
        u = current_coordinate_array[:, 3]
        v = current_coordinate_array[:, 4]
        ax.scatter(x,y, s=4.0, marker='o',alpha=0.7,color='red')
        ax.quiver(x, y, u, v, color='g', width=0.004, alpha=0.5)

    # Start the writing process for the gif
    writergif = animation.PillowWriter(fps=2.0) 
    anim = animation.FuncAnimation(fig, animate, frames=length)
    anim.save("particle_swarm.gif", writer=writergif)
