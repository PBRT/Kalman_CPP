#ifndef PID_H
#define PID_H

#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include "DataReader.h"

class PID {

        //Attributs
        private :
        std::vector<float> *data_linear;         //Buffer des données PID, vitesse linéaire
        std::vector<float> *data_angular;         //Buffer des données PID, vitesse linéaire
        std::string topic_name;
        DataReader *reader;
        double timeStamp;
        int sizeMess;     
        std::string type;
        
        //Fonctions
        public :
                //Constructeur et Destructeur
                PID(std::string name, int s,std::string t);
                ~PID();

                //Getteurs
                std::string getType();
                std::vector<float>* getDataLinear();
                std::vector<float>* getDataAngular();
                std::string getTopic();
                DataReader* getDataReader();
                double getTimeStamp();
                int getSizeMess();

                //Setteurs
                void setTimeStamp(double);
                void setTopic(std::string);
                
                //Afichage
                void Display();
                void Acquisition();
                void Analysis_for_PID_Messages();

                std::vector<std::string> split2(const std::string &s, char delim, std::vector<std::string> &elems);
                std::vector<std::string> split(const std::string &s, char delim);


};

#endif
