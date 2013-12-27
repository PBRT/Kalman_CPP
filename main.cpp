#include <iostream>
#include "Headers/GPS.h"
#include "Headers/DataReader.h"
#include "Headers/QR.h"
#include "Headers/Kalman.h"
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

//Thread QR Code
void *threadQR(void *obj){

        QR *qr = (QR*)obj;
        //Reading loop
        while(1)
            qr->Acquisition();

        return NULL;
}

void *threadIMU(void *obj){
        
        IMU *imu = (IMU*)obj;
        //Reading loop
        while(1)
                imu->Acquisition();

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
        std::vector<double> *Z = new vector<double>(6);

        struct timeb end2;
        double diff2;

        ofstream myfile;
        myfile.open("Kalman_Results.txt");

        //Lecture des données péridiquement
        while(1){

                //Read
                cout << "----Aquisition et lecture buffers numero "<<i<<": " << endl; 
                printf("-------> GPS : TimeStamp : %f Value : %f \n", gps_global->getTimeStamp(), gps_global->getData()->at(1));
                printf("-------> ODOM : TimeStamp : %f Value : %f \n", odom_global->getTimeStamp(), odom_global->getData()->at(0));
               // printf("-------> QRCODE : TimeStamp : %f Value : %d \n", qr_global->getTimeStamp(), qr_global->getData()->at(1));
                //printf("-------> IMU : TimeStamp : %f Value : %d \n", imu_global->getTimeStamp(), imu_global->getData()->at(1));
               // printf("-------> PID : TimeStamp : %f Value : %d \n\n", pid_global->getTimeStamp(), pid_global->getData()->at(1)); 
                
                //Acquisition du temps
                ftime(&end2);
                diff2=1000.0*end2.time + end2.millitm;
                printf(" === Temps courant : %f \n\n", diff2);

                //Contruction du vecteur de mesures Z en verifiant la validité

                //Odometry
                Z->at(0)=checkTimeStamp(diff2,odom_global->getTimeStamp(), odom_global->getData()->at(0));
                Z->at(1)=checkTimeStamp(diff2,odom_global->getTimeStamp(), odom_global->getData()->at(1));
                Z->at(2)=checkTimeStamp(diff2,odom_global->getTimeStamp(), odom_global->getData()->at(2));

                //GPS
                Z->at(3)=checkTimeStamp(diff2,gps_global->getTimeStamp(), gps_global->getData()->at(0));
                Z->at(4)=checkTimeStamp(diff2,gps_global->getTimeStamp(), gps_global->getData()->at(1));
                Z->at(5)=checkTimeStamp(diff2,gps_global->getTimeStamp(), gps_global->getData()->at(2));
                
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
                myfile << i<<" " << kalman->getX()->at(0) << " " << kalman->getX()->at(1) << " " << kalman->getX()->at(2) << " " << kalman->getX()->at(3)<< " " << kalman->getX()->at(4)<< " " << kalman->getX()->at(5) << endl;
                
        }

        myfile.close();


        return NULL;
}



int main(){

         //Frequence des itération du Kalman et de relevé des mesures en ms       
        //Freq=1000*Freq; //Conversion en usecondes
       
         pthread_t t1,t2,t3,t4,t5,t6;
         pthread_create(&t1,NULL,&threadGPS,gps_global);
         //pthread_create(&t2,NULL,&threadQR,qr_global);
         pthread_create(&t3,NULL,&threadGPS,odom_global);
        // pthread_create(&t4,NULL,&threadIMU,imu_global);
       //  pthread_create(&t5,NULL,&threadGPS,pid_global);

         pthread_create(&t6,NULL,&threadGlobal,NULL);

         //Join for the main will not stop until all threads are overs
         //pthread_join(t3,NULL);
         //pthread_join(t6,NULL);
   
         //For plotting, comment join and uncomment sleep
         sleep(10);
         
                //Plotting of results
        FILE *gnuplot = popen("gnuplot -persist", "w");
        fprintf(gnuplot, "load \"Plotting/config\"\n");
        fflush(gnuplot);

        //TO DO      

        //Decodage des trames recuent => QR/GPS/IMU/PID (demander format trames)
        //Arriver a publier les chiffres !!

        return 0;

}