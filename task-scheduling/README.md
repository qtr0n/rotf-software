# Dynamic Task Scheduling:
We envision a system in which autonomous mobile robots robustly perform service tasks in indoor environments. By splitting these tasks into proper scheduling agents and employing Linear Programming Optimization on each of the constraints, we aim to implement a robust scheduling algorithm as proposed in [this paper](http://www.cs.cmu.edu/~mmv/papers/11aaaiw-brian.pdf) with the following User-to-Robot Architecture: 

<p align="center">
<img src="https://github.com/theobscuredev/rotf-software/blob/main/navigation/assets/PSO_Setup1_Run1.png">
</p>

Segregating the tasks into the following agents enables a flexible scheduling:
* Interface Agent: To manage the bookings, including updating them real-time as per the input.
* Scheduling Agent: Receives the booking from Interface, checks the feasibility and stores them.
* Executing Manager Agent: Handles communication with robot, sending them the task to be executed.
* Robot Manager Agent: Handles communication with the server.
* Behaviour Interaction Planner: Executes the tasks by breaking them into sub-parts.
* Navigation: Handles the actual navigation.
* KBase: Used to store the current robot state.
