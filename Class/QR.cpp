#include "../Headers/QR.h"
#include "../Headers/DataReader.h"
#include <iostream>
#include <string>
#include <sys/timeb.h>
#include <stdio.h>

using namespace std;


//Constructeur
QR::QR(std::string n, int s){      
        this->data = new vector <int>(3);   //Contient X, Y et Z ainsi que les Covariances associées
        this->topic_name=n;
        this->sizeMess=s;
        this->reader= new DataReader(this->topic_name,s);
}


//Getteurs
std::vector<int>* QR::getData(){
    return this->data;
}

std::string QR::getTopic(){
    return this->topic_name;
}
DataReader* QR::getDataReader(){
    return this->reader;
}
double QR::getTimeStamp(){
    return this->timeStamp;
}
int QR::getSizeMess(){
    return this->sizeMess;
}

//Setteur 
void QR::setTimeStamp(double val){
    this->timeStamp=val;
}

//Affichage des données dans le buffer
void QR::Display(){

        cout << endl << "-------------> QR data" << endl;
        cout << "Nom du topic à lire : " << this->getTopic() << endl;
       /* for(int i=0; i<3; i++){
                cout << this->getData()->at(i) << endl;
        }*/
        printf("Time stamp de QR : %f\n",this->getTimeStamp() );
        cout << "--------------> Fin QR DATA" << endl << endl;
}

//Recupère les données en provenance du noeud ROS associé
void QR::Acquisition(){
        
        struct timeb end;
        double diff;

        this->reader->Reading(); 
        ftime(&end);

        diff=1000.0*end.time + end.millitm;
        this->setTimeStamp(diff);
        this->Analysis();
        
        
}

//Analyse les données recuent et les converti en entier
void QR::Analysis(){
        
        for(int i=0; i<3; i++){
                 this->getData()->at(i)+=i;
        }

}
