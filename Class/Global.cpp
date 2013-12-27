#include "../Headers/GPS.h"
#include "../Headers/QR.h"
#include "../Headers/IMU.h"
#include "../Headers/Kalman.h"

//Data Reading
GPS *gps_global= new GPS("foo", 33,"gps");
GPS *odom_global=new GPS("foo3", 33,"odom");		//Odometry message ==> 33 lines
GPS *pid_global=new GPS("foo5", 33,"pid");
QR *qr_global=new QR("foo2",33);
IMU *imu_global=new IMU("foo4",25);


//Kalman filtering
Kalman *kalman = new Kalman(1,1,0.1,0.1);
std::vector<std::vector<int> > A;
std::vector<std::vector<int> > C;
std::vector<std::vector<int> > Q;
std::vector<std::vector<int> > R;

int Freq=20;