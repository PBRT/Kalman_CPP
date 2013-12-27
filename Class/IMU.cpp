#include "../Headers/IMU.h"
#include "../Headers/DataReader.h"
#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <sys/timeb.h>
#include <stdlib.h>

#include <fstream>
#include <string>
#include <sstream>
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
        
        //Separation du message recut dans un vecteur
        std::vector<std::string> container = split(this->reader->result, '\n');
        
        //Position-------------------------------------------------
        float x =  atof(split(container.at(7), ' ').at(3).c_str());
        float y =  atof(split(container.at(8), ' ').at(3).c_str());
        float z =  atof(split(container.at(9), ' ').at(3).c_str());       

        //Covariance
        //X
        std::string cov = split(container.at(11), ' ').at(1).c_str();
        float CovX =  atof(cov.substr(1,cov.size()-2).c_str());

        //Y
        cov = split(container.at(11), ' ').at(4).c_str();
        float CovY =  atof(cov.substr(0,cov.size()-1).c_str());

        //Z
        cov = split(container.at(11), ' ').at(7).c_str();
        float CovZ =  atof(cov.substr(0,cov.size()-1).c_str());

        //Vitesse--------------------------------------------------

        float dx =  atof(split(container.at(13), ' ').at(3).c_str());
        float dy =  atof(split(container.at(14), ' ').at(3).c_str());
        float dz =  atof(split(container.at(15), ' ').at(3).c_str());       

        //Covariance
        //X
        cov = split(container.at(16), ' ').at(1).c_str();
        float dCovX =  atof(cov.substr(1,cov.size()-2).c_str());

        //Y
        cov = split(container.at(16), ' ').at(4).c_str();
        float dCovY =  atof(cov.substr(0,cov.size()-1).c_str());

        //Z
        cov = split(container.at(16), ' ').at(7).c_str();
        float dCovZ =  atof(cov.substr(0,cov.size()-1).c_str());

        this->data->at(0)=x;
        this->data->at(1)=y;
        this->data->at(2)=z;
        this->data->at(3)=CovX;
        this->data->at(4)=CovY;
        this->data->at(5)=CovZ;

        this->data_vitesse->at(0)=dx;
        this->data_vitesse->at(1)=dy;
        this->data_vitesse->at(2)=dz;
        this->data_vitesse->at(3)=dCovX;
        this->data_vitesse->at(4)=dCovY;
        this->data_vitesse->at(5)=dCovZ;

     
        printf("Valeur de x IMU: %f\n", dx);
        printf("Valeur de Y IMU: %f\n", dy);
        printf("Valeur de Z IMU: %f\n", dz); 
        printf("Valeur de covx : %f\n", dCovX);
        printf("Valeur de covY : %f\n", dCovY);
        printf("Valeur de covZ : %f\n", dCovZ);


}

std::vector<std::string> IMU::split2(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> IMU::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split2(s, delim, elems);
    return elems;
}
