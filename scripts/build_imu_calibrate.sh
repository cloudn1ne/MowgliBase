#!/bin/bash

cd ~/MowgliBase
catkin_make --only-pkg-with-deps mower_msgs
catkin_make --only-pkg-with-deps mowgli
catkin_make --only-pkg-with-deps sensor_msgs_ext
catkin_make --only-pkg-with-deps calibration_imu
cd -
