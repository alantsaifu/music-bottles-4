#include "audio.h"

//file paths
const char *JAZZ1_PATH = "music-files/jazz1.wav";
const char *JAZZ2_PATH = "music-files/jazz2.wav";
const char *JAZZ3_PATH = "music-files/jazz3.wav";

const char *CLAS1_PATH = "music-files/classic1.wav";
const char *CLAS2_PATH = "music-files/classic2.wav";
const char *CLAS3_PATH = "music-files/classic3.wav";

const char *TECH1_PATH = "music-files/synth1.wav";
const char *TECH2_PATH = "music-files/synth2.wav";
const char *TECH3_PATH = "music-files/synth3.wav";

const char *BOST1_PATH = "music-files/boston1.wav";
const char *BOST2_PATH = "music-files/boston2.wav";
const char *BOST3_PATH = "music-files/boston3.wav";


//Wave chunks
Mix_Chunk *JAZZ1 = NULL;
Mix_Chunk *JAZZ2 = NULL;
Mix_Chunk *JAZZ3 = NULL;

Mix_Chunk *CLAS1 = NULL;
Mix_Chunk *CLAS2 = NULL;
Mix_Chunk *CLAS3 = NULL;

Mix_Chunk *TECH1 = NULL;
Mix_Chunk *TECH2 = NULL;
Mix_Chunk *TECH3 = NULL;

Mix_Chunk *BOST1 = NULL;
Mix_Chunk *BOST2 = NULL;
Mix_Chunk *BOST3 = NULL;

Mix_Chunk *chanA = NULL;
Mix_Chunk *chanB = NULL;
Mix_Chunk *chanC = NULL;

void initSound() {

	printf("Initializing Audio\n");

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Error initializing SDL\n");
		return;
	}

	Mix_AllocateChannels(3);

	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
		printf("Error initializing MIXER: %s\n",Mix_GetError());
		return;
	}

	volume(0,0);
	volume(1,0);
	volume(2,0);

	printf("Loading sounds to memory...\n");
	
	JAZZ1 = Mix_LoadWAV(JAZZ1_PATH);
	if (JAZZ1 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	JAZZ2 = Mix_LoadWAV(JAZZ2_PATH);
	if (JAZZ2 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	JAZZ3 = Mix_LoadWAV(JAZZ3_PATH);
	if (JAZZ3 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	printf("Loaded 'Jazz'.\n");

	CLAS1 = Mix_LoadWAV(CLAS1_PATH);
	if (CLAS1 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	CLAS2 = Mix_LoadWAV(CLAS2_PATH);
	if (CLAS2 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	CLAS3 = Mix_LoadWAV(CLAS3_PATH);
	if (CLAS3 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	printf("Loaded 'Classic'.\n");

	TECH1 = Mix_LoadWAV(TECH1_PATH);
	if (TECH1 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	TECH2 = Mix_LoadWAV(TECH2_PATH);
	if (TECH2 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	TECH3 = Mix_LoadWAV(TECH3_PATH);
	if (TECH3 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	printf("Loaded 'Techno/Synth'.\n");

	BOST1 = Mix_LoadWAV(BOST1_PATH);
	if (BOST1 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	BOST2 = Mix_LoadWAV(BOST2_PATH);
	if (BOST2 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	BOST3 = Mix_LoadWAV(BOST3_PATH);
	if (BOST3 == NULL) { printf("Error initializing CHAN_A: %s\n",Mix_GetError());	return; }
	printf("Loaded 'Boston'.\n");

	setFiles(0); //default Jazz
}

int isPlaying = 0;
int fileSet = -1; //so that first call to setFiles will actually set

void rewindFiles() {
	setFiles(fileSet);
}

//0 - Jazz, 1 - Classical, 2 - Techno, 3 - Boston
void setFiles(int i) {
	if (i>=0 && i<=3) {
		Mix_HaltChannel(-1);
		isPlaying = 0;
		fileSet = i;
		switch (i) {
			default:
			case 0:
				chanA = JAZZ1;
				chanB = JAZZ2;
				chanC = JAZZ3;
				break;
			case 1:
				chanA = CLAS1;
				chanB = CLAS2;
				chanC = CLAS3;
				break;
			case 2:
				chanA = TECH1;
				chanB = TECH2;
				chanC = TECH3;
				break;
			case 3:
				chanA = BOST1;
				chanB = BOST2;
				chanC = BOST3;
				break;
		}
	}
}

//TODO: enable fade in and out
void volume(int chan, int vol) {
	if (vol!=0 && isPlaying==0) {
		play();
	}
	Mix_Volume(chan, vol);
}

void play() {

	if (isPlaying == 0) {
		isPlaying = 1;

		if ( Mix_PlayChannel(0, chanA, -1) == -1 ) {
			printf("Error playing CHAN_A: %s\n",Mix_GetError());
			return;
		}
		
		if ( Mix_PlayChannel(1, chanB, -1) == -1 ) {
			printf("Error playing CHAN_B: %s\n",Mix_GetError());
			return;
		}

		if ( Mix_PlayChannel(2, chanC, -1) == -1 ) {
			printf("Error playing CHAN_C: %s\n",Mix_GetError());
			return;
		}

	}
}

