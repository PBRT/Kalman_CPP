#include "../Headers/DataReader.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

DataReader::DataReader(std::string n, int siz){      
        this->result="";
        this->topic_name=n;
        this->size_message=siz;
}

//Affichage des données dans le buffer
void DataReader::Display(){

        cout << "Nom du topic à lire : " << this->topic_name << endl;     
        cout << this->result << endl;       

}

void DataReader::Reading(){

    std::string cmd= "rostopic echo /"+this->topic_name;
    FILE *pipe = popen(cmd.c_str(),"r");
    char buf[128];
    std::string res="";
       
    int i=1;
    while((!feof(pipe))&&(i<this->size_message)){
        if(fgets(buf, 128, pipe) != NULL){
                res += buf;              
                i++;
        }        
    }
    this->result=res;
    pclose(pipe);

}
