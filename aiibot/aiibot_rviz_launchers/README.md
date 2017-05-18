# Aiibot Rviz 显示程序

该程序包主要功能是辅助Aiibot导航程序进行可视化显示。没有核心代码，所以不需要编译等操作。

具体导航功能请参考：http://git.aiiage.com:9000/liu.f/aiibot_navigation/blob/master/README.md

## 显示机器人
```
$ roslaunch aiibot_rviz_launchers view_model.launch
```

## 使用Aiibot进行建图
```
$ roslaunch aiibot_rviz_launchers view_gmapping.launch
```

## 根据已有地图进行导航
```
$ roslaunch aiibot_rviz_launchers view_amcl.launch
```

## 无地图导航
```
$ roslaunch aiibot_rviz_launchers view_amcl.launch
```

## 查看TF转化
```
$ roslaunch aiibot_rviz_launchers view_tf.launch
```


***
## 版权声明

本文档版权归深圳寒武纪智能科技有限公司所有，并保留一切权利。未经书面许可，任何公司和个人不得将此文档中的任何部分公开、转载或以其他方式散发给第三方。否则，必将追究其法律责任。

作者：刘发 创建日期：2016/08/16