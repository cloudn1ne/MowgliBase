
### Add the MowgliBase Workspace setup.bash to your .bashrc

```
echo "source ~/MowgliBase/devel/setup.bash " >> ~/.bashrc
. ~/.bashrc
```


### ROS requirements

```
sudo apt-get install -y ros-noetic-sensor-msgs-ext
```

### Qt requirements (for the IMU GUI)

```
sudo apt-get install -y build-essential qtcreator qt5-default libqt5datavisualization5-dev libqt5charts5-dev
```
