#include "../Headers/Kalman.h"
#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <sys/timeb.h>

#include <stdlib.h>
#include <pthread.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdlib>
using namespace std;


//Constructeur
Kalman::Kalman(int a, int c, double q, double r){      
       this->A=a;
       this->C=c;
       this->Q=q;
       this->R=r;
       this->X = new vector<double>(3);   
       this->Xprec = new vector<double>(3);   
      // this->X=0.0;
      // this->Xprec=0.0;
       this->P=0.0;
       this->Pprec=0.0;
}


//Getteurs
int Kalman::getA(){
    return this->A;
}

std::vector<double> * Kalman::getX(){
    return this->X;
}

std::vector<double> * Kalman::getXprec(){
    return this->Xprec;
}

double Kalman::getP(){
    return this->P;
}

double Kalman::getPprec(){
    return this->Pprec;
}

//Setteurs
void Kalman::setX(std::vector<double> * i){
    this->X=i;
}

void Kalman::setXprec(std::vector<double> * i){
    this->Xprec=i;
}

void Kalman::setP(double i){
    this->P=i;
}

void Kalman::setPprec(double i){
    this->Pprec=i;
}

//Fonctions

void Kalman::Kalman_Filter(std::vector<double> *Z){

    //Analyse des mesures (Validité), normalement, changer la matrice C, peut etre déja fait dans la fonction Kalman
    for(int i=0; i<6; i++){
        if(Z->at(i)==-10000)
            cout << "Mesure fausse car trop vielle!!!" << endl;
    }

    //Algorithme de Kalman (pour l'instant, simple moyenne)    


    //Mise a jours des Valeurs 
    this->setX(Z);

}
