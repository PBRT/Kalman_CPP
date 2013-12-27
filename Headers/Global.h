#ifndef GLOBAL_H // header guards
#define GLOBAL_H
#include "GPS.h"
#include "QR.h"
#include "IMU.h"
#include "Kalman.h"
 
//Data Reading
extern GPS *gps_global;
extern GPS *odom_global;
extern GPS *pid_global;
extern QR *qr_global;
extern IMU *imu_global;

//Kalman filtering
extern Kalman *kalman;
/*extern std::vector<std::vector<int> > A (3, std::vector<int>(3, 0));
extern std::vector<std::vector<int> > C (3, std::vector<int>(3, 0));
extern std::vector<std::vector<double> > Q (3, std::vector<double>(3, 0));
extern std::vector<std::vector<double> > R (3, std::vector<double>(3, 0));*/
extern int Freq;

 
#endif