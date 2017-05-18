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


