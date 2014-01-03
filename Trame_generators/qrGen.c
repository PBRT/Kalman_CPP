#include <stdio.h>
#include <stdlib.h>

int main(){

	int it = 0;

	while(1)
		system("rostopic pub -r 1 qrcode nav_msgs/Odometry -f /home/jack/Bureau/CPP/Trame_generators/QRMsg");

	return 0;
}
