#include "../Headers/Kalman.h"
#include "../Headers/Global.h"
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
       this->P=new vector<vector<double> >(3, vector<double>(3));
       this->Pprec=new vector<vector<double> >(3, vector<double>(3));
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

std::vector<std::vector<double> >*  Kalman::getP(){
    return this->P;
}

std::vector<std::vector<double> > * Kalman::getPprec(){
    return this->Pprec;
}

//Setteurs
void Kalman::setX(std::vector<double> * i){
    this->X=i;
}

void Kalman::setXprec(std::vector<double> * i){
    this->Xprec=i;
}

void Kalman::setP(std::vector<std::vector<double> > *i){
    this->P=i;
}

void Kalman::setPprec(std::vector<std::vector<double> > *i){
    this->Pprec=i;
}


//Fonctions

void  Kalman::matrix_display(double (*A)[3][3], char *name){
        int i,j;
        
        printf("%s\n", name);
        for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                        printf(" %f |", (*A)[i][j]);
                }
                printf("\n");
        }
        printf("\n");
}


void Kalman::Kalman_Filter(std::vector<double> *Z){

    //Analyse des mesures (Validité), normalement, changer la matrice C, peut etre déja fait dans la fonction Kalman
    for(int i=0; i<15; i++){
        if(Z->at(i)==-10000){}
           // cout << "Mesure fausse car trop vielle!!!" << endl;
    }

    //Algorithme de Kalman (pour l'instant, simple moyenne)    
    //Matrice A => mat_A;
    //Matrice C => mat_C;
    //Matrice Q => mat_Q;
    //Matrice R => mat_R;
    //Matrice P => mat_P;
    //Matrice P0 => mat_P0;
    //Matrice X => mat_X;
    //Matrice X0 => mat_X0;
    mat_C=mat_A;
    matrix_display(mat_C,"C");

    
    //Mise a jours des Valeurs 
    this->setX(Z);

}
