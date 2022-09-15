
### This procedure assumes that you have a working ROS Noetic installation on an Ubuntu 20.04 box 

If you dont have one yet, check the [first chapter of MowgliRover's setup instructions](https://github.com/cloudn1ne/MowgliRover/blob/main/help/InstallMowgli.md)

### Clone Repo

```
cd ~
git clone git@github.com:cloudn1ne/MowgliBase.git
cd ~/MowgliBase
git submodule update --init --recursive
catkin_make --only-pkg-with-deps open_mower_ros mower_msgs
catkin_make --only-pkg-with-deps open_mower_ros mowgli
```

### Add the MowgliBase Workspace setup.bash to your .bashrc

```
echo "source ~/MowgliBase/devel/setup.bash " >> ~/.bashrc
. ~/.bashrc
```

### Qt requirements (for the IMU GUI)

```
sudo apt-get install -y build-essential qtcreator qt5-default libqt5datavisualization5-dev libqt5charts5-dev ros-noetic-robot-localization
```

### Compile imu_calibration

```
~/MowgliBase/scripts/build_imu_calibrate.sh
```

Output should look simliar to:

```
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~  traversing 1 packages in topological order:
-- ~~  - calibration_imu
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- +++ processing catkin package: 'calibration_imu'
-- ==> add_subdirectory(Mowgli-ros-calibration_imu)
-- Using these message generators: gencpp;geneus;genlisp;gennodejs;genpy
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cn/MowgliBase/build
####
#### Running command: "make -j8 -l8" in "/home/cn/MowgliBase/build"
####
Scanning dependencies of target accelerometer_autogen
Scanning dependencies of target magnetometer_autogen
[  4%] Automatic MOC and UIC for target accelerometer
[  8%] Automatic MOC and UIC for target magnetometer
[  8%] Built target accelerometer_autogen
Scanning dependencies of target accelerometer
[  8%] Built target magnetometer_autogen
Scanning dependencies of target magnetometer
[ 12%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/accelerometer_autogen/mocs_compilation.cpp.o
[ 16%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/graph/graph.cpp.o
[ 20%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/data/data_interface.cpp.o
[ 24%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/main.cpp.o
[ 28%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/common/geometry/ellipsoid.cpp.o
[ 32%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/gui/fmain.cpp.o
[ 36%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/common/calibration/variables_center.cpp.o
[ 40%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/magnetometer_autogen/mocs_compilation.cpp.o
[ 44%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/common/calibration/variables_radius.cpp.o
[ 48%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/calibration/cost_term.cpp.o
[ 52%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/calibration/calibrator.cpp.o
[ 56%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/main.cpp.o
[ 60%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/gui/fmain.cpp.o
[ 64%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/data/data_interface.cpp.o
[ 68%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/common/geometry/ellipsoid.cpp.o
[ 72%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/graph/graph.cpp.o
[ 76%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/common/calibration/variables_center.cpp.o
[ 80%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/variables_rotation.cpp.o
[ 84%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/common/calibration/variables_radius.cpp.o
[ 88%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/cost_term.cpp.o
[ 92%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/calibrator.cpp.o
[ 96%] Linking CXX executable /home/cn/MowgliBase/devel/lib/calibration_imu/accelerometer
[ 96%] Built target accelerometer
[100%] Linking CXX executable /home/cn/MowgliBase/devel/lib/calibration_imu/magnetometer
[100%] Built target magnetometer
```

Continue with calibrating Mowgli's Magentometer [here](Calibrate.md)

