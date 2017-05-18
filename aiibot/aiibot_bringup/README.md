# Aiibot 底盘启动程序
## 1 功能说明

该程序包主要实现了启动Aiibot底盘和激光雷达的功能。

1. 关于Aiibot底盘启动程序，主要是封装了串口通信程序:
    - 向下位机传输线速度和角速度
    - 获取下位机传输的码盘数据，并转化成一段时间的位移和旋转角度。
    - 具体传输格式和主要代码请参照：http://git.aiiage.com:9000/algorithm/dev-doc/blob/master/Aiibot.md
    
2. 本程序包直接调用了思岚激光雷达的启动文件，所以如果要想一起启动Aiibot底盘和激光雷达，还需要下载思岚的激光雷达程序包。

    详情请参考：http://git.aiiage.com:9000/liu.f/aiibot_rplidar/tree/master


## 2 编译方法：

### 2.1 创建并初始化 Workspace
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

### 2.2 拷贝工程到 workspace

继续输入如下指令：

```
$ cd ~/catkin_ws/src
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_bringup.git
$ git clone http://git.aiiage.com:9000/liu.f/aiibot_rplidar.git (可选)
$ cd ~/catkin_ws
$ caktin_make
$ source ~/.bashrc
```

执行完毕后，关闭终端

## 3 设置串口权限
串口插入电脑后，往往会由于权限不足，无法进行通信，所以在插入串口之前，我们要对电脑USB端口修改权限，具体代码如下：

```
$ cd /etc/udev/rules.d/
$ sudo touch 50-usb-serial.rules
$ sudo gedit 50-usb-serial.rules
```

写入：KERNEL=="ttyUSB*", MODE="0666"

保存，关闭。

## 4 仅仅启动底盘
1. 插入底盘串口(/ttyUSB0)
2. 打开底盘开关
3. 打开终端(ctrl + alt + T), 运行如下指令： 

    ```
    $ roslaunch aiibot_bringup base_control.launch
    ```

## 5 启动底盘和激光雷达
1. 插入底盘串口(/ttyUSB0)
2. 插入激光雷达串口线(/ttyUSB1)
3. 打开底盘开关
4. 修改激光雷达lanch文件串口为 /ttyUSB1，具体请参照：http://git.aiiage.com:9000/liu.f/aiibot_rplidar/blob/master/README.md
5. 打开终端(ctrl + alt + T), 运行如下指令：

    ```
    $ roslaunch aiibot_bringup run.launch
    ```
    
【注意】在执行上面的指令时，也许会出现没有相关依赖库的错误，当出现错误时，我们只需要使用 sudo apt-get install ros-indigo-*** 的安装指令把所有的依赖库都装上就好了...

## 使用键盘控制小车移动
请参考：http://git.aiiage.com:9000/liu.f/aiibot_teleop/blob/master/README.md

***

## 版权声明

本文档版权归深圳寒武纪智能科技有限公司所有，并保留一切权利。未经书面许可，任何公司和个人不得将此文档中的任何部分公开、转载或以其他方式散发给第三方。否则，必将追究其法律责任。

*作者：刘发 创建日期：2016/08/16*