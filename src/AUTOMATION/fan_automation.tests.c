#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <conf_loader.h>
#include <math.h>
#include <fan_automation.h>


int get_temp_reads_proper_value(){
	float result = get_cur_temp();
	float expected = 55.5f;

	if (fabs(expected - result) > 0.0001){
		printf("get_cur_temp() expected %f, got %f\n",expected,result);
		return -1;
	}

	return 0;
}

int check_thresh_returns_proper_value(){
	float over_thresh = 55.6f;
	float under_thresh = 55.4f;
	
	if(temp_over_thresh(over_thresh) != 1){
		printf("temp_over_thresh() expected thresh to be exceeded");
		return -1;
	} else if(temp_over_thresh(under_thresh) != 0){
		printf("temp_over_thresh() expected thresh NOT to be exceeded");
		return -2;
	}

	return 0;
}


int main(){
	int result = 1;

	result = get_temp_reads_proper_value();
	if(result != 0){
		errx(result,"FAILED -- get_cur_temp() failed to retrieve temperature\n");
	} else {
		//Alert of Pass
		printf("get_cur_temp() fetches temperature -- PASSED\n");
	}

	result = check_thresh_returns_proper_value();
	if(result != 0){
		errx(result,"FAILED -- temp_over_thresh() falsely flagged temp threshold\n");
	} else {
		//Alert of Pass
		printf("temp_over_thresh() alerts of threshold exceed -- PASSED\n");
	}



	return 0;
}


