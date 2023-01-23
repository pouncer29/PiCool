#include <conf_loader.h>

CONFIG* fan_config = NULL;

CONFIG* load_config(char* config_path){

	//Load up a new config struct
	CONFIG* my_config = (CONFIG*) malloc(sizeof(CONFIG));

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");

	//Collect the values
	int* val = (int*) malloc(sizeof(int));
	int count = 0;
	while(fscanf(conf_file,"%d",val) == 1){
		//Assign Values
		if(count == 0)
			my_config->fan_pin = (uint8_t) *val;
		else if(count == 1)
			my_config->poll_time = (uint8_t) *val;
		else if(count == 2)
			my_config->active_thresh = (uint8_t) *val;
		
		count++;
	}

	free(val);


	return my_config;
}

uint8_t get_fan_pin(){
	return -1;
}

uint8_t get_poll_time(){
	return -1;
}

uint8_t get_active_temp(){
	return -1;
}

uint8_t get_cur_temp(){
	return -1;
}
