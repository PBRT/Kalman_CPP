#ifndef QR_H
#define QR_H

#include <vector>
#include <string>

#include "DataReader.h"

class QR {

        //Attributs
        private :
        std::vector<int> *data;         //Buffer des données GPS, contient X,Y,Z et CovX,CovY et CovZ
        std::string topic_name;
        DataReader *reader;
        double timeStamp;
        int sizeMess;
        
        //Fonctions
        public :
                //Constructeur et Destructeur
                QR(std::string name, int s);
                ~QR();

                //Getteurs
                std::vector<int>* getData();
                std::string getTopic();
                double getTimeStamp();
                DataReader* getDataReader();
                int getSizeMess();

                //Setteurs
                void setTimeStamp(double);

                
                //Afichage
                void Display();
                void Acquisition();
                void Analysis();


};

#endif
