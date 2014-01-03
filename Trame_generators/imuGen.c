#include <stdio.h>
#include <stdlib.h>

int main(){

	while(1)
		system("rostopic pub -r 1 imu sensor_msgs/Imu -f /home/jack/Bureau/CPP/Trame_generators/IMUMsg");

	return 0;
}
