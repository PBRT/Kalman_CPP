#include <iostream>
#include "Headers/GPS.h"
#include "Headers/PID.h"
#include "Headers/DataReader.h"
#include "Headers/Kalman.h"
#include "Headers/Initializer.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <pthread.h>
#include "Headers/Global.h"
#include <sstream>
#include <fstream>
#include <math.h>
#include <sys/timeb.h>

using namespace std;

//Threads d'acquisition

//Thread GPS
void *threadGPS(void *obj){

        GPS *gps = (GPS*)obj;
        //Reading loop
        while(1)  
            gps->Acquisition();

        return NULL;
}

void *threadIMU(void *obj){
        
        IMU *imu = (IMU*)obj;
        //Reading loop
        while(1)
                imu->Acquisition();

        return NULL;

}

void *threadPID(void *obj){
        
        PID *pid = (PID*)obj;
        //Reading loop
        while(1)
                pid->Acquisition();

        return NULL;

}

//Check data validity
//If valid, return the value
//If unvalid, return -10000
double checkTimeStamp(double ta, double tb, double val){
    
    double var = -10000;
    if((ta-tb)<Freq)
        return val;
    else
        return var;
}

//Thread global
void *threadGlobal(void *o){

        //int *freq = (int*)o;
        int i=0;
        std::vector<double> *Z = new vector<double>(15);

        struct timeb end2;
        double diff2;

        ofstream myfile;
        myfile.open("Kalman_Results.txt");

        //Lecture des données péridiquement
        while(1){

                //Read
               /* cout << "----Aquisition et lecture buffers numero "<<i<<": " << endl; 
                printf("-------> GPS : TimeStamp : %f Value : %f \n", gps_global->getTimeStamp(), gps_global->getData()->at(1));
                printf("-------> ODOM : TimeStamp : %f Value : %f \n", odom_global->getTimeStamp(), odom_global->getData()->at(0));
                printf("-------> QRCODE : TimeStamp : %f Value : %f \n", qr_global->getTimeStamp(), qr_global->getData()->at(1));
                printf("-------> IMU : TimeStamp : %f Value : %d \n", imu_global->getTimeStamp(), imu_global->getData()->at(1));
                printf("-------> PID : TimeStamp : %f Value : %f \n\n", pid_global->getTimeStamp(), pid_global->getDataLinear()->at(1)); 
                */
                //Acquisition du temps
                ftime(&end2);
                diff2=1000.0*end2.time + end2.millitm;
               // printf(" === Temps courant : %f \n\n", diff2);

                //Contruction du vecteur de mesures Z en verifiant la validité

                //Odometry
                Z->at(0)=checkTimeStamp(diff2,odom_global->getTimeStamp(), odom_global->getData()->at(0));
                Z->at(1)=checkTimeStamp(diff2,odom_global->getTimeStamp(), odom_global->getData()->at(1));
                Z->at(2)=checkTimeStamp(diff2,odom_global->getTimeStamp(), odom_global->getData()->at(2));

                //GPS
                Z->at(3)=checkTimeStamp(diff2,gps_global->getTimeStamp(), gps_global->getData()->at(0));
                Z->at(4)=checkTimeStamp(diff2,gps_global->getTimeStamp(), gps_global->getData()->at(1));
                Z->at(5)=checkTimeStamp(diff2,gps_global->getTimeStamp(), gps_global->getData()->at(2));

                //IMU
                Z->at(6)=checkTimeStamp(diff2,imu_global->getTimeStamp(), imu_global->getData()->at(0));
                Z->at(7)=checkTimeStamp(diff2,imu_global->getTimeStamp(), imu_global->getData()->at(1));
                Z->at(8)=checkTimeStamp(diff2,imu_global->getTimeStamp(), imu_global->getData()->at(2));

                //PID
                Z->at(9)=checkTimeStamp(diff2,pid_global->getTimeStamp(), pid_global->getDataLinear()->at(0));
                Z->at(10)=checkTimeStamp(diff2,pid_global->getTimeStamp(), pid_global->getDataLinear()->at(1));
                Z->at(11)=checkTimeStamp(diff2,pid_global->getTimeStamp(), pid_global->getDataLinear()->at(2));

                //QR
                Z->at(12)=checkTimeStamp(diff2,qr_global->getTimeStamp(), qr_global->getData()->at(0));
                Z->at(13)=checkTimeStamp(diff2,qr_global->getTimeStamp(), qr_global->getData()->at(1));
                Z->at(14)=checkTimeStamp(diff2,qr_global->getTimeStamp(), qr_global->getData()->at(2));
                
                //Filtrage de kalman
                kalman->Kalman_Filter(Z);
                i++; 

                //Echantillonage des mesures  
                usleep(1000*Freq);        


                //Publishing                
               /* std::string cmd="rostopic pub -r 1 vo std_msgs/String \"";
                cmd+=gps_global->getTopic();
                cmd+="\"";
                system(cmd.c_str());*/

                //Plotting
                myfile << i<<" " << kalman->getX()->at(0) << " " << kalman->getX()->at(1) << " " << kalman->getX()->at(2) << " " << kalman->getX()->at(3)<< " " << kalman->getX()->at(4)<< " " << kalman->getX()->at(5) << " " << kalman->getX()->at(6) << " " << kalman->getX()->at(7)<< " " << kalman->getX()->at(8) << " " << kalman->getX()->at(9) << " " << kalman->getX()->at(10)<< " " << kalman->getX()->at(11) << " " << kalman->getX()->at(12) << " " << kalman->getX()->at(13) << " " << kalman->getX()->at(14) <<  endl;
                
        }

        myfile.close();


        return NULL;
}


int main(){

        //Initialisation des variables (matrices et topics) depuis un fichier texte
        Initializer *initi = new Initializer("Model.txt");
        cout << "Fichier d'initialisation : " << initi->getFileName() << endl;

        //Threads
        pthread_t t1,t2,t3,t4,t5,t6;
        pthread_create(&t1,NULL,&threadGPS,gps_global);
        pthread_create(&t2,NULL,&threadGPS,qr_global);
        pthread_create(&t3,NULL,&threadGPS,odom_global);
        pthread_create(&t4,NULL,&threadIMU,imu_global);
        pthread_create(&t5,NULL,&threadPID,pid_global);

        pthread_create(&t6,NULL,&threadGlobal,NULL);

         //Join for the main will not stop until all threads are overs
         //pthread_join(t3,NULL);
         //pthread_join(t6,NULL);
   
         //For plotting, comment join and uncomment sleep
         sleep(15);
         
        //Plotting of results
        FILE *gnuplot = popen("gnuplot -persist", "w");
        fprintf(gnuplot, "load \"Plotting/config\"\n");
        fflush(gnuplot);

        return 0;
}
