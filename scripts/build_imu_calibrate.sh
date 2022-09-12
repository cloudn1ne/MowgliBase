#!/bin/bash

cd ~/MowgliBase
catkin_make --only-pkg-with-deps calibration_imu
cd -
