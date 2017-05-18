# Aiibot 移动平台上激光雷达调用程序

## 程序包说明

该程序包是由思岚官方Git： https://github.com/robopeak/rplidar_ros  提供，我对他们的程序包进行了本地化处理，使其更好的适用于我们的Aiibot移动平台。

本程序包主要是在ROS环境下调用激光雷达驱动，并把激光雷达数据通过Topic: /scan 发布出来，这样当其他程序，如gmapping建图，需要使用激光数据时，直接订阅该Topic即可。

具体编译和运行操作如下：

## 1 编译
### 1.1 创建并初始化 Workspace
如果工作空间已存在，则跳过该步骤，如果不存在，那么：

打开终端(ctrl + alt + T), 输入如下指令：

```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ catkin_init_workspace
$ cd ~/catkin_ws
$ catkin_make
$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```

### 1.2 拷贝工程到 workspace

继续输入如下指令：

```
$ cd ~/catkin_ws/src
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_rplidar.git
$ cd ~/catkin_ws
$ caktin_make
$ source ~/.bashrc
```

执行完毕后，关闭终端

## 2 运行
1. 修改 ./launch/rplidar.launch 文件中

    ```
    <param name="serial_port"         type="string" value="/dev/ttyUSB1"/>
    ```
    
    改为
    
    ```
    <param name="serial_port"         type="string" value="/dev/ttyUSB0"/>
    ```

2. 插入激光雷达串口线
3. 运行如下指令：

    ```
    roslaunch aiibot_rplidar rplidar.launch
    ```
4. 如果需要可视化显示激光雷达探测情况，请参考：
    http://git.aiiage.com:9000/liu.f/aiibot_rviz_launchers/blob/master/README.md

***
## 版权声明

本文档版权归深圳寒武纪智能科技有限公司所有，并保留一切权利。未经书面许可，任何公司和个人不得将此文档中的任何部分公开、转载或以其他方式散发给第三方。否则，必将追究其法律责任。

*作者：刘发 创建日期：2016/08/16*