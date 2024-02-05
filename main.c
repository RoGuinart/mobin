#include <stdio.h>
#include <string.h>	
#include <stdlib.h>
#include "mobin.h"


int main(int argc, char *argv[])
{
	char *sentence;
	unsigned sen_len = 0;
	if(argc < 2) {
		printf("No hi ha res a traduir.\n");
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		sen_len += strlen(argv[i]);
		if(i+1 != argc)
		sen_len++; // Space between words
	}

	sentence = malloc(sen_len);
	int sen_pos = 0;
	int i = 1;
	do {
		strcpy(sentence + sen_pos, argv[i]);
		sen_pos += strlen(argv[i]);
		if(i+1 != argc)
		sentence[sen_pos++] = ' ';

		i++;
	} while ( i < argc);

	//Enough for the worst possible scenario. Don't care about optimization. 
	// You'd need to write 241 chars to allocate 1KB. It's nothing.
	unsigned output_size = (int)(sen_len * 4.25)+1; 
	char *output = malloc(output_size);
	memset(output, 0, output_size);

	printf("Original: %s\n", sentence);

	if(strtomobin(sentence, output, output_size)) {
		printf("Error converting to mobin\n");
		return 1;
	}
	
	printf("Mobin: %s\n", output);

	if(mobintostr(output, sentence, sen_len)) {
		printf("Error converting back to alphanumeric\n");
		return 1;
	}

	printf("Retranslated: %s\n", sentence);

	free(sentence);
	free(output);
}