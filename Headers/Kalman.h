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

        std::vector<std::vector<double> > *P, *Pprec;
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
                std::vector<std::vector<double> > * getP();
                std::vector<std::vector<double> > *getPprec();

                //Setteurs
                void setX(std::vector<double> *);
                void setXprec(std::vector<double> *);
                void setP(std::vector<std::vector<double> > *);
                void setPprec(std::vector<std::vector<double> > *);

                //Filtering
                void Kalman_Filter(std::vector<double> *);
                void matrix_display(double (*A)[3][3], char *name);
};

#endif
