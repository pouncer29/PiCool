#include <picool.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

//Initialize global CONF
//fan_pin
//poll_time
//active_thresh
CONFIG* config = NULL;
int run = 1;

void shutdown(){
	run = 0;
}
void cleanup(){
	printf("HIT THE CLEANUP\n");

	if(config != NULL){
		//Deactivate the fan
		if(deactivate_fan() != 0){
			fprintf(stderr,"ERROR: FAILED TO DEACTIVATE FAN\n");
		} else {
			printf("FAN DEACTIVATED ON SHUTDOWN\n");
		}
		deactivate_fan();
		//Unload the config
		if(unload_config() != 0){
			fprintf(stderr,"ERROR: FAILED TO FREE CONFIG\n");
		} else {
			printf("FREED THE CONFIG\n");
		}
	}
		
}

/**
 * First, load the conf file
 * Second, check the temperature
 * Third 	A, if temp is > thresh, activate fan
 * 		B, if temp is < thresh, deactivate fan
 * Fourth, sleep(<DURATION>) seconds
 */
int main(int argc, char* argv[]){

	//Register the cleanup handler
	signal(SIGQUIT,shutdown);
	signal(SIGINT,shutdown);

	//Load the config
	config = get_config(DEFAULT_CONF_FILE_LOC);

	if(config == NULL){
		fprintf(stderr,"ERROR: CONFIG FILE WAS NULL");
		return EXIT_FAILURE;
	}
	printf("CONFIG @ %s WAS %d, %d, %f\n",DEFAULT_CONF_FILE_LOC,config->fan_pin,config->poll_time,
		config->active_thresh);

	//Initialize GPIO
	int gpio_init = initialize_GPIO();
	if(gpio_init != 0){
		fprintf(stderr,"ERROR: FAILED TO INIT GPIO %d",gpio_init);
	}

	/** FOREVER */
	//HOld on, TODO: Free the config file on exit
	while(run == 1){
		printf("STATUS: TEMP=%f PIN=%d, THRESH=%f\n",get_cur_temp(),
			config->fan_pin,config->active_thresh);
		//If the read temp exceeds the threshold
		if(0 == temp_over_thresh(config->active_thresh)){
			//Activate the fan & Check return
			if(activate_fan() != 0){
				fprintf(stderr,"ERROR: FAILED TO ACTIVATE FAN\n");
			} else {
				printf("FAN ACTIVATED\n");
			}
		} else {
			//Otherwise, deactivate it
			if(deactivate_fan() != 0){
				fprintf(stderr,"ERROR: FAILED TO DEACTIVATE FAN\n");
			} else {
				printf("FAN DEACTIVATED\n");
			}
		}

		//And then sleep for  the poll_time duration
		sleep(config->poll_time);
		printf("AWAKE\n");
	}

	//If we were told to quit, then cleanup
	cleanup();
	return EXIT_SUCCESS;

}

