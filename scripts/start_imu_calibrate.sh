#!/bin/bash

cd ~/MowgliBase
rosrun calibration_imu magnetometer imu/magnetometer:=/imu/mag_calibration
cd -

