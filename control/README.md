# Control Scripts
LiDAR based [SLAM](https://github.com/theobscuredev/rotf-software/blob/main/control/mapping.m) is used for reactive control following the [G-Mapping](https://openslam-org.github.io/gmapping.html) Strategy.
[Extended Kalman Filter](https://github.com/theobscuredev/rotf-software/blob/main/control/ekf.m) is used to linearize the position and velocity estimates. A [teleop](https://github.com/theobscuredev/rotf-software/blob/main/control/teleop.m) i.e keyboard enabled input method is also provided for manual control.
Combining all these features, the actual [control](https://github.com/theobscuredev/rotf-software/blob/main/control/wapoint_path.m) occurs while tracing the path predicted by PSO.
