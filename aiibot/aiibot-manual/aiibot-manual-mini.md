# Aiibot  操作手册精简版

- 先插入底盘串口线

- 再插入激光雷达串口线

- 打开第一个终端(Ctrl+Alt+T)，输入
   ```
   $ roscore
   ```
   
- 打开第二个终端(Ctrl+Shift+T), 分成上下左右四块, 第一块中输入
   ```
   $ roslaunch aiibot_bringup run.launch
   ```
   
## Gmapping 建图程序

- 在第二块中输入：
	```
	$ roslaunch aiibot_navigation gmapping_demo.launch
	```
	
- 在第三块中输入:
	```
	$ roslaunch aiibot_rviz_launchers view_gmapping.launch
	```
	
- 在第四块中输入：
	```
	$ roslaunch aiibot_teleop keyboard_teleop.launch
	```
	
## Amcl 带地图导航程序

- 在第二块中输入：
	```
	$ roslaunch aiibot_navigation amcl_demo.launch
	```
	
- 在第三块中输入:
	```
	$ roslaunch aiibot_rviz_launchers view_amcl.launch
	```
	
- 使用 Rviz 工具栏中 2D Pose Estime 工具进行初始位置修正

- 使用 Rviz 工具栏中 2D Nav Goal 工具给定目的地

## Move_base 无地图导航

- 在第二块中输入：
	```
	$ roslaunch aiibot_navigation move_base_mapless_demo.launch
	```
	
- 在第三块中输入:
	```
	$ roslaunch aiibot_rviz_launchers view_movebase.launch
    ```
    
- 使用 Rviz 工具栏中 2D Nav Goal 工具给定目的地

## Move_base 无地图导航并建图

- 在第二块中输入：
	```
	$ roslaunch aiibot_navigation move_base_gmapping.launch
	```
	
- 在第三块中输入:
	```
	$ roslaunch aiibot_rviz_launchers view_movebase.launch
    ```
    
- 使用 Rviz 工具栏中 2D Nav Goal 工具给定目的地

## 保存地图

- 打开一个新的终端(Ctrl+Shift+T)，输入

    ```
    rosrun map_server map_saver -f ~/aiibot_ws/src/aiibot_navigation/maps/aiiage_map
    ```

***
## 版权声明

本文档版权归深圳寒武纪智能科技有限公司所有，并保留一切权利。未经书面许可，任何公司和个人不得将此文档中的任何部分公开、转载或以其他方式散发给第三方。否则，必将追究其法律责任。

*作者：刘发 创建日期：2016/08/16*