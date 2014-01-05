#include "../Headers/Initializer.h"
#include "../Headers/Global.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


//Constructeur
Initializer::Initializer(string n){      
       this->file_name=n;
       this->DataCollect();
}

//Getteurs
string Initializer::getFileName(){
    return this->file_name;
}

std::vector<std::string> Initializer::split2(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Initializer::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split2(s, delim, elems);
    return elems;
}

void  Initializer::matrix_display(double (*A)[3][3], char *name){
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

void  Initializer::matrix_display_X(double (*A)[6], char *name){
        int j;
        
        printf("%s\n", name);
     
                for(j=0;j<6;j++){
                        printf(" %f |", (*A)[j]);
                }
                printf("\n");
    
        printf("\n");
}

void Initializer::DataCollect(){

		ifstream file("Model.txt");;
        std::string str;
        std::string file_contents;
       
        
        //Kalman model
        double A[3][3]={{0,0,0},{0,0,0},{0,0,0}};
        double C[3][3]={{0,0,0},{0,0,0},{0,0,0}};
        double R[3][3]={{0,0,0},{0,0,0},{0,0,0}};
        double Q[3][3]={{0,0,0},{0,0,0},{0,0,0}};
        double P0[3][3]={{0,0,0},{0,0,0},{0,0,0}};
        double X0[6]={0,0,0,0,0,0};
        
        //Topics names
        std::vector<std::string>* topics_names = new std::vector<std::string>(5);

        while (std::getline(file, str)){
 
          //Data recuperation
          std::vector<std::string> test=split(str, '=');    
          if(test.size()>1){
          
                //Kalman model
                //A
                if(test.at(0)=="A"){                             
                        cout <<"A = "<< test.at(1) << endl;
                        std::vector<std::string> lines=split(test.at(1), ';');               
                       for(int k=0; k<3; k++){
                                std::vector<std::string> values=split(lines.at(k), ' ');                              
                                for(int l=1; l<4; l++){                                           
                                          A[k][l-1]=atof(values.at(l).c_str());
                                }
                        }
                        /*string n="A";                   
                        matrix_display(&A,&n[0]);  */                  
                }
                //C
                if(test.at(0)=="C"){                             
                        cout <<"C = "<< test.at(1) << endl;
                        std::vector<std::string> lines=split(test.at(1), ';');               
                       for(int k=0; k<3; k++){
                                std::vector<std::string> values=split(lines.at(k), ' ');                              
                                for(int l=1; l<4; l++){                                          
                                          C[k][l-1]=atof(values.at(l).c_str());
                                }
                        }
                        /*string n="C";
                        matrix_display(&C,&n[0]);    */                
                }  
                //R
                if(test.at(0)=="R"){                             
                        cout <<"R = "<< test.at(1) << endl;
                        std::vector<std::string> lines=split(test.at(1), ';');               
                       for(int k=0; k<3; k++){
                                std::vector<std::string> values=split(lines.at(k), ' ');                              
                                for(int l=1; l<4; l++){                                          
                                          R[k][l-1]=atof(values.at(l).c_str());
                                }
                        }
                        /*string n="R";
                        matrix_display(&R,&n[0]);       */             
                }  
               
               
                //Q
                if(test.at(0)=="Q"){                             
                        cout <<"Q = "<< test.at(1) << endl;
                        std::vector<std::string> lines=split(test.at(1), ';');               
                       for(int k=0; k<3; k++){
                                std::vector<std::string> values=split(lines.at(k), ' ');                              
                                for(int l=1; l<4; l++){                                          
                                          Q[k][l-1]=atof(values.at(l).c_str());
                                }
                        }
                        /*string n="Q";
                        matrix_display(&Q,&n[0]); */                   
                }  
               
                //X0
                if(test.at(0)=="X0"){                             
                        cout <<"X0 = "<< test.at(1) << endl;
                        std::vector<std::string> lines=split(test.at(1), ' ');               
                       for(int k=0; k<6; k++){                    
                              X0[k]=atof(lines.at(k+1).c_str());                               
                        }
                        /*string n="X0";
                        matrix_display_X(&X0,&n[0]);  */                  
                }  
                
                //P0
                if(test.at(0)=="P0"){                             
                        cout <<"P0 = "<< test.at(1) << endl;
                        std::vector<std::string> lines=split(test.at(1), ';');               
                       for(int k=0; k<3; k++){
                                std::vector<std::string> values=split(lines.at(k), ' ');                              
                                for(int l=1; l<4; l++){                                          
                                          P0[k][l-1]=atof(values.at(l).c_str());
                                }
                        }
                       /* string n="P0";
                        matrix_display(&P0,&n[0]);        */            
                }  
                        
                //Topics names 
                //GPS
                if(test.at(0)=="GPS")                       
                        topics_names->at(0)=test.at(1);
                        
                //QRCode  
                if(test.at(0)=="QRCode")                             
                        topics_names->at(1)=test.at(1);  
                //PID
                if(test.at(0)=="PID")                             
                        topics_names->at(2)=test.at(1);     
                //IMU                    
                if(test.at(0)=="IMU")                             
                        topics_names->at(3)=test.at(1);  
                //Odometry                      
                if(test.at(0)=="Odometry")                             
                        topics_names->at(4)=test.at(1);                      
                        
                        
                                                         
          }
          
      

        }  

        /*for(int o=0; o<(int)(topics_names->size()); o++){
           cout << "Topic numero " << o << " : " << topics_names->at(o) << endl;

        }*/

        //Affectation
        GPS *gps= new GPS(topics_names->at(0), 33,"gps");
		GPS *odom=new GPS(topics_names->at(4), 33,"odom");		//Odometry message ==> 33 lines
		PID *pid=new PID(topics_names->at(2), 33,"pid");
		GPS *qr=new GPS(topics_names->at(1),33, "qrcode");
		IMU *imu=new IMU(topics_names->at(3),25);

		gps_global=gps;
		qr_global=qr;
		pid_global=pid;
		imu_global=imu;
		odom_global=odom;

        //Kalman
        mat_A=&A;
        mat_C=&C;
        mat_R=&R;
        mat_Q=&Q;
        mat_P0=&P0;
        mat_P=&P0;
        mat_X0=&X0;
        mat_X=&X0;  

}