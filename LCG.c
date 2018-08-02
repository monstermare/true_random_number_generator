#include "mraa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>

//referenced from the 'Grove Temperature Sensor'
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

unsigned short wait=1000; // wait 1000 microseconds after the measurement
unsigned short period = 1000000; // every 1 second, outputs the data

const unsigned short M = 10;
const unsigned short A = 5;
const unsigned short C = 1;

// declare the analog input contexts
mraa_aio_context temp;
mraa_aio_context light;
mraa_aio_context sound;

// initialize the contexts
int init(int argv, char **argc){
	// aio means analog, and you must plug temperature sensor on AIO0, light sensor on AIO1, and sound sensor on AIO2
	temp = mraa_aio_init(0); // AIO0
	light = mraa_aio_init(1); // AIO1
	sound = mraa_aio_init(2); // AIO2
	if(argv>2){
		fprintf(stderr, "too many arguments.\n\tUsage: lcg <seed number>\n");
		exit(1);
	}else if(argv<2){
		fprintf(stderr, "seed number must be provided.\n\tUsage: lcg <seed number>\n");
		exit(1);
	}else{
		int seed = atoi(argc[1]);
		if(seed==0||seed>=M){
			fprintf(stderr, "invalid number. number must be an integer smaller than %d.\n\tUsage: lcg <seed number>\n",M);
			exit(1);
		}
		return seed;
	}

}

void measureSensors(int seed){
	// if the sensors are not initialized, exit with 1
	if(temp==NULL||light==NULL||sound==NULL){
		fprintf(stderr,"unable to initialize AIO");
		exit(1);
	}
	char buf[50];
	uint16_t temp_val;
	uint16_t light_val;
	uint16_t sound_val;
	float R;
	float temperature;
	float adj_temp;
	float adj_light;
	float adj_sound;
	int n;
	int index;
	int frequency = period/wait;
	int prev = seed;
	while(1){
		adj_sound = 0;
		adj_temp = 0;
		adj_light = 0;
		// mreasuring data from sensors and finding average value
		for(index=0;index<period;index+=wait){
			//measuring analog data
			sound_val = mraa_aio_read(sound);
			temp_val = mraa_aio_read(temp);
			light_val = mraa_aio_read(light);
			//recording sound
			adj_sound += sound_val;
			//recording temperature
			R = R0*(1023.0/temp_val-1.0);
			adj_temp += 1.0/(log(R/R0)/B+1/298.15)-273.15;
			//recording light
			adj_light += light_val;
			usleep(wait);
		}
    adj_temp = adj_temp/frequency;
		adj_light = adj_light/frequency;
		adj_sound = adj_sound/frequency;
		//sprintf(buf, "temp:%.1f\tlight:%.1f\tsound:%.1f\n",adj_temp,adj_light,adj_sound);
		int rand = prev+
		rand = (A*rand+C)%M;
		n = strlen(buf);
		write(1,buf,n);
	}
}

int main(int argv, char **argc){
	int seed = init(int argv, char **argc);
	measureSensors(seed);
}
