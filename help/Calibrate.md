# Calibrate Mowgli's Magnetometer

From a X11 session run

```
~/MowgliBase/scripts/start_imu_calibrate.sh
```

* Provide your True Field Strength (in nano Tesla !)

  Visit [https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml](https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#igrfwmm)
  Select "Magnetic Field" and provide your GPS coords. From the resulting popup chose the Total Field in nT      

* Click "Start" to record samples from Mowglis Magentometer 
* You should see the Points counter starting to count up
* Whirl Mowgli around all axes, the number of rotations is not important one per axis is sufficient
* Press the 'Calibrate' button
* Admire the charts - you should get a sphere that is centered on 0,0,0
* Press 'Save to FLASH' - this can take a bit, and when done Mowgli should reboot (watch for the tripple chirp)


Thats it, Mowgli's Magnetometer topic should now return useful data.


## Troubleshooting

When Mowgli (stm32) boots you can use 'debug' via serial console to see the values that are applied.

You can also use the [Scripts](https://github.com/cloudn1ne/MowgliRover/tree/main/src/mowgli/scripts/cfg) that come with [MowgliRover](https://github.com/cloudn1ne/MowgliRover) to backup and restore those settings if needed. (Handy while testing indoors vs. outdoors)


## Testing calibration

Make sure MowgliRover is running ./scripts/start_mowgli.sh so that the IMU and ODOM stack is available.

Then run

```
~/MowgliBase/scripts/show_heading_all.py
```

You should see output simliar as below.

Upon start this script will zero any offsets reported by MAG, ODOM or IMU.

So it is mostly meant to check if turn XXdeg to see if MAG, ODOM, IMU properl follows.

Signs might be differnt due to the offset cancelation. 

MAG captured
ODOM captured
IMU captured
MAG (/imu/mag): 0.000 	ODOM (/odom): 0.000 	IMU (/imu/data): 0.000
MAG (/imu/mag): 0.047 	ODOM (/odom): -0.631 	IMU (/imu/data): -0.631
MAG (/imu/mag): -0.344 	ODOM (/odom): 0.044 	IMU (/imu/data): 0.044
MAG (/imu/mag): -0.561 	ODOM (/odom): -0.558 	IMU (/imu/data): -0.558
MAG (/imu/mag): -0.033 	ODOM (/odom): 0.003 	IMU (/imu/data): 0.003
MAG (/imu/mag): 1.139 	ODOM (/odom): -0.670 	IMU (/imu/data): -0.670
MAG (/imu/mag): 0.821 	ODOM (/odom): 0.258 	IMU (/imu/data): 0.258
MAG (/imu/mag): 0.798 	ODOM (/odom): -0.334 	IMU (/imu/data): -0.334
MAG (/imu/mag): -1.444 	ODOM (/odom): 0.375 	IMU (/imu/data): 0.375
MAG (/imu/mag): -1.824 	ODOM (/odom): -0.381 	IMU (/imu/data): -0.381
MAG (/imu/mag): -0.890 	ODOM (/odom): 0.196 	IMU (/imu/data): 0.196
MAG (/imu/mag): -1.064 	ODOM (/odom): -0.492 	IMU (/imu/data): -0.492
MAG (/imu/mag): -0.499 	ODOM (/odom): 0.111 	IMU (/imu/data): 0.111
MAG (/imu/mag): 0.157 	ODOM (/odom): -0.568 	IMU (/imu/data): -0.568
MAG (/imu/mag): -0.637 	ODOM (/odom): 0.135 	IMU (/imu/data): 0.135
MAG (/imu/mag): 0.588 	ODOM (/odom): -0.546 	IMU (/imu/data): -0.546
MAG (/imu/mag): 0.126 	ODOM (/odom): 0.175 	IMU (/imu/data): 0.175
