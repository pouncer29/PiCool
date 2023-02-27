#include <fan_automation.h>
// TEMPERATURE_FILE "./test_temperature/temp"
float get_cur_temp(){

	//Open the file	
	FILE* temp_file = fopen(TEMPERATURE_FILE,"r");
	
	if(temp_file == NULL){
		fprintf(stderr,"TEMP FILE \"%s\" NOT FOUND.\n",TEMPERATURE_FILE);
		return 1;
	}

	float cur_temp = 0.0f;
	
	fscanf(temp_file,"%f",&cur_temp);

	//Close the file
	fclose(temp_file);

	return cur_temp/1000; //Divide by 1000 to get deg_celcius
}

int run(){
	return 1;
}

