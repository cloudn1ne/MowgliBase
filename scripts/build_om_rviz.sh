#!/bin/bash

cd ~/MowgliBase
echo ""
echo " Building the OpenMower version of mowgli_rviz"
echo ""
catkin_make --cmake-args=-DOPENMOWER_ONLY --only-pkg-with-deps mowgli_rviz
cd -
