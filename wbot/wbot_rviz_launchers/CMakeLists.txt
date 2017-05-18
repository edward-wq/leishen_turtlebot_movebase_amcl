cmake_minimum_required(VERSION 2.8.3)
project(aiibot_rviz_launchers)

find_package(catkin REQUIRED COMPONENTS
  aiibot_description
  joint_state_publisher
  rviz
  rviz_imu_plugin
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)
