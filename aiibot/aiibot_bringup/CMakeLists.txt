cmake_minimum_required(VERSION 2.8.3)
project(aiibot_bringup)


find_package(catkin REQUIRED COMPONENTS
  controller_manager
  diff_drive_controller
  geometry_msgs
  robot_localization
  rosconsole
  roscpp
  sensor_msgs
  tf
  std_srvs
)
catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(velocity_send src/send_node.cpp)
target_link_libraries(velocity_send
  ${catkin_LIBRARIES}
)

add_executable(odometry_recv src/recv_node.cpp)
target_link_libraries(odometry_recv
  ${catkin_LIBRARIES}
)