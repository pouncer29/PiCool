#include <fan_automation.h>

/*
 * Synopsis: Returns the value inside of the TEMPERATURE_FILE in deg celcius
 */
float get_cur_temp(){

	//Open the file	
	FILE* temp_file = fopen(TEMPERATURE_FILE,"r");
	
	if(temp_file == NULL){
		fprintf(stderr,"TEMP FILE \"%s\" NOT FOUND.\n",TEMPERATURE_FILE);
		return -1.0f;
	}

	float cur_temp = 0.0f;
	
	fscanf(temp_file,"%f",&cur_temp);

	//Close the file
	fclose(temp_file);

	return cur_temp/1000; //Divide by 1000 to get deg_celcius
}

/**
 * Synopsis: Returns 1 if cur_temp > danger_temp, 0 otherwise
 */
int temp_over_thresh(float danger_temp){
	return (danger_temp - get_cur_temp()) > 0.0f;
}
