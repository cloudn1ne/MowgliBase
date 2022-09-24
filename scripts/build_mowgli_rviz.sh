#!/bin/bash

cd ~/MowgliBase
catkin_make --only-pkg-with-deps mowgli_rviz
cd -
