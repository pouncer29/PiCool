#include <conf_loader.h>

CONFIG* fan_config = NULL;

CONFIG* load_config(char* config_path){

	//Load up a new config struct
	CONFIG* my_config = (CONFIG*) malloc(sizeof(CONFIG));

	//Open the file	
	FILE* conf_file = fopen(config_path,"r");

	//Collect the values
	int val = 0;
	int count = 0;
	char keyword[10];
	int scan_ret = 0;

	//Look at the line of the file
	do{
		// Do Scan
		scan_ret = fscanf(conf_file,"%s%d",keyword,&val);

		//Should have ONLY key= value 2 args.
		if(scan_ret < 2){
			return NULL;
		}

		//TODO: evaluate keyword

		//Assign Values
		if(count == 0)
			my_config->fan_pin = val;
		else if(count == 1)
			my_config->poll_time = val;
		else if(count == 2)
			my_config->active_thresh = val;
		
		count++;
	} while (scan_ret != EOF);

	fclose(conf_file);

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
