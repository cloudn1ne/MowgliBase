
### This procedure assumes that you have a working ROS Noetic installation on an Ubuntu 20.04 box 

If you dont have one yet, check the [first chapter of MowgliRover's setup instructions](https://github.com/cloudn1ne/MowgliRover/blob/main/help/InstallMowgli.md) up to at least step 1.5.

The following ROS related Ubuntu pkgs are required at a minimum to compile the IMU calibration tool

```
sudo apt-get -y install g++ cpp cmake ros-noetic-tf2-eigen ros-noetic-teleop-twist-keyboard ros-noetic-robot-state-publisher ros-noetic-joint-state-publisher ros-noetic-map-server ros-noetic-rosserial-server ros-noetic-gps-common picocom  ros-noetic-tf2-geometry-msgs ros-noetic-robot-localization libpigpiod-if-dev wavemon ros-noetic-rosserial-arduino python3-paho-mqtt openocd python3-rosdep ros-noetic-ifopt
```

### Clone Repo

```
cd ~
git clone https://github.com/cloudn1ne/MowgliBase.git
cd ~/MowgliBase
source /opt/ros/noetic/setup.bash
catkin_make
git submodule update --init
```
(subrepos: mowgli, and open_mower_ros are needed due to dependencies via the ROS msgs types)

### Add the MowgliBase Workspace setup.bash to your .bashrc

```
echo "source ~/MowgliBase/devel/setup.bash " >> ~/.bashrc
. ~/.bashrc
```

### Qt requirements (for the IMU GUI)

```
sudo apt-get install -y build-essential qtcreator qt5-default libqt5datavisualization5-dev libqt5charts5-dev ros-noetic-robot-localization ros-noetic-ublox
```

### Compile imu_calibration

```
~/MowgliBase/scripts/build_imu_calibrate.sh
```

Output should look simliar to:

```
~/MowgliBase/scripts/build_imu_calibrate.sh
Base path: /home/cn/MowgliBase
Source space: /home/cn/MowgliBase/src
Build space: /home/cn/MowgliBase/build
Devel space: /home/cn/MowgliBase/devel
Install space: /home/cn/MowgliBase/install
Whitelisted packages: mower_msgs
####
#### Running command: "cmake /home/cn/MowgliBase/src -DCATKIN_DEVEL_PREFIX=/home/cn/MowgliBase/devel -DCMAKE_INSTALL_PREFIX=/home/cn/MowgliBase/install -DCATKIN_WHITELIST_PACKAGES=mower_msgs -G Unix Makefiles" in "/home/cn/MowgliBase/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/cn/MowgliBase/devel
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/opt/ros/noetic
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
#### Running command: "make -j2 -l2" in "/home/cn/MowgliBase/build"
####
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_GPSControlSrv
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_HighLevelControlSrv
[  0%] Built target _mower_msgs_generate_messages_check_deps_GPSControlSrv
[  0%] Built target _mower_msgs_generate_messages_check_deps_HighLevelControlSrv
Scanning dependencies of target std_msgs_generate_messages_lisp
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_ImuRaw
[  0%] Built target std_msgs_generate_messages_lisp
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_MowerControlSrv
[  0%] Built target _mower_msgs_generate_messages_check_deps_ImuRaw
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_EmergencyStopSrv
[  0%] Built target _mower_msgs_generate_messages_check_deps_MowerControlSrv
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_Status
[  0%] Built target _mower_msgs_generate_messages_check_deps_EmergencyStopSrv
Scanning dependencies of target _mower_msgs_generate_messages_check_deps_ESCStatus
[  0%] Built target _mower_msgs_generate_messages_check_deps_Status
Scanning dependencies of target std_msgs_generate_messages_cpp
[  0%] Built target std_msgs_generate_messages_cpp
[  0%] Built target _mower_msgs_generate_messages_check_deps_ESCStatus
Scanning dependencies of target std_msgs_generate_messages_eus
Scanning dependencies of target std_msgs_generate_messages_nodejs
[  0%] Built target std_msgs_generate_messages_eus
[  0%] Built target std_msgs_generate_messages_nodejs
Scanning dependencies of target std_msgs_generate_messages_py
Scanning dependencies of target mower_msgs_generate_messages_lisp
[  0%] Built target std_msgs_generate_messages_py
[  2%] Generating Lisp code from mower_msgs/Status.msg
Scanning dependencies of target mower_msgs_generate_messages_cpp
[  5%] Generating C++ code from mower_msgs/Status.msg
[  7%] Generating Lisp code from mower_msgs/ImuRaw.msg
[ 10%] Generating Lisp code from mower_msgs/ESCStatus.msg
[ 13%] Generating C++ code from mower_msgs/ImuRaw.msg
[ 15%] Generating Lisp code from mower_msgs/EmergencyStopSrv.srv
[ 18%] Generating Lisp code from mower_msgs/GPSControlSrv.srv
[ 21%] Generating C++ code from mower_msgs/ESCStatus.msg
[ 23%] Generating Lisp code from mower_msgs/MowerControlSrv.srv
[ 26%] Generating Lisp code from mower_msgs/HighLevelControlSrv.srv
[ 28%] Generating C++ code from mower_msgs/EmergencyStopSrv.srv
[ 28%] Built target mower_msgs_generate_messages_lisp
Scanning dependencies of target mower_msgs_generate_messages_eus
[ 31%] Generating EusLisp code from mower_msgs/Status.msg
[ 34%] Generating EusLisp code from mower_msgs/ImuRaw.msg
[ 36%] Generating C++ code from mower_msgs/GPSControlSrv.srv
[ 39%] Generating EusLisp code from mower_msgs/ESCStatus.msg
[ 42%] Generating EusLisp code from mower_msgs/EmergencyStopSrv.srv
[ 44%] Generating C++ code from mower_msgs/MowerControlSrv.srv
[ 47%] Generating EusLisp code from mower_msgs/GPSControlSrv.srv
[ 50%] Generating EusLisp code from mower_msgs/MowerControlSrv.srv
[ 52%] Generating C++ code from mower_msgs/HighLevelControlSrv.srv
[ 55%] Generating EusLisp code from mower_msgs/HighLevelControlSrv.srv
[ 57%] Generating EusLisp manifest code for mower_msgs
[ 57%] Built target mower_msgs_generate_messages_cpp
Scanning dependencies of target mower_msgs_generate_messages_nodejs
[ 60%] Generating Javascript code from mower_msgs/Status.msg
[ 63%] Generating Javascript code from mower_msgs/ImuRaw.msg
[ 65%] Generating Javascript code from mower_msgs/ESCStatus.msg
[ 68%] Generating Javascript code from mower_msgs/EmergencyStopSrv.srv
[ 71%] Generating Javascript code from mower_msgs/GPSControlSrv.srv
[ 71%] Built target mower_msgs_generate_messages_eus
Scanning dependencies of target mower_msgs_generate_messages_py
[ 73%] Generating Python from MSG mower_msgs/Status
[ 76%] Generating Javascript code from mower_msgs/MowerControlSrv.srv
[ 78%] Generating Javascript code from mower_msgs/HighLevelControlSrv.srv
[ 78%] Built target mower_msgs_generate_messages_nodejs
[ 81%] Generating Python from MSG mower_msgs/ImuRaw
[ 84%] Generating Python from MSG mower_msgs/ESCStatus
[ 86%] Generating Python code from SRV mower_msgs/EmergencyStopSrv
[ 89%] Generating Python code from SRV mower_msgs/GPSControlSrv
[ 92%] Generating Python code from SRV mower_msgs/MowerControlSrv
[ 94%] Generating Python code from SRV mower_msgs/HighLevelControlSrv
[100%] Generating Python msg __init__.py for mower_msgs
[100%] Generating Python srv __init__.py for mower_msgs
[100%] Built target mower_msgs_generate_messages_py
Scanning dependencies of target mower_msgs_generate_messages
[100%] Built target mower_msgs_generate_messages
Base path: /home/cn/MowgliBase
Source space: /home/cn/MowgliBase/src
Build space: /home/cn/MowgliBase/build
Devel space: /home/cn/MowgliBase/devel
Install space: /home/cn/MowgliBase/install
Whitelisted packages: mowgli
####
#### Running command: "cmake /home/cn/MowgliBase/src -DCATKIN_DEVEL_PREFIX=/home/cn/MowgliBase/devel -DCMAKE_INSTALL_PREFIX=/home/cn/MowgliBase/install -DCATKIN_WHITELIST_PACKAGES=mowgli -G Unix Makefiles" in "/home/cn/MowgliBase/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/cn/MowgliBase/devel
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/opt/ros/noetic
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
-- Found GeographicLib: /usr/lib/x86_64-linux-gnu
-- mowgli: 2 messages, 2 services
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cn/MowgliBase/build
####
#### Running command: "make -j2 -l2" in "/home/cn/MowgliBase/build"
####
Scanning dependencies of target _mowgli_generate_messages_check_deps_GetCfg
Scanning dependencies of target _mowgli_generate_messages_check_deps_SetCfg
[  0%] Built target _mowgli_generate_messages_check_deps_SetCfg
[  0%] Built target _mowgli_generate_messages_check_deps_GetCfg
Scanning dependencies of target _mowgli_generate_messages_check_deps_status
Scanning dependencies of target _mowgli_generate_messages_check_deps_magnetometer
[  0%] Built target _mowgli_generate_messages_check_deps_magnetometer
[  0%] Built target _mowgli_generate_messages_check_deps_status
Scanning dependencies of target std_msgs_generate_messages_cpp
Scanning dependencies of target std_msgs_generate_messages_eus
[  0%] Built target std_msgs_generate_messages_cpp
[  0%] Built target std_msgs_generate_messages_eus
Scanning dependencies of target std_msgs_generate_messages_nodejs
Scanning dependencies of target std_msgs_generate_messages_lisp
[  0%] Built target std_msgs_generate_messages_nodejs
[  0%] Built target std_msgs_generate_messages_lisp
Scanning dependencies of target std_msgs_generate_messages_py
Scanning dependencies of target mowgli_gencfg
[  0%] Built target std_msgs_generate_messages_py
[  3%] Generating dynamic reconfigure files from cfg/MowgliProxy.cfg: /home/cn/MowgliBase/devel/include/mowgli/MowgliProxyConfig.h /home/cn/MowgliBase/devel/lib/python3/dist-packages/mowgli/cfg/MowgliProxyConfig.py
Scanning dependencies of target mowgli_blade
[  7%] Building CXX object MowgliRover/src/mowgli/CMakeFiles/mowgli_blade.dir/src/mowgli_blade.cpp.o
Generating reconfiguration files for MowgliProxy in mowgli
Wrote header file in /home/cn/MowgliBase/devel/include/mowgli/MowgliProxyConfig.h
[  7%] Built target mowgli_gencfg
Scanning dependencies of target mowgli_generate_messages_cpp
[ 10%] Generating C++ code from mowgli/magnetometer.msg
[ 14%] Generating C++ code from mowgli/status.msg
[ 17%] Generating C++ code from mowgli/SetCfg.srv
[ 21%] Generating C++ code from mowgli/GetCfg.srv
[ 21%] Built target mowgli_generate_messages_cpp
Scanning dependencies of target mowgli_generate_messages_eus
[ 25%] Generating EusLisp code from mowgli/magnetometer.msg
[ 28%] Generating EusLisp code from mowgli/status.msg
[ 32%] Generating EusLisp code from mowgli/SetCfg.srv
[ 35%] Generating EusLisp code from mowgli/GetCfg.srv
[ 39%] Generating EusLisp manifest code for mowgli
[ 39%] Built target mowgli_generate_messages_eus
Scanning dependencies of target mowgli_generate_messages_nodejs
[ 42%] Generating Javascript code from mowgli/magnetometer.msg
[ 46%] Generating Javascript code from mowgli/status.msg
[ 50%] Generating Javascript code from mowgli/SetCfg.srv
[ 53%] Generating Javascript code from mowgli/GetCfg.srv
[ 53%] Built target mowgli_generate_messages_nodejs
Scanning dependencies of target mowgli_generate_messages_lisp
[ 57%] Generating Lisp code from mowgli/magnetometer.msg
[ 60%] Generating Lisp code from mowgli/status.msg
[ 64%] Generating Lisp code from mowgli/SetCfg.srv
[ 67%] Generating Lisp code from mowgli/GetCfg.srv
[ 67%] Built target mowgli_generate_messages_lisp
Scanning dependencies of target mowgli_generate_messages_py
[ 71%] Generating Python from MSG mowgli/magnetometer
[ 75%] Generating Python from MSG mowgli/status
[ 78%] Generating Python code from SRV mowgli/SetCfg
[ 82%] Generating Python code from SRV mowgli/GetCfg
[ 85%] Linking CXX executable /home/cn/MowgliBase/devel/lib/mowgli/mowgli_blade
[ 89%] Generating Python msg __init__.py for mowgli
[ 89%] Built target mowgli_blade
Scanning dependencies of target mowgli_proxy
[ 92%] Generating Python srv __init__.py for mowgli
[ 96%] Building CXX object MowgliRover/src/mowgli/CMakeFiles/mowgli_proxy.dir/src/mowgli_proxy.cpp.o
[ 96%] Built target mowgli_generate_messages_py
Scanning dependencies of target mowgli_generate_messages
[ 96%] Built target mowgli_generate_messages
[100%] Linking CXX executable /home/cn/MowgliBase/devel/lib/mowgli/mowgli_proxy
[100%] Built target mowgli_proxy
Base path: /home/cn/MowgliBase
Source space: /home/cn/MowgliBase/src
Build space: /home/cn/MowgliBase/build
Devel space: /home/cn/MowgliBase/devel
Install space: /home/cn/MowgliBase/install
Whitelisted packages: sensor_msgs_ext
####
#### Running command: "cmake /home/cn/MowgliBase/src -DCATKIN_DEVEL_PREFIX=/home/cn/MowgliBase/devel -DCMAKE_INSTALL_PREFIX=/home/cn/MowgliBase/install -DCATKIN_WHITELIST_PACKAGES=sensor_msgs_ext -G Unix Makefiles" in "/home/cn/MowgliBase/build"
####
-- Using CATKIN_DEVEL_PREFIX: /home/cn/MowgliBase/devel
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/opt/ros/noetic
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
-- Using CATKIN_WHITELIST_PACKAGES: sensor_msgs_ext
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~  traversing 1 packages in topological order:
-- ~~  - sensor_msgs_ext
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- +++ processing catkin package: 'sensor_msgs_ext'
-- ==> add_subdirectory(ros-sensor_msgs_ext)
-- Using these message generators: gencpp;geneus;genlisp;gennodejs;genpy
-- sensor_msgs_ext: 12 messages, 3 services
-- Configuring done
-- Generating done
-- Build files have been written to: /home/cn/MowgliBase/build
####
#### Running command: "make -j2 -l2" in "/home/cn/MowgliBase/build"
####
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_gyroscope
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_axis_state
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_gyroscope
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_axis_state
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_magnetometer
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_analog_voltage
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_magnetometer
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_analog_voltage
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_temperature
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_accelerometer
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_temperature
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_accelerometer
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_time_reference
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_gnss_track
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_gnss_track
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_time_reference
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_gnss_position
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_gnss_fix
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_gnss_position
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_gnss_fix
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_covariance
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_calibrate_gyroscope
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_calibrate_gyroscope
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_covariance
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_set_axis_home
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_proximity
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_proximity
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_set_axis_home
Scanning dependencies of target _sensor_msgs_ext_generate_messages_check_deps_get_proximity_configuration
[  0%] Built target _sensor_msgs_ext_generate_messages_check_deps_get_proximity_configuration
Scanning dependencies of target sensor_msgs_ext_generate_messages_eus
Scanning dependencies of target sensor_msgs_ext_generate_messages_py
[  1%] Generating EusLisp code from sensor_msgs_ext/axis_state.msg
[  2%] Generating Python from MSG sensor_msgs_ext/axis_state
[  3%] Generating EusLisp code from sensor_msgs_ext/proximity.msg
[  5%] Generating EusLisp code from sensor_msgs_ext/analog_voltage.msg
[  6%] Generating Python from MSG sensor_msgs_ext/proximity
[  7%] Generating EusLisp code from sensor_msgs_ext/time_reference.msg
[  8%] Generating EusLisp code from sensor_msgs_ext/gnss_fix.msg
[ 10%] Generating Python from MSG sensor_msgs_ext/analog_voltage
[ 11%] Generating EusLisp code from sensor_msgs_ext/gnss_position.msg
[ 12%] Generating EusLisp code from sensor_msgs_ext/gnss_track.msg
[ 14%] Generating Python from MSG sensor_msgs_ext/time_reference
[ 15%] Generating EusLisp code from sensor_msgs_ext/accelerometer.msg
[ 16%] Generating EusLisp code from sensor_msgs_ext/gyroscope.msg
[ 17%] Generating Python from MSG sensor_msgs_ext/gnss_fix
[ 19%] Generating EusLisp code from sensor_msgs_ext/magnetometer.msg
[ 20%] Generating EusLisp code from sensor_msgs_ext/temperature.msg
[ 21%] Generating Python from MSG sensor_msgs_ext/gnss_position
[ 23%] Generating EusLisp code from sensor_msgs_ext/covariance.msg
[ 24%] Generating EusLisp code from sensor_msgs_ext/calibrate_gyroscope.srv
[ 25%] Generating EusLisp code from sensor_msgs_ext/set_axis_home.srv
[ 26%] Generating Python from MSG sensor_msgs_ext/gnss_track
[ 28%] Generating EusLisp code from sensor_msgs_ext/get_proximity_configuration.srv
[ 29%] Generating EusLisp manifest code for sensor_msgs_ext
[ 30%] Generating Python from MSG sensor_msgs_ext/accelerometer
[ 32%] Generating Python from MSG sensor_msgs_ext/gyroscope
[ 32%] Built target sensor_msgs_ext_generate_messages_eus
Scanning dependencies of target sensor_msgs_ext_generate_messages_cpp
[ 33%] Generating C++ code from sensor_msgs_ext/axis_state.msg
[ 34%] Generating Python from MSG sensor_msgs_ext/magnetometer
[ 35%] Generating C++ code from sensor_msgs_ext/proximity.msg
[ 37%] Generating Python from MSG sensor_msgs_ext/temperature
[ 38%] Generating C++ code from sensor_msgs_ext/analog_voltage.msg
[ 39%] Generating C++ code from sensor_msgs_ext/time_reference.msg
[ 41%] Generating Python from MSG sensor_msgs_ext/covariance
[ 42%] Generating C++ code from sensor_msgs_ext/gnss_fix.msg
[ 43%] Generating C++ code from sensor_msgs_ext/gnss_position.msg
[ 44%] Generating Python code from SRV sensor_msgs_ext/calibrate_gyroscope
[ 46%] Generating C++ code from sensor_msgs_ext/gnss_track.msg
[ 47%] Generating Python code from SRV sensor_msgs_ext/set_axis_home
[ 48%] Generating C++ code from sensor_msgs_ext/accelerometer.msg
[ 50%] Generating C++ code from sensor_msgs_ext/gyroscope.msg
[ 51%] Generating Python code from SRV sensor_msgs_ext/get_proximity_configuration
[ 52%] Generating C++ code from sensor_msgs_ext/magnetometer.msg
[ 53%] Generating C++ code from sensor_msgs_ext/temperature.msg
[ 55%] Generating Python msg __init__.py for sensor_msgs_ext
[ 56%] Generating C++ code from sensor_msgs_ext/covariance.msg
[ 57%] Generating Python srv __init__.py for sensor_msgs_ext
[ 58%] Generating C++ code from sensor_msgs_ext/calibrate_gyroscope.srv
[ 58%] Built target sensor_msgs_ext_generate_messages_py
Scanning dependencies of target sensor_msgs_ext_generate_messages_nodejs
[ 60%] Generating Javascript code from sensor_msgs_ext/axis_state.msg
[ 61%] Generating C++ code from sensor_msgs_ext/set_axis_home.srv
[ 62%] Generating Javascript code from sensor_msgs_ext/proximity.msg
[ 64%] Generating Javascript code from sensor_msgs_ext/analog_voltage.msg
[ 65%] Generating Javascript code from sensor_msgs_ext/time_reference.msg
[ 66%] Generating C++ code from sensor_msgs_ext/get_proximity_configuration.srv
[ 67%] Generating Javascript code from sensor_msgs_ext/gnss_fix.msg
[ 69%] Generating Javascript code from sensor_msgs_ext/gnss_position.msg
[ 70%] Generating Javascript code from sensor_msgs_ext/gnss_track.msg
[ 70%] Built target sensor_msgs_ext_generate_messages_cpp
Scanning dependencies of target sensor_msgs_ext_generate_messages_lisp
[ 71%] Generating Lisp code from sensor_msgs_ext/axis_state.msg
[ 73%] Generating Javascript code from sensor_msgs_ext/accelerometer.msg
[ 74%] Generating Lisp code from sensor_msgs_ext/proximity.msg
[ 75%] Generating Javascript code from sensor_msgs_ext/gyroscope.msg
[ 76%] Generating Lisp code from sensor_msgs_ext/analog_voltage.msg
[ 78%] Generating Javascript code from sensor_msgs_ext/magnetometer.msg
[ 79%] Generating Lisp code from sensor_msgs_ext/time_reference.msg
[ 80%] Generating Javascript code from sensor_msgs_ext/temperature.msg
[ 82%] Generating Lisp code from sensor_msgs_ext/gnss_fix.msg
[ 83%] Generating Javascript code from sensor_msgs_ext/covariance.msg
[ 84%] Generating Lisp code from sensor_msgs_ext/gnss_position.msg
[ 85%] Generating Javascript code from sensor_msgs_ext/calibrate_gyroscope.srv
[ 87%] Generating Lisp code from sensor_msgs_ext/gnss_track.msg
[ 88%] Generating Javascript code from sensor_msgs_ext/set_axis_home.srv
[ 89%] Generating Lisp code from sensor_msgs_ext/accelerometer.msg
[ 91%] Generating Javascript code from sensor_msgs_ext/get_proximity_configuration.srv
[ 92%] Generating Lisp code from sensor_msgs_ext/gyroscope.msg
[ 92%] Built target sensor_msgs_ext_generate_messages_nodejs
[ 93%] Generating Lisp code from sensor_msgs_ext/magnetometer.msg
[ 94%] Generating Lisp code from sensor_msgs_ext/temperature.msg
[ 96%] Generating Lisp code from sensor_msgs_ext/covariance.msg
[ 97%] Generating Lisp code from sensor_msgs_ext/calibrate_gyroscope.srv
[ 98%] Generating Lisp code from sensor_msgs_ext/set_axis_home.srv
[100%] Generating Lisp code from sensor_msgs_ext/get_proximity_configuration.srv
[100%] Built target sensor_msgs_ext_generate_messages_lisp
Scanning dependencies of target sensor_msgs_ext_generate_messages
[100%] Built target sensor_msgs_ext_generate_messages
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
-- Using CMAKE_PREFIX_PATH: /home/cn/MowgliBase/devel;/opt/ros/noetic
-- This workspace overlays: /home/cn/MowgliBase/devel;/opt/ros/noetic
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
#### Running command: "make -j2 -l2" in "/home/cn/MowgliBase/build"
####
Scanning dependencies of target accelerometer_autogen
Scanning dependencies of target magnetometer_autogen
[  8%] Automatic MOC and UIC for target magnetometer
[  8%] Automatic MOC and UIC for target accelerometer
[  8%] Built target accelerometer_autogen
Scanning dependencies of target accelerometer
[ 12%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/accelerometer_autogen/mocs_compilation.cpp.o
[ 12%] Built target magnetometer_autogen
Scanning dependencies of target magnetometer
[ 16%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/magnetometer_autogen/mocs_compilation.cpp.o
[ 20%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/main.cpp.o
[ 24%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/main.cpp.o
[ 28%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/gui/fmain.cpp.o
[ 32%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/gui/fmain.cpp.o
[ 36%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/data/data_interface.cpp.o
[ 40%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/data/data_interface.cpp.o
[ 44%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/graph/graph.cpp.o
[ 48%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/common/geometry/ellipsoid.cpp.o
[ 52%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/common/geometry/ellipsoid.cpp.o
[ 56%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/graph/graph.cpp.o
[ 60%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/common/calibration/variables_center.cpp.o
[ 64%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/common/calibration/variables_radius.cpp.o
[ 68%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/calibration/cost_term.cpp.o
[ 72%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/accelerometer.dir/src/accelerometer/calibration/calibrator.cpp.o
[ 76%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/common/calibration/variables_center.cpp.o
[ 80%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/variables_rotation.cpp.o
[ 84%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/common/calibration/variables_radius.cpp.o
[ 88%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/cost_term.cpp.o
[ 92%] Building CXX object Mowgli-ros-calibration_imu/CMakeFiles/magnetometer.dir/src/magnetometer/calibration/calibrator.cpp.o
[ 96%] Linking CXX executable /home/cn/MowgliBase/devel/lib/calibration_imu/accelerometer
[ 96%] Built target accelerometer
[100%] Linking CXX executable /home/cn/MowgliBase/devel/lib/calibration_imu/magnetometer
[100%] Built target magnetometer
/home/cn/MowgliBase
```


Continue with calibrating Mowgli's Magentometer [here](Calibrate.md)

