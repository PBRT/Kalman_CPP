#ifndef IMU_H
#define IMU_H

#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include "DataReader.h"

class IMU {

        //Attributs
        private :
        std::vector<int> *data;         //Buffer des données GPS, contient X,Y,Z et CovX,CovY et CovZ
        std::vector<int> *data_vitesse;         //Buffer des données GPS, contient vitesse X,Y,Z et CovX,CovY et CovZ
        std::string topic_name;
        DataReader *reader;
        double timeStamp;
        int sizeMess;
        
        //Fonctions
        public :
                //Constructeur et Destructeur
                IMU(std::string name, int s);
                ~IMU();

                //Getteurs
                std::vector<int>* getData();
                std::vector<int>* getVitesse();
                std::string getTopic();
                DataReader* getDataReader();
                double getTimeStamp();
                int getSizeMess();

                //Setteurs
                void setTimeStamp(double);
                
                //Afichage
                void Display();
                void Acquisition();
                void Analysis();


};

#endif
