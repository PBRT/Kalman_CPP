#ifndef GPS_H
#define GPS_H

#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include "DataReader.h"

class GPS {

        //Attributs
        private :
        std::vector<float> *data;         //Buffer des données GPS, contient X,Y,Z et CovX,CovY et CovZ
        std::string topic_name;
        DataReader *reader;
        double timeStamp;
        int sizeMess;     
        std::string type;
        
        //Fonctions
        public :
                //Constructeur et Destructeur
                GPS(std::string name, int s,std::string t);
                ~GPS();

                //Getteurs
                std::string getType();
                std::vector<float>* getData();
                std::string getTopic();
                DataReader* getDataReader();
                double getTimeStamp();
                int getSizeMess();

                //Setteurs
                void setTimeStamp(double);
                
                //Afichage
                void Display();
                void Acquisition();
                void Analysis_for_Odometric_Messages();

                std::vector<std::string> split2(const std::string &s, char delim, std::vector<std::string> &elems);
                std::vector<std::string> split(const std::string &s, char delim);


};

#endif
