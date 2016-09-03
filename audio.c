#include "audio.h"

//file paths
const char *JAZZ_1_PATH = "music-files/jazz1.wav";
const char *JAZZ_2_PATH = "music-files/jazz2.wav";
const char *JAZZ_3_PATH = "music-files/jazz3.wav";

const char *CLAS_1_PATH = "music-files/classic1.wav";
const char *CLAS_2_PATH = "music-files/classic2.wav";
const char *CLAS_3_PATH = "music-files/classic3.wav";

const char *TECH_1_PATH = "music-files/synth1.wav";
const char *TECH_2_PATH = "music-files/synth2.wav";
const char *TECH_3_PATH = "music-files/synth3.wav";

const char *BOST_1_PATH = "music-files/boston1.wav";
const char *BOST_2_PATH = "music-files/boston2.wav";
const char *BOST_3_PATH = "music-files/boston3.wav";


//Wave channels
Mix_Chunk *chanA = NULL;
Mix_Chunk *chanB = NULL;
Mix_Chunk *chanC = NULL;

void initSound() {
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

	setFiles(0); //default Jazz
}

//0 - Jazz, 1 - Classical, 2 - Techno, 3 - Boston
void setFiles(int i) {
	const char *chanA_Path, *chanB_Path, *chanC_Path;
	switch (i) {
		default:
		case 0:
			chanA_Path = JAZZ_1_PATH;
			chanB_Path = JAZZ_2_PATH;
			chanC_Path = JAZZ_3_PATH;
			break;
		case 1:
			chanA_Path = CLAS_1_PATH;
			chanB_Path = CLAS_2_PATH;
			chanC_Path = CLAS_3_PATH;
			break;
		case 2:
			chanA_Path = TECH_1_PATH;
			chanB_Path = TECH_2_PATH;
			chanC_Path = TECH_3_PATH;
			break;
		case 3:
			chanA_Path = BOST_1_PATH;
			chanB_Path = BOST_2_PATH;
			chanC_Path = BOST_3_PATH;
			break;
	}


	Mix_HaltChannel(0);
	Mix_HaltChannel(1);
	Mix_HaltChannel(2);

	chanA = Mix_LoadWAV(chanA_Path);
	if (chanA == NULL) {
		printf("Error initializing CHAN_A: %s\n",Mix_GetError());
		return;
	}
	
	chanB = Mix_LoadWAV(chanB_Path);
	if (chanB == NULL) {
		printf("Error initializing CHAN_B: %s\n",Mix_GetError());
		return;
	}

	chanC = Mix_LoadWAV(chanC_Path);
	if (chanC == NULL) {
		printf("Error initializing CHAN_C: %s\n",Mix_GetError());
		return;
	}
}

//TODO: enable fade in and out
void volume(int chan, int vol) {
	Mix_Volume(chan, vol);
}

void play() {
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

