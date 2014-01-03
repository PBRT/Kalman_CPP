#include "../Headers/PID.h"
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
PID::PID(std::string n, int s, std::string t){      
        this->data_linear = new vector <float>(3);   //Vitesse lineaire X, Y et Z
        this->data_angular = new vector <float>(3);   //Vitesse angulaire X, Y et Z
        this->topic_name=n;
        this->sizeMess=s;
        this->reader= new DataReader(this->topic_name,s);
        this->timeStamp=0.0;
        this->type=t;
}


//Getteurs
std::vector<float>* PID::getDataLinear(){
    return this->data_linear;
}
std::vector<float>* PID::getDataAngular(){
    return this->data_angular;
}
std::string PID::getType(){
    return this->type;
}

std::string PID::getTopic(){
    return this->topic_name;
}
DataReader* PID::getDataReader(){
    return this->reader;
}
double PID::getTimeStamp(){
    return this->timeStamp;
}
int PID::getSizeMess(){
    return this->sizeMess;
}
//Setteur 
void PID::setTimeStamp(double val){
    this->timeStamp=val;
}
void PID::setTopic(std::string val){
    this->topic_name=val;
}

//Affichage des données dans le buffer
void PID::Display(){

        cout << endl << "----->GPS data -----";
        cout << "Nom du topic à lire : " << this->getTopic() << endl;
       /* for(int i=0; i<6; i++){
                cout << this->getData()->at(i) << endl;
        }*/
        printf("Valeur du timeStamp GPS : %f \n", this->getTimeStamp());
        cout << "--------------FIN GPS DATA" << endl << endl;
     
}

//Recupère les données en provenance du noeud ROS associé
void PID::Acquisition(){
   
        struct timeb end;
        double diff;

        this->reader->Reading(); 
        ftime(&end);

        diff=1000.0*end.time + end.millitm;
        this->setTimeStamp(diff);

        //Odometric analysis
        if(this->getType().compare("odom")==0)    
            this->Analysis_for_PID_Messages();

        //GPS analysis
        else if(this->getType().compare("gps")==0)
            this->Analysis_for_PID_Messages();

        //PID analysis
        else if(this->getType().compare("pid")==0)
            this->Analysis_for_PID_Messages();
       

}

//Analyse les données recuent et les converti en entier
void PID::Analysis_for_PID_Messages(){
        
        //Separation du message recut dans un vecteur
        std::vector<std::string> container = split(this->reader->result, '\n');      
        float x =  atof(split(container.at(1), ' ').at(3).c_str());
        float y =  atof(split(container.at(2), ' ').at(3).c_str());
        float z =  atof(split(container.at(3), ' ').at(3).c_str());  

        float xa =  atof(split(container.at(5), ' ').at(3).c_str());
        float ya =  atof(split(container.at(6), ' ').at(3).c_str());
        float za =  atof(split(container.at(7), ' ').at(3).c_str());      

        //Covariance
        //X
        /*std::string cov = split(container.at(18), ' ').at(3).c_str();
        float CovX =  atof(cov.substr(1,cov.size()-2).c_str());

        //Y
        cov = split(container.at(18), ' ').at(10).c_str();
        float CovY =  atof(cov.substr(0,cov.size()-1).c_str());

        //Z
        cov = split(container.at(18), ' ').at(17).c_str();
        float CovZ =  atof(cov.substr(0,cov.size()-1).c_str());*/

        this->data_linear->at(0)=x;
        this->data_linear->at(1)=y;
        this->data_linear->at(2)=z;
        this->data_angular->at(0)=xa;
        this->data_angular->at(1)=ya;
        this->data_angular->at(2)=za;
     /*
        printf("Valeur de x : %f\n", this->data_linear->at(0));
        printf("Valeur de Y : %f\n", this->data_linear->at(1));
        printf("Valeur de Z : %f\n", this->data_linear->at(2)); */
    


}

std::vector<std::string> PID::split2(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> PID::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split2(s, delim, elems);
    return elems;
}
