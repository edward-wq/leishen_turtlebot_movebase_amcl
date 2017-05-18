# Aiibot 使用说明书
***

### [Aiibot 操作指南（简易版）](http://git.aiiage.com:9000/liu.f/aiibot-manual/blob/master/aiibot-manual-mini.md)

***

### [Aiibot 操作指南（详细版）](http://git.aiiage.com:9000/liu.f/aiibot_navigation)

***

### [Aiibot 移动平台源码调用方法](http://git.aiiage.com:9000/algorithm/dev-doc/blob/master/Aiibot.md)

***

### Aiibot 硬件参数

| **器材** | **参数** |
| ---  | ---- |
| 激光雷达| 思岚 A1，探测范围 0.2m ~ 6m |
| 电机|  2个有刷直流电机| 
| 万向轮 | 一个 |  
| 深度相机 | 华硕 xtion | 
| 下位机底盘 |  STM32f103 | 
| 串口线+串口 | 1个 |
| 最大线速度 | 0.8 m/s | 
| 最大角速度 | 1 rad/s | 
| 最大载重 | 约6kg | 
| 健康电压 | 10v ~ 12v |

***

### Aiibot 使用过程中的注意事项
1. 当电池电压小于10V时，需要及时充电，具体请询问硬件组；
2. 串口线如果不慎拔掉，需要咨询硬件组，在不熟悉的情况下不可自行插入，不然会烧坏串口USB；
3. 由于Aiibot没有越障能力，所以在操作时尽量远离不平整的地面；
4. Aiibot 周围的不干胶是为了防止底盘刮伤人和固定电线，所以如果开胶，还请再次粘上；
5. Aiibot 下位机程序已经交接，如果要对下位机程序进行修改，比如PID等，需要在Windows环境下，把修改好的下位机程序烧到下位机底盘上，程序的具体烧制和使用方法请询问硬件组；
6. 现在Aiibot使用的是思岚激光雷达A1, 今后如果更换其他的激光雷达，在安装过程中，需要保持激光雷达的正方向和Aiibot的正方向相反（涉及到坐标变换的问题，当然也可以在软件层面进行修改）；
7. 激光雷达参数，Gmapping建图参数，move_base导航参数等的修改还请参见各个程序包；
8. 插入串口线时，要记得先插入底盘串口线，再插入激光雷达串口线，然后再打开开关；
9. 当不使用Aiibot时，请记得关闭开关;
10. 最后一条，无论今后是谁接手我的工作, 还请 **照顾好 Aiibot** ..........

***

### 各程序包相互关系图

![image](http://git.aiiage.com:9000/liu.f/aiibot-manual/raw/master/images/frame.jpg)


