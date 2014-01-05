#include "../Headers/GPS.h"
#include "../Headers/IMU.h"
#include "../Headers/PID.h"
#include "../Headers/Kalman.h"

//Data Reading
GPS *gps_global= new GPS("foo", 33,"gps");
GPS *odom_global=new GPS("foo3", 33,"odom");		//Odometry message ==> 33 lines
PID *pid_global=new PID("foo5", 33,"pid");
GPS *qr_global=new GPS("foo2",33, "qrcode");
IMU *imu_global=new IMU("foo4",25);


//Kalman filtering
Kalman *kalman = new Kalman(1,1,0.1,0.1);
double *mat_A[3][3]={{0,0,0},{0,0,0},{0,0,0}};
double *mat_C[3][3]={{0,0,0},{0,0,0},{0,0,0}};
double *mat_R[3][3]={{0,0,0},{0,0,0},{0,0,0}};
double *mat_Q[3][3]={{0,0,0},{0,0,0},{0,0,0}};
double *mat_P0[3][3]={{0,0,0},{0,0,0},{0,0,0}};
double *mat_P[3][3]={{0,0,0},{0,0,0},{0,0,0}};

double *mat_X0[6]={0};
double *mat_X[6]={0};


int Freq=20;