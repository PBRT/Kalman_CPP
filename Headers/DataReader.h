#ifndef DATAREADER_H
#define DATAREADER_H

#include <vector>
#include <string>

class DataReader {

        //Attributs
        public :
        std::string result;         //Buffer des données GPS, contient X,Y,Z et CovX,CovY et CovZ
        std::string topic_name;
        int size_message;               //Taille du message en nombre de lignes
        
        //Fonctions
        public :
                //Constructeur et Destructeur
                DataReader(std::string name, int siz);
                ~DataReader();
                
                //Afichage
                void Display();
                void Reading();


};

#endif
