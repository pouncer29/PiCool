#include <stdio.h>
#include <stdlib.h>

/**
Parameters
*/
float dangerTemp = 60.0;
int outPin = 18;
int pollTime = 60;
//char* sysfs_root = "/sys/class/gpio/gpio18"; //TODO: change the 18 to be dynamic
char* sysfs_root = "/Users/FrankyB/fGrams/Projects/PiCool/Test/gpio18"; 

/**
Reads the current temperature
*/
int readTemp(){
	return 0;
}

/**
writes to the sys log
*/
int writeToLog(char* msg){
	return fprintf(stdout,"%s o:%i,p:%i,d:%f \n",msg, outPin,pollTime,dangerTemp);
}

//Activate GPIO pin 18
int activate(){
	FILE* gpio = fopen(sysfs_root, "w+");
	int wo = fprintf(gpio,"%i",1);
	return wo;
}

//Deactivate GPIO
int deactivate(){
	FILE* gpio = fopen(sysfs_root, "w+");
	return fprintf(gpio,"%i",0);
}

int main(int argc, char **argv) {
	writeToLog("\nTesting Deactivate:");
	int ret = deactivate();
	printf("\n Deactivate Returned:%d", ret);

	writeToLog("Testing Activate: ");
	ret = activate();
	printf("Activate Returned:%d", ret);

	return 0;
}

