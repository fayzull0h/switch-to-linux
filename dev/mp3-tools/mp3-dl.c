#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fgetline(char buf[], int size, FILE * fp);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: mp3-dl [filename]\n");
		return 0;
	}

	if (argc > 3) {
		if (!strcmp(argv[1], "--single")) {
			printf("Download single file?");
			getc(stdin);
			char command[128];
			sprintf(command, "yt-dlp \"%s\" -x --audio-format mp3 -o %s", argv[2], argv[3]);
			printf("Downloading file...\n");
			system(command);
			return 0;
		}
	}

	FILE * songs;

	char *filename = argv[1];

	printf("You put the file: ");
	puts(filename);

	// Get number of songs
	int numTracks;
	printf("How many songs are there? ");
	scanf("%d", &numTracks);

	// Make array for youtube links
	char links[numTracks][45];
	char songnames[numTracks][128];
	char commands[numTracks][128];

	// Initialize commands array with "youtube-dl "
	for (int i = 0; i < numTracks; i++) {
		strcpy(commands[i], "youtube-dl ");
	}

	// Open file with links for reading
	songs = fopen(filename, "r");
	
	// Populate array of youtube links
	char bufferlink[50] = "temp";
	for (int i = 0; i < numTracks; i++) {
		fgetline(bufferlink, 50, songs);
		strcpy(links[i], bufferlink);
	}

	fgetc(songs);

	char buffersong[128] = "temp";
	for (int i = 0; i < numTracks; i++) {
		fgetline(buffersong, 128, songs);
		strcpy(songnames[i], buffersong);
	}

	for (int i = 0; i < numTracks; i++) {
		for (int j = 0; j < 128; j++) {
			if (songnames[i][j] == '/') {
				songnames[i][j] = '_';
			}
		}
	}

	for (int i = 0; i < numTracks; i++) {
		strcat(commands[i], links[i]);
		strcat(commands[i], " -o \"");
		strcat(commands[i], songnames[i]);
		strcat(commands[i], ".mp3\"");
	}	

	for (int i = 0; i < numTracks; i++) {
		system(commands[i]);
	}

	fclose(songs);
	return 0;
}

void fgetline(char buf[], int size, FILE * fp) {
	char line[size];
	int counter = size;
	for (int i = 0; i < size; i++) {
		char temp = fgetc(fp);
		if (temp == '\n') {
			counter = i;
			break;
		}
		line[i] = temp;
	}

	for (int i = counter; i < size; i++) {
		line[i] = '\0';
	}

	for (int i = 0; i < size; i++) {
		buf[i] = line[i];
	}
}
