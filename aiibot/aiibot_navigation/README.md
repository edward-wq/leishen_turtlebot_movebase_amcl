# Aiibot 导航和建图程序

## 功能说明
本程序包包含了Aiibot移动平台关于激光SLAM的所有相关操作，共包含：
- Gmapping 建图程序
- Move base + Amcl 导航（有地图）
- Move base 导航（无地图，不建图）
- Move base 导航（无地图，使用 Gmapping 建图）

操作说明简易版请参考：*http://git.aiiage.com:9000/liu.f/aiibot-manual/blob/master/aiibot-manual-mini.md*

详细编译和使用方法如下：

## 1 编译方法：
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
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_bringup.git
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_rplidar.git
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_teleop.git
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_navigation.git
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_description.git
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_rviz_launchers.git
$ cd ~/catkin_ws
$ caktin_make
$ source ~/.bashrc
```

执行完毕后，关闭终端

## 2. 使用方法

要使用 aiibot_navigation 这个Package， 需要如下几个步骤：

### 2.1 启动ROSCORE
打开一个终端(ctrl+alt+T), 输入如下指令:
```
$ roscore
```
### 2.2 启动底盘和激光雷达
1. 连接底盘串口和激光雷达串口，如果遇到问题，请参照：http://git.aiiage.com:9000/liu.f/aiibot_bringup/blob/master/README.md
2. 连接后好，打开一个新的终端(ctrl+shift+T)，输入如下指令：

    ```
    $ roslaunch aiibot_bringup run.launch
    ```

### 2.3 使用Gmapping建图
在步骤2.2之后，如果想运行Gmapping建图程序，那么请运行如下步骤：
1. 运行Gmapping

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_navigation gmapping_demo.launch
    ```
    
2. 打开 Rviz 用于显示实时建图效果

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_rviz_launchers view_gmapping.launch
    ```
    
    详情请参考：http://git.aiiage.com:9000/liu.f/aiibot_rviz_launchers/blob/master/README.md
    
3.  打开键盘控制程序

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_teleop keyboard_teleop.launch
    ```
    
    详细的控制方法，请参考：http://git.aiiage.com:9000/liu.f/aiibot_teleop/blob/master/README.md

    [注意] 在运动过程中，需要保持这个运行键盘控制程序的终端处于选中状态。

### 2.4 根据已有地图进行导航

在步骤2.2之后，如果想运行根据已有地图进行导航程序，那么请运行如下步骤：

1. 运行amcl

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_navigation amcl_demo.launch
    ```
    
    [注意]　需要一个已知先验地图（位于～/catkin_ws/src/aiibot_navigation/map/）
    
2. 打开 Rviz 用于显示实时建图效果

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_rviz_launchers view_amcl.launch
    ```
    
    详情请参考：http://git.aiiage.com:9000/liu.f/aiibot_rviz_launchers/blob/master/README.md
    
3.  矫正初始位置

    虽然在加载地图过程中，机器人会自动判断当前所对应的地图位置，但往往会出现偏差。就算在导航过程中，机器人会根据障碍物自动定位，但是如果其实位置偏差过大，最后的结果往往会不如人意，所以这里我们要手动估计机器人的位姿。
    
    具体操作是：选中Rviz窗口工具栏中，2D Pose Estimate工具；然后在地图相应位置点击并拖动，点击的位置代表了机器人的实际位置，绿色箭头的方向代表机器人的朝向。
    
    当确定好位姿后松开鼠标，机器人会自动调整到这个位置。
    
4. 给定导航目标，进行导航
    
    调整完初始状态后，我们就可以对机器人进行导航了。
    
    这次我们要用到 2D Nav Goal 工具，操作和上面相同，在地图的相应地方点击并拖动，点击的位置代表了机器人的目的地，绿色箭头的方向代表了机器人到达目的地后的朝向。
    
    当我们一撒手，机器人就会自动规划路线进行导航啦...
    

### 2.5 无地图导航

在步骤2.2之后，如果想运行根据无地图进行导航程序，那么请运行如下步骤：

1. 运行move_base

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_navigation move_base_mapless_demo.launch
    ```
    
2. 打开 Rviz 用于显示实时建图效果

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_rviz_launchers view_movebase.launch
    ```
    
    详情请参考：http://git.aiiage.com:9000/liu.f/aiibot_rviz_launchers/blob/master/README.md
    
3. 给定导航目标，进行导航
    
    等Rviz打开后，我们就可以直接对机器人进行导航了。
    
    同理，我们要用到 2D Nav Goal 工具，操作和上面相同，在地图的任意地方点击并拖动，点击的位置代表了机器人的目的地，绿色箭头的方向代表了机器人到达目的地后的朝向。
    
    如果机器人在运行过程中发现前方有无法越过的障碍物，或者目的地是处在障碍物中，那么机器人就会暂停，等待你的再次输入！

### 2.6 导航并建图

这一步有点像 步骤2.3 和 步骤2.5 的结合，具体就是边导航，边建图，操作如下：

在步骤2.2之后，如果想运行根据导航并建图程序，那么请运行如下步骤：

1. 运行 move_base

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_navigation move_base_gmapping.launch
    ```
    
2. 打开 Rviz 用于显示实时建图效果

    打开一个新的终端(ctrl+shift+T), 运行如下指令：
    
    ```
    $ roslaunch aiibot_rviz_launchers view_movebase.launch
    ```
    
    详情请参考：http://git.aiiage.com:9000/liu.f/aiibot_rviz_launchers/blob/master/README.md
    
3. 给定导航目标，进行导航
    
    等Rviz打开后，我们就可以直接对机器人进行导航了。
    
    同理，我们要用到 2D Nav Goal 工具，操作和上面相同，在地图的任意地方点击并拖动，点击的位置代表了机器人的目的地，绿色箭头的方向代表了机器人到达目的地后的朝向。
    
    如果机器人在运行过程中发现前方有无法越过的障碍物，或者目的地是处在障碍物中，那么机器人就会暂停，等待你的再次输入！
    
    与 步骤2.5 不同的是在导航过程中，该程序同时运行了Gmapping进行地图的绘制。

### 2.7 保存地图

在执行 步骤2.2 和 步骤2.6 后，我们如果想对所创建的地图进行保存，执行如下操作：

打开新的终端(ctrl+shift+T), 输入：

```
$ rosrun map_server map_saver -f ~/catkin_ws/src/aiibot_navigation/map/aiiage.ymal
```

***
## 版权声明

本文档版权归深圳寒武纪智能科技有限公司所有，并保留一切权利。未经书面许可，任何公司和个人不得将此文档中的任何部分公开、转载或以其他方式散发给第三方。否则，必将追究其法律责任。

*作者：刘发 创建日期：2016/08/16*