
#include <stdlib.h>

/**
Parameters
*/
float danger_temp = 60.0;
int outPin = 18;
int pollTime = 60;
char* sysfs_root = "/sys/class/gpio/gpio18" //TODO: change the 18 to be dynamic

//Activate GPIO pin 18
int activate(){
	return NULL;
}

//Deactivate GPIO
int deactivate(){
	return NULL;
}

int main(int argc, char **argv) {
	
}

