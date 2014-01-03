#include "../Headers/GPS.h"
#include "../Headers/DataReader.h"
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
GPS::GPS(std::string n, int s, std::string t){      
        this->data = new vector <float>(6);   //Contient X, Y et Z ainsi que les Covariances associées
        this->topic_name=n;
        this->sizeMess=s;
        this->reader= new DataReader(this->topic_name,s);
        this->timeStamp=0.0;
        this->type=t;
}


//Getteurs
std::vector<float>* GPS::getData(){
    return this->data;
}
std::string GPS::getType(){
    return this->type;
}

std::string GPS::getTopic(){
    return this->topic_name;
}
DataReader* GPS::getDataReader(){
    return this->reader;
}
double GPS::getTimeStamp(){
    return this->timeStamp;
}
int GPS::getSizeMess(){
    return this->sizeMess;
}
//Setteur 
void GPS::setTimeStamp(double val){
    this->timeStamp=val;
}

//Affichage des données dans le buffer
void GPS::Display(){

        cout << endl << "----->GPS data -----";
        cout << "Nom du topic à lire : " << this->getTopic() << endl;
       /* for(int i=0; i<6; i++){
                cout << this->getData()->at(i) << endl;
        }*/
        printf("Valeur du timeStamp GPS : %f \n", this->getTimeStamp());
        cout << "--------------FIN GPS DATA" << endl << endl;
     
}

//Recupère les données en provenance du noeud ROS associé
void GPS::Acquisition(){
   
        struct timeb end;
        double diff;

        this->reader->Reading(); 
        ftime(&end);

        diff=1000.0*end.time + end.millitm;
        this->setTimeStamp(diff);

        this->Analysis_for_Odometric_Messages();


}

//Analyse les données recuent et les converti en entier
void GPS::Analysis_for_Odometric_Messages(){
        
        //Separation du message recut dans un vecteur
        std::vector<std::string> container = split(this->reader->result, '\n');
        
        float x =  atof(split(container.at(10), ' ').at(7).c_str());
        float y =  atof(split(container.at(11), ' ').at(7).c_str());
        float z =  atof(split(container.at(12), ' ').at(7).c_str());       

        //Covariance
        //X
        std::string cov = split(container.at(18), ' ').at(3).c_str();
        float CovX =  atof(cov.substr(1,cov.size()-2).c_str());

        //Y
        cov = split(container.at(18), ' ').at(10).c_str();
        float CovY =  atof(cov.substr(0,cov.size()-1).c_str());

        //Z
        cov = split(container.at(18), ' ').at(17).c_str();
        float CovZ =  atof(cov.substr(0,cov.size()-1).c_str());

        this->data->at(0)=x;
        this->data->at(1)=y;
        this->data->at(2)=z;
        this->data->at(3)=CovX;
        this->data->at(4)=CovY;
        this->data->at(5)=CovZ;
     
        /*printf("Valeur de x : %f\n", x);
        printf("Valeur de Y : %f\n", y);
        printf("Valeur de Z : %f\n", z); 
        printf("Valeur de covx : %f\n", CovX);
        printf("Valeur de covY : %f\n", CovY);
        printf("Valeur de covZ : %f\n", CovZ);*/


}

std::vector<std::string> GPS::split2(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> GPS::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split2(s, delim, elems);
    return elems;
}
