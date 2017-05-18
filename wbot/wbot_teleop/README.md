# Aiibot 移动平台键盘控制程序
## 功能说明
本程序实现了通过键盘按键，发布线速度和角速度数据。

具体流程是:
1. 检测用户按键;
2. 根据算法，判断用户逻辑；
3. 生成Topic: /cml_vel 并发布；
4. 等待客户端接受该Topic。

这里我们可以启动Aiibot移动平台，然后监听该Topic，这样就实现了使用键盘控制机器人移动的功能；

启动移动平台请看：http://git.aiiage.com:9000/liu.f/aiibot_bringup

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
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_rplidar.git (可选)
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_teleop.git
$ cd ~/catkin_ws
$ caktin_make
$ source ~/.bashrc
```

执行完毕后，关闭终端

## 2 运行方法：
### 2.1 打开一个终端（ctrl + alt + T），启动ROS环境
```
$ roscore
```

### 2.2 再打开一个终端（ctrl + shift + T），启动底盘程序

连接串口线，打开开关，输入如下指令：

```
$ roslaunch aiibot_bringup base_control.launch
```

具体请参见: http://git.aiiage.com:9000/liu.f/aiibot_bringup/blob/master/README.md

### 2.3 打开第三个终端(Ctrl + Shift + T)，输入如下指令：

```
$ roslaunch aiibot_teleop keyboard_teleop.launch
```

## 3 控制方法：
保持键盘控制程序的终端始终处在选中状态，根据下面的说明，对底盘进行控制

| 按键 | 功能          |
|:----:| ----------    |
|  W   | 前进          | 
|  X   | 后退          | 
|  A   | 向左转        | 
|  D   | 向右转        | 
|  Q   | 向左前方旋转  | 
|  E   | 向右前方旋转  | 
|  Z   | 向左后方旋转  | 
|  C   | 向右后方旋转  | 
|  S   | 急停          |
|----| ----------------      |
|  u   | 增加线速度和角速度  | 
|  i   | 减小线速度和角速度  | 
|  j   | 增加线速度          | 
|  k   | 减少线速度          |
|  m   | 增加角速度          | 
|  ,   | 减少角速度          |


