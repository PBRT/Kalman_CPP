#include "../Headers/IMU.h"
#include "../Headers/DataReader.h"
#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <sys/timeb.h>

using namespace std;


//Constructeur
IMU::IMU(std::string n, int s){      
        this->data = new vector <int>(6);   //Contient X, Y et Z ainsi que les Covariances associées
        this->data_vitesse = new vector <int>(6);   //Contient vitesses X, Y et Z ainsi que les Covariances associées
        this->topic_name=n;
        this->sizeMess=s;
        this->reader= new DataReader(this->topic_name, s);
        this->timeStamp=0.0;
}


//Getteurs
std::vector<int>* IMU::getData(){
    return this->data;
}
std::vector<int>* IMU::getVitesse(){
    return this->data_vitesse;
}

std::string IMU::getTopic(){
    return this->topic_name;
}
DataReader* IMU::getDataReader(){
    return this->reader;
}
double IMU::getTimeStamp(){
    return this->timeStamp;
}
int IMU::getSizeMess(){
    return this->sizeMess;
}
//Setteur 
void IMU::setTimeStamp(double val){
    this->timeStamp=val;
}

//Affichage des données dans le buffer
void IMU::Display(){

        cout << endl << "----->IMU data -----";
        cout << "Nom du topic à lire : " << this->getTopic() << endl;
       /* for(int i=0; i<6; i++){
                cout << this->getData()->at(i) << endl;
        }*/
        printf("Valeur du timeStamp IMU : %f \n", this->getTimeStamp());
        cout << "--------------FIN IMU DATA" << endl << endl;
     
}

//Recupère les données en provenance du noeud ROS associé
void IMU::Acquisition(){
   
        struct timeb end;
        double diff;

        this->reader->Reading(); 
        ftime(&end);

        diff=1000.0*end.time + end.millitm;
        this->setTimeStamp(diff);
        this->Analysis();
        
        
}

//Analyse les données recuent et les converti en entier
void IMU::Analysis(){
        
        for(int i=0; i<6; i++){
                 this->getData()->at(i)+=i;
                 this->getVitesse()->at(i)+=(50+i);
        }

}
