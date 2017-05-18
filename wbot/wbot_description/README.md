# 该项目是 Aiibot 移动平台3D模型
## 功能说明

该程序包实现了Aiibot3D模型的封装，用户可以在Rviz中查看虚拟Aiibot的3D模型。

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
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_description.git
$ cd ~/catkin_ws
$ caktin_make
$ source ~/.bashrc
```

执行完毕后，关闭终端

## 2 查看机器人模型
1. 打开一个终端(ctrl + alt + T), 启动ros开发环境
```
$ roscore
```

2. 再打开一个终端(ctrl + shift + T), 运行如下指令，打开3D模型：
```
$ roslaunch aiibot_description description.launch
```

***

## 附加提醒
- 机器人3D模型是用URDF格式文件编写
- base frame: base_link
- kinect相机高度待确定
- 查看模型需要RVIZ支持



