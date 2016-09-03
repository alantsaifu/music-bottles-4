/**

Music Bottles v4 by Tal Achituv

Based on code by Tomer Weller, Jasmin Rubinovitz, as well as the general idea of previous Music Bottles versions

*/

#include "audio.h"
#include "hx711.h"

//Buttons connections
#define RETARE_PIN  26
#define MUSIC1_PIN  19
#define MUSIC2_PIN  13
#define MUSIC3_PIN  6
#define MUSIC4_PIN  5


int main(int argc, char **argv) {
	int i;

	initHX711();

	float sps = speedTest();
	printf("Test shows: %f SPS\n",sps);

	for (i=0; i<10; i++) {
		long sample = getCleanSample(4,4);
		printf("got sample: %d\n",sample);
	}

	initSound();

	play();
	volume(0,0);
	volume(1,64);
	volume(2,0);

	sleep(2);
	volume(0,64);
	volume(1,64);
	volume(2,0);
	sleep(2);
	volume(0,64);
	volume(1,64);
	volume(2,64);
	sleep(2);

	setFiles(2);
	play();
	sleep(3);

}