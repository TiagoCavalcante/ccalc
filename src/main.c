#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char character = 0;

	unsigned char characters[255];
	unsigned char charactersLenght = 0;

	// tokens [ even ] = INT
	// tokens [ odd ]  = '+' || '-' || '*' || '/'
	unsigned char *tokens[255];
	unsigned char tokensLenght = 0;

	int numbers[255];

	unsigned char openNumber = 0;

	char temporaryCharacter[2] = { 0, '\0' };

	for (unsigned char i = 1; i < argc; ++i) {
		for (unsigned char j = 0; argv[i][j] != '\0'; ++j) {
			if (argv[i][j] != ' ') {
				characters[charactersLenght++] = argv[i][j];
			}
		}
	}

	for (unsigned char i = 0; i < charactersLenght; ++i) {
		temporaryCharacter[0] = characters[i];

		if (characters[i] >= '0' && characters[i] <= '9') {
			if (!openNumber) {
				tokens[tokensLenght++] = (char *) malloc(16);
				tokens[tokensLenght - 1][0] = '\0';

				openNumber = 1;
			}

			strcat(tokens[tokensLenght - 1], temporaryCharacter);
		}
		else {
			openNumber = 0;

			tokens[tokensLenght++] = (char *) malloc(16);
			tokens[tokensLenght - 1][0] = '\0';
			
			strcat(tokens[tokensLenght - 1], temporaryCharacter);
		}
	}

	for (unsigned char i = 0; i < tokensLenght; i += 2) {
		numbers[i / 2] = atoi(tokens[i]);
	}

	for (unsigned char i = 1; i < tokensLenght; i += 2) {
		switch (tokens[i][0]) {
			case '+':
				numbers[i / 2 + 1] += numbers[i / 2];

				break;
			case '-':
				numbers[i / 2 + 1] -= numbers[i / 2];

				break;
			case '*':
				numbers[i / 2 + 1] *= numbers[i / 2];

				break;
			case '/':
				numbers[i / 2 + 1] /= numbers[i / 2];

				break;
		}
	}

	printf("%d\n", numbers[tokensLenght / 2]);

	for (unsigned char i = 0; i < tokensLenght; ++i) {
		free(tokens[i]);	
	}

	return 0;
}