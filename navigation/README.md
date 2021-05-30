# Robot Path Planning using Particle Swarm Optimization(PSO).
ROTF uses the robust [PSO Algorithm](https://en.wikipedia.org/wiki/Particle_swarm_optimization) for Autonomous Navigation. 
Our Simulation in [Gazebo Environment](http://gazebosim.org/) makes use of the [Turtlebot](https://www.turtlebot.com/). The bot navigates between two user-defined positions by creating a dynamic map of the environment using the on-board LiDAR, thereby avoiding obstacles along it's path.

Here's the brief System Architecture of the same:
<p align="center">
<img src="https://github.com/theobscuredev/rotf-software/blob/main/navigation/assets/overview.PNG">
</p>

MATLAB scripts are used to control the bot, which sends the occupancy grid matrix to the PSO Algorithm, thereby guiding the bot ahead. Detailed flowchart of this system is as follows:
<p align="center">
<img src="https://github.com/theobscuredev/rotf-software/blob/main/navigation/assets/system_overview.png">
</p>

[Explanation of the PSO Algorithm](https://github.com/theobscuredev/rotf-software/blob/main/navigation/pso/README.md).

Video Demonstrations:
[Mapping](https://drive.google.com/file/d/1SO8MXUNIVMJc8czz6t7-7wbhuiYi155K/view?usp=sharing)
[Waypoint-aided Navigation](https://drive.google.com/file/d/1yE4o4E4XnkK5toRakd7t5LulSuYEHGLY/view?usp=sharing)
