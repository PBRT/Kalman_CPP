#ifndef GLOBAL_H // header guards
#define GLOBAL_H
#include "GPS.h"
#include "IMU.h"
#include "Kalman.h"
#include "PID.h"
 
//Data Reading
extern GPS *gps_global;
extern GPS *odom_global;
extern PID *pid_global;
extern GPS *qr_global;
extern IMU *imu_global;

//Kalman filtering
extern Kalman *kalman;
extern double (*mat_A)[3][3];
extern double (*mat_C)[3][3];
extern double (*mat_R)[3][3];
extern double (*mat_Q)[3][3];
extern double (*mat_P)[3][3];
extern double (*mat_P0)[3][3];

extern double (*mat_X0)[6];
extern double (*mat_X)[6];

extern int Freq;

 
#endif