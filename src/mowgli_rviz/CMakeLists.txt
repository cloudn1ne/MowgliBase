cmake_minimum_required(VERSION 3.0.2)
project(mowgli_rviz)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Get the information about this package's buildtime dependencies
find_package(catkin REQUIRED
    roscpp
    grid_map_core
    grid_map_ros
    mower_map
    nav_msgs
    ublox_gps
#  tf2_geometry_msgs
#  grid_map_cv
#  grid_map_filters
#  grid_map_loader
#  grid_map_msgs
#  grid_map_octomap
#    COMPONENTS message_generation std_msgs sensor_msgs
)

catkin_package(
        INCLUDE_DIRS include
        #  LIBRARIES mowgli_rviz
        #  CATKIN_DEPENDS other_catkin_pkg
        #  DEPENDS system_lib
)


include_directories(
        # include
         ${catkin_INCLUDE_DIRS}
)

# Declare the message files to be built
#  add_message_files(FILES
#    MyMessage1.msg
#    MyMessage2.msg
#  )

# Declare the service files to be built
#  add_service_files(FILES
#    MyService.srv
#  )

# Actually generate the language-specific message and service files
#  generate_messages(DEPENDENCIES std_msgs sensor_msgs)

# Declare that this catkin package's runtime dependencies
#  catkin_package(
#   CATKIN_DEPENDS message_runtime std_msgs sensor_msgs
#  )

# define executable using MyMessage1 etc.
add_executable(mowgli_rviz src/mowgli_rviz.cpp)

# link libraries
target_link_libraries(
  mowgli_rviz
  ${catkin_LIBRARIES}
)

