
### This procedure assumes that you have a working ROS Noetic installation on an Ubuntu 20.04 box 

If you dont have one yet, check the [first chapter of MowgliRover's setup instructions](https://github.com/cloudn1ne/MowgliRover/blob/main/help/InstallMowgli.md)

### Clone Repo

```
cd ~
git clone git@github.com:cloudn1ne/MowgliBase.git
cd ~/MowgliBase
catkin_make
git submodule update --init --recursive
```
(subrepos: mowgli, and open_mower_ros are needed due to dependencies via the ROS msgs types)

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
cn@roscore:~/MowgliBase$ ./scripts/build_imu_calibrate.sh
Base path: /home/cn/MowgliBase
Source space: /home/cn/MowgliBase/src
Build space: /home/cn/MowgliBase/build
Devel space: /home/cn/MowgliBase/devel
Install space: /home/cn/MowgliBase/install
Packages "open_mower_ros" not found in the workspace - ignoring them
Whitelisted packages: mower_msgs
####
#### Running command: "cmake /home/cn/MowgliBase/src -DCATKIN_DEVEL_PREFIX=/home/cn/MowgliBase/devel -DCMAKE_INSTALL_PREFIX=/home/cn/MowgliBase/install -DCATKIN_WHITELIST_PACKAGES=mower_msgs -G Unix Makefiles" in "/home/cn/MowgliBase/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/cn/MowgliBase/devel
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/home/cn/mowgli_base/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/home/cn/mowgli_base/devel;/opt/ros/noetic
-- Found PythonInterp: /usr/bin/python3 (found suitable version "3.8.10", minimum required is "3")
-- Using PYTHON_EXECUTABLE: /usr/bin/python3
-- Using Debian Python package layout
-- Using empy: /usr/lib/python3/dist-packages/em.py
-- Using CATKIN_ENABLE_TESTING: ON
-- Call enable_testing()
-- Using CATKIN_TEST_RESULTS_DIR: /home/cn/MowgliBase/build/test_results
-- Forcing gtest/gmock from source, though one was otherwise available.
-- Found gtest sources under '/usr/src/googletest': gtests will be built
-- Found gmock sources under '/usr/src/googletest': gmock will be built
-- Found PythonInterp: /usr/bin/python3 (found version "3.8.10")
-- Using Python nosetests: /usr/bin/nosetests3
-- catkin 0.8.10
-- BUILD_SHARED_LIBS is on
-- BUILD_SHARED_LIBS is on
-- Using CATKIN_WHITELIST_PACKAGES: mower_msgs
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~  traversing 1 packages in topological order:
-- ~~  - mower_msgs
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- +++ processing catkin package: 'mower_msgs'
-- ==> add_subdirectory(open_mower_ros/src/mower_msgs)
-- Using these message generators: gencpp;geneus;genlisp;gennodejs;genpy
-- mower_msgs: 3 messages, 4 services
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cn/MowgliBase/build
####
#### Running command: "make -j8 -l8" in "/home/cn/MowgliBase/build"
####
[  0%] Built target std_msgs_generate_messages_lisp
[  0%] Built target _mower_msgs_generate_messages_check_deps_EmergencyStopSrv
[  0%] Built target _mower_msgs_generate_messages_check_deps_MowerControlSrv
[  0%] Built target std_msgs_generate_messages_cpp
[  0%] Built target _mower_msgs_generate_messages_check_deps_ImuRaw
[  0%] Built target _mower_msgs_generate_messages_check_deps_HighLevelControlSrv
[  0%] Built target _mower_msgs_generate_messages_check_deps_ESCStatus
[  0%] Built target std_msgs_generate_messages_eus
[  0%] Built target std_msgs_generate_messages_py
[  0%] Built target std_msgs_generate_messages_nodejs
[  0%] Built target _mower_msgs_generate_messages_check_deps_Status
[  0%] Built target _mower_msgs_generate_messages_check_deps_GPSControlSrv
[ 18%] Built target mower_msgs_generate_messages_cpp
[ 36%] Built target mower_msgs_generate_messages_lisp
[ 57%] Built target mower_msgs_generate_messages_eus
[ 81%] Built target mower_msgs_generate_messages_py
[100%] Built target mower_msgs_generate_messages_nodejs
[100%] Built target mower_msgs_generate_messages
Base path: /home/cn/MowgliBase
Source space: /home/cn/MowgliBase/src
Build space: /home/cn/MowgliBase/build
Devel space: /home/cn/MowgliBase/devel
Install space: /home/cn/MowgliBase/install
Packages "open_mower_ros" not found in the workspace - ignoring them
Whitelisted packages: mowgli
####
#### Running command: "cmake /home/cn/MowgliBase/src -DCATKIN_DEVEL_PREFIX=/home/cn/MowgliBase/devel -DCMAKE_INSTALL_PREFIX=/home/cn/MowgliBase/install -DCATKIN_WHITELIST_PACKAGES=mowgli -G Unix Makefiles" in "/home/cn/MowgliBase/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/cn/MowgliBase/devel
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/home/cn/mowgli_base/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/home/cn/mowgli_base/devel;/opt/ros/noetic
-- Found PythonInterp: /usr/bin/python3 (found suitable version "3.8.10", minimum required is "3")
-- Using PYTHON_EXECUTABLE: /usr/bin/python3
-- Using Debian Python package layout
-- Using empy: /usr/lib/python3/dist-packages/em.py
-- Using CATKIN_ENABLE_TESTING: ON
-- Call enable_testing()
-- Using CATKIN_TEST_RESULTS_DIR: /home/cn/MowgliBase/build/test_results
-- Forcing gtest/gmock from source, though one was otherwise available.
-- Found gtest sources under '/usr/src/googletest': gtests will be built
-- Found gmock sources under '/usr/src/googletest': gmock will be built
-- Found PythonInterp: /usr/bin/python3 (found version "3.8.10")
-- Using Python nosetests: /usr/bin/nosetests3
-- catkin 0.8.10
-- BUILD_SHARED_LIBS is on
-- BUILD_SHARED_LIBS is on
-- Using CATKIN_WHITELIST_PACKAGES: mowgli
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~  traversing 1 packages in topological order:
-- ~~  - mowgli
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- +++ processing catkin package: 'mowgli'
-- ==> add_subdirectory(MowgliRover/src/mowgli)
-- Using these message generators: gencpp;geneus;genlisp;gennodejs;genpy
-- mowgli: 2 messages, 2 services
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cn/MowgliBase/build
####
#### Running command: "make -j8 -l8" in "/home/cn/MowgliBase/build"
####
[  0%] Built target std_msgs_generate_messages_eus
[  0%] Built target std_msgs_generate_messages_nodejs
[  3%] Building CXX object MowgliRover/src/mowgli/CMakeFiles/mowgli_proxy.dir/src/mowgli_proxy.cpp.o
[  3%] Built target std_msgs_generate_messages_lisp
[  3%] Built target std_msgs_generate_messages_cpp
[  3%] Built target std_msgs_generate_messages_py
[  3%] Built target _mowgli_generate_messages_check_deps_SetCfg
[  3%] Built target _mowgli_generate_messages_check_deps_GetCfg
[  7%] Built target mowgli_gencfg
[  7%] Built target _mowgli_generate_messages_check_deps_magnetometer
[  7%] Built target _mowgli_generate_messages_check_deps_status
[ 21%] Built target mowgli_generate_messages_cpp
[ 28%] Built target mowgli_blade
[ 42%] Built target mowgli_generate_messages_nodejs
[ 60%] Built target mowgli_generate_messages_eus
[ 82%] Built target mowgli_generate_messages_py
[ 96%] Built target mowgli_generate_messages_lisp
[ 96%] Built target mowgli_generate_messages
/home/cn/MowgliBase/src/MowgliRover/src/mowgli/src/mowgli_proxy.cpp:30:10: fatal error: ublox_msgs/NavPVT.h: No such file or directory
   30 | #include <ublox_msgs/NavPVT.h>
      |          ^~~~~~~~~~~~~~~~~~~~~
compilation terminated.
make[2]: *** [MowgliRover/src/mowgli/CMakeFiles/mowgli_proxy.dir/build.make:63: MowgliRover/src/mowgli/CMakeFiles/mowgli_proxy.dir/src/mowgli_proxy.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:499: MowgliRover/src/mowgli/CMakeFiles/mowgli_proxy.dir/all] Error 2
make: *** [Makefile:141: all] Error 2
Invoking "make -j8 -l8" failed
Base path: /home/cn/MowgliBase
Source space: /home/cn/MowgliBase/src
Build space: /home/cn/MowgliBase/build
Devel space: /home/cn/MowgliBase/devel
Install space: /home/cn/MowgliBase/install
Whitelisted packages: calibration_imu
####
#### Running command: "cmake /home/cn/MowgliBase/src -DCATKIN_DEVEL_PREFIX=/home/cn/MowgliBase/devel -DCMAKE_INSTALL_PREFIX=/home/cn/MowgliBase/install -DCATKIN_WHITELIST_PACKAGES=calibration_imu -G Unix Makefiles" in "/home/cn/MowgliBase/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/cn/MowgliBase/devel
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/home/cn/mowgli_base/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/home/cn/mowgli_base/devel;/opt/ros/noetic
-- Found PythonInterp: /usr/bin/python3 (found suitable version "3.8.10", minimum required is "3")
-- Using PYTHON_EXECUTABLE: /usr/bin/python3
-- Using Debian Python package layout
-- Using empy: /usr/lib/python3/dist-packages/em.py
-- Using CATKIN_ENABLE_TESTING: ON
-- Call enable_testing()
-- Using CATKIN_TEST_RESULTS_DIR: /home/cn/MowgliBase/build/test_results
-- Forcing gtest/gmock from source, though one was otherwise available.
-- Found gtest sources under '/usr/src/googletest': gtests will be built
-- Found gmock sources under '/usr/src/googletest': gmock will be built
-- Found PythonInterp: /usr/bin/python3 (found version "3.8.10")
-- Using Python nosetests: /usr/bin/nosetests3
-- catkin 0.8.10
-- BUILD_SHARED_LIBS is on
-- BUILD_SHARED_LIBS is on
-- Using CATKIN_WHITELIST_PACKAGES: calibration_imu
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
[  4%] Automatic MOC and UIC for target accelerometer
[  8%] Automatic MOC and UIC for target magnetometer
[  8%] Built target accelerometer_autogen
[  8%] Built target magnetometer_autogen
[ 12%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/calibrator.cpp.o
[ 56%] Built target accelerometer
[ 60%] Linking CXX executable /home/cn/MowgliBase/devel/lib/calibration_imu/magnetometer
[100%] Built target magnetometer
/home/cn/MowgliBase
```

Note you will get an error complaining about ublox_msgs
```
   30 | #include <ublox_msgs/NavPVT.h>
      |          ^~~~~~~~~~~~~~~~~~~~~
```
You can ignore that, we only need the ROS msg types from mowgli/openmower in order to build the imu_calibrate tool


Continue with calibrating Mowgli's Magentometer [here](Calibrate.md)

