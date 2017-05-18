cmake_minimum_required(VERSION 2.8.3)
project(aiibot_teleop)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Mark executable scripts (Python etc.) for installation
install(PROGRAMS
  scripts/aiibot_teleop_key
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
