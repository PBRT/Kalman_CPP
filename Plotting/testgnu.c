#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
 
     
        FILE *gnuplot = popen("gnuplot -persist", "w");
        fprintf(gnuplot, "load \"config\"\n");
        fflush(gnuplot);
       
       return 0;
       }
