#ifndef KALMAN_H
#define KALMAN_H

#include <vector>
#include <string>
#include <time.h>
#include <ctime>

class Kalman {

        //Attributs
        private :

        //Kalman attributes
        int A;
        int C;
        double Q;
        double R;

        double P,Pprec;
        std::vector<double> *X, *Xprec;

        
        //Fonctions
        public :
                //Constructeur et Destructeur
                Kalman(int, int, double, double);
                ~Kalman();

                //Getteurs
                int getA();
                std::vector<double> *getX();
                std::vector<double> *getXprec();
                double getP();
                double getPprec();

                //Setteurs
                void setX(std::vector<double> *);
                void setXprec(std::vector<double> *);
                void setP(double);
                void setPprec(double);

                //Filtering
                void Kalman_Filter(std::vector<double> *);
};

#endif
