#ifndef INITIAL_H
#define INITIAL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Initializer {

        //Attributs
        private :

        //Kalman attributes
        std::string file_name;
        
        //Fonctions
        public :
                //Constructeur et Destructeur
                Initializer(std::string);
                ~Initializer();

                //Getteurs
                std::string getFileName();

                //Function
                void DataCollect();
                std::vector<std::string> split2(const std::string &s, char delim, std::vector<std::string> &elems);
                std::vector<std::string> split(const std::string &s, char delim);
                void matrix_display(double (*A)[3][3], char *name);
                void matrix_display_X(double (*A)[6], char *name);
};

#endif
