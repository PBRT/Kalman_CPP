#ifndef GLOBAL_H // header guards
#define GLOBAL_H
#include "GPS.h"
#include "QR.h"
#include "IMU.h"
#include "Kalman.h"
 
// extern tells the compiler this variable is declared elsewhere
extern GPS *gps_global;
extern GPS *odom_global;
extern GPS *pid_global;

extern QR *qr_global;

extern IMU *imu_global;

extern Kalman *kalman;

extern int Freq;

 
#endif