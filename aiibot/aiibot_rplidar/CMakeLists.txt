cmake_minimum_required(VERSION 2.8.3)
project(aiibot_rplidar)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  rosconsole
  roscpp
  sensor_msgs
  std_srvs
)
set(RPLIDAR_SDK_PATH "./sdk/")
#set(RPLIDAR_SDK_SRC "./sdk/src/")

FILE(GLOB RPLIDAR_SDK_SRC 
  "${RPLIDAR_SDK_PATH}/src/arch/linux/*.cpp"
  "${RPLIDAR_SDK_PATH}/src/hal/*.cpp"
  "${RPLIDAR_SDK_PATH}/src/*.cpp"
)

catkin_package()


include_directories(
  ${RPLIDAR_SDK_PATH}/include
  ${RPLIDAR_SDK_PATH}/src
  ${catkin_INCLUDE_DIRS}
)

add_executable(rplidar src/rplidar_node.cpp ${RPLIDAR_SDK_SRC})
target_link_libraries(rplidar ${catkin_LIBRARIES})
