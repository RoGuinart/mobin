
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mobin.h"

#define HEX_TABLE "0123456789ABCDEF"

static int  charToMorse (char input, char *output);
static int  morseToBin  (char morse, char *bin, unsigned *pos);
static char morseToChar (char *morse);
static int  hexToBin    (char hex, char *bin, int *len);

/**
 * \brief Translates a letter to morse code, returned as string.
 *        It does not accept tildes or any special symbols, so keep it simple
 *        with ASCII characters. If you enter invalid characters, the contents 
 *        of output will be unchanged. 
 * 
 * \param input  Letter to translate
 * \param output Output string. To prevent segmentation faults, this should
 *               always have at least 8 bytes of space.
 * 
 * \return 0 on success, 1 if input is invalid.
 */
static int charToMorse(char input, char *output)
{
	if(sizeof(output) < 8)
		return 1;

	switch(input) {
	case 'a': case 'A': strcpy(output,".- "    ); break;
	case 'b': case 'B': strcpy(output,"-... "  ); break;
	case 'c': case 'C': strcpy(output,"-.-. "  ); break;
	case 'd': case 'D': strcpy(output,"-.. "   ); break;
	case 'e': case 'E': strcpy(output,". "     ); break;
	case 'f': case 'F': strcpy(output,"..-. "  ); break;
	case 'g': case 'G': strcpy(output,"--. "   ); break;
	case 'h': case 'H': strcpy(output,".... "  ); break;
	case 'i': case 'I': strcpy(output,".. "    ); break;
	case 'j': case 'J': strcpy(output,".--- "  ); break;
	case 'k': case 'K': strcpy(output,"-.- "   ); break;
	case 'l': case 'L': strcpy(output,".-.. "  ); break;
	case 'm': case 'M': strcpy(output,"-- "    ); break;
	case 'n': case 'N': strcpy(output,"-. "    ); break;
	case 'o': case 'O': strcpy(output,"--- "   ); break;
	case 'p': case 'P': strcpy(output,".--. "  ); break;
	case 'q': case 'Q': strcpy(output,"--.- "  ); break;
	case 'r': case 'R': strcpy(output,".-. "   ); break;
	case 's': case 'S': strcpy(output,"... "   ); break;
	case 't': case 'T': strcpy(output,"- "     ); break;
	case 'u': case 'U': strcpy(output,"..- "   ); break;
	case 'v': case 'V': strcpy(output,"...- "  ); break;
	case 'w': case 'W': strcpy(output,".-- "   ); break;
	case 'x': case 'X': strcpy(output,"-..- "  ); break;
	case 'y': case 'Y': strcpy(output,"-.-- "  ); break;
	case 'z': case 'Z': strcpy(output,"--.. "  ); break;

	case '0':           strcpy(output,"----- " ); break;
	case '1':           strcpy(output,".---- " ); break;
	case '2':           strcpy(output,"..--- " ); break;
	case '3':           strcpy(output,"...-- " ); break;
	case '4':           strcpy(output,"....- " ); break;
	case '5':           strcpy(output,"..... " ); break;
	case '6':           strcpy(output,"-.... " ); break;
	case '7':           strcpy(output,"--... " ); break;
	case '8':           strcpy(output,"---.. " ); break;
	case '9':           strcpy(output,"----. " ); break;

	case ' ':           strcpy(output,"\\"     ); break;
	case '.':           strcpy(output,".-.-.- "); break;
	case ',':           strcpy(output,"--..-- "); break;
	case ':':           strcpy(output,"---... "); break;
	case ';':           strcpy(output,"-.-.-. "); break;
	case '!':           strcpy(output,"-.-.-- "); break;
	case '?':           strcpy(output,"..--.. "); break;
	case '\'':          strcpy(output,".----. "); break;
	case '"':           strcpy(output,".-..-. "); break;
	// case '¡':           strcpy(output,"--...-" ); break;
	// case '¿':           strcpy(output,"..-.- " ); break;
	case '/':           strcpy(output,"-..-. " ); break;
	case '(':           strcpy(output,"-.--. " ); break;
	case ')':           strcpy(output,"-.--.- "); break;
	case '+':           strcpy(output,".-.-. " ); break;
	case '-':           strcpy(output,"-....- "); break;
	case '=':           strcpy(output,"-...- " ); break;
	case '&':           strcpy(output,".-... " ); break;
	default:                                   return 1;
	}
	return 0;
}

/**
 * \brief Converts a morse digit to binary notation.
 *        '.' becomes "1", '-' becomes "11"
 *        0s are added between digits, letters, words.
 * 
 * \param morse Morse digit to translate
 * \param bin   Output string
 * \param pos   Pointer position where the result is stored
 */
static int morseToBin(char morse, char *bin, unsigned *pos)
{
	switch (morse) {
	case '-':
		bin[(*pos)++] = '1';
		bin[(*pos)++] = '1';
		break;
	case '.':
		bin[(*pos)++] = '1';
		break;
	case ' ':
		bin[(*pos)++] = '0';
		break;
	case '\\':
		bin[(*pos)++] = '0';
		break;
	default:
		return -1;
	}
	return 0;
}

/**
 * \brief Translates a morse letter to alphanumeric.
 * 
 * \param morse Morse letter to translate
 * 
 * \return ASCII code of the letter. Returns 0 on invalid cases.
 * 
 * TODO: Optimize! Every single comparison is a whole call to strcmp()
 */
static char morseToChar(char *morse)
{
	switch (strlen(morse)) {
	case 1:
		if(!strcmp(morse, "."    ))  return  'E';
		if(!strcmp(morse, "-"    ))  return  'T';
		if(!strcmp(morse, "\\"   ))  return  ' ';
		break;
	case 2:
		if(!strcmp(morse, ".."   ))  return  'I';
		if(!strcmp(morse, ".-"   ))  return  'A';
		if(!strcmp(morse, "-."   ))  return  'N';
		if(!strcmp(morse, "--"   ))  return  'M';
		break;
	case 3:
		if(!strcmp(morse, "..."  ))  return  'S';
		if(!strcmp(morse, "..-"  ))  return  'U';
		if(!strcmp(morse, ".-."  ))  return  'R';
		if(!strcmp(morse, ".--"  ))  return  'W';
		if(!strcmp(morse, "-.."  ))  return  'D';
		if(!strcmp(morse, "-.-"  ))  return  'K';
		if(!strcmp(morse, "--."  ))  return  'G';
		if(!strcmp(morse, "---"  ))  return  'O';
		break;
	case 4:
		if(!strcmp(morse, "...." ))  return  'H';
		if(!strcmp(morse, "...-" ))  return  'V';
		if(!strcmp(morse, "..-." ))  return  'F';
		if(!strcmp(morse, ".-.." ))  return  'L';
		if(!strcmp(morse, ".--." ))  return  'P';
		if(!strcmp(morse, ".---" ))  return  'J';
		if(!strcmp(morse, "-..." ))  return  'B';
		if(!strcmp(morse, "-..-" ))  return  'X';
		if(!strcmp(morse, "-.-." ))  return  'C';
		if(!strcmp(morse, "-.--" ))  return  'Y';
		if(!strcmp(morse, "--.." ))  return  'Z';
		if(!strcmp(morse, "--.-" ))  return  'Q';
		break;
	case 5: //Numbers & symbols
		if(!strcmp(morse, "-----"))  return  '0';
		if(!strcmp(morse, ".----"))  return  '1';
		if(!strcmp(morse, "..---"))  return  '2';
		if(!strcmp(morse, "...--"))  return  '3';
		if(!strcmp(morse, "....-"))  return  '4';
		if(!strcmp(morse, "....."))  return  '5';
		if(!strcmp(morse, "-...."))  return  '6';
		if(!strcmp(morse, "--..."))  return  '7';
		if(!strcmp(morse, "---.."))  return  '8';
		if(!strcmp(morse, "----."))  return  '9';
		// if(!strcmp(morse, "..-.-"))  return  '¿';
		if(!strcmp(morse, "-..-."))  return  '/';
		if(!strcmp(morse, "-.--."))  return  '(';
		if(!strcmp(morse, ".-.-."))  return  '+';
		if(!strcmp(morse, "-...-"))  return  '=';
		if(!strcmp(morse, ".-..."))  return  '&';
		break;
	case 6: //Symbols
		if(!strcmp(morse, ".-.-.-")) return  '.';
		if(!strcmp(morse, "--..--")) return  ',';
		if(!strcmp(morse, "---...")) return  ':';
		if(!strcmp(morse, "-.-.-.")) return  ';';
		if(!strcmp(morse, "-.-.--")) return  '!';
		if(!strcmp(morse, "..--..")) return  '?';
		if(!strcmp(morse, ".----.")) return '\'';
		if(!strcmp(morse, ".-..-.")) return  '"';
		// if(!strcmp(morse, "--...-")) return  '¡';
		if(!strcmp(morse, "-.--.-")) return  ')';
		if(!strcmp(morse, "-....-")) return  '-';

	default:
		break;
	}

	return 0;
}

/**
 * \brief Converts a hex digit to its binary equivalent.
 * 
 * \param hex Hexadecimal character to convert
 * \param bin Pointer to store the result
 * \param pos String position to store the result at.
 */
static int hexToBin(char hex, char *bin, int *len)
{
	int pos = (*len) = strlen(bin);
	switch (hex) {
	case '0': strcpy(bin+pos, "0000"); break; //Should never occur
	case '1': strcpy(bin+pos, "0001"); break;
	case '2': strcpy(bin+pos, "0010"); break;
	case '3': strcpy(bin+pos, "0011"); break;
	case '4': strcpy(bin+pos, "0100"); break;
	case '5': strcpy(bin+pos, "0101"); break;
	case '6': strcpy(bin+pos, "0110"); break;
	case '7': strcpy(bin+pos, "0111"); break; //Should never occur
	case '8': strcpy(bin+pos, "1000"); break;
	case '9': strcpy(bin+pos, "1001"); break;
	case 'A': strcpy(bin+pos, "1010"); break;
	case 'B': strcpy(bin+pos, "1011"); break;
	case 'C': strcpy(bin+pos, "1100"); break;
	case 'D': strcpy(bin+pos, "1101"); break;
	case 'E': strcpy(bin+pos, "1110"); break; //Should never occur
	case 'F': strcpy(bin+pos, "1111"); break; //Should never occur
	default:                        return 1;
	}

	(*len) += 4;
	return 0;
}

int strtomobin(char *str, char *mobin, long mlen)
{
	int i, j, err;
	unsigned k = 0,          //Posició a bAux
		 output_pos = 0; //Posició a output
	char bAux[9]; // auxiliar on guardar binari
	memset(bAux, 0, 9);

	int input_len = strlen(str);
	for (i = 0; i < input_len; i++) { //for each input letter
		char mAux[8]; //aux to store morse
		memset(mAux, 0, 8);

		err = charToMorse(str[i], mAux);
		if(err)
			continue;

		for (j = 0; j < strlen(mAux); j++) { // for each morse digit

			err = morseToBin(mAux[j], bAux, &k);
			if(err)
				continue;

			if(j+1 < strlen(mAux)) // If the letter isn't finished yet
				bAux[k++] = '0';

			if(strlen(bAux) >= 4) {
				char hAux[5]; // aux to store 4 bits
				memset(hAux, 0, 5);
				strncpy(hAux, bAux, 4);

				// Store hex
				int hexDigit = strtol(hAux, NULL, 2);

				// If it exists. If bin % 4 == 0, it would add another 0 to hex, which we don't want
				if(hexDigit && output_pos < mlen) 
					mobin[ output_pos++ ] = HEX_TABLE[hexDigit];

				for (int n = 0; n < 4; n++) {
					bAux[n] = bAux[n+4];
					bAux[n+4] = 0;
				}

				k-=4;
				
			} //if(strlen(bAux) > 4)
		} // for(j = 0; j < strlen(mAux); j++)
	} // for (i = 0; i < strlen(input); i++)

	for (int rem = strlen(bAux) % 4; rem < 4; rem++)
		bAux[k++] = '0';
	int hexDigit = strtol(bAux, NULL, 2);

	// If bin % 4 == 0, it would add another 0 to hex, which we don't want
	if(hexDigit && output_pos < mlen)
		mobin[ output_pos++ ] = HEX_TABLE[hexDigit];

	return 0;
}

int mobintostr(char *mobin, char *str, long slen)
{
	char mAux[16], // Morse code.
	     bAux[ 9]; // Letters in binary.
	unsigned mor_pos = 0, out_pos = 0, mob_pos = 0;
	int bin_len = 0, mob_len;
	char one = 0, zero = 0;


	memset(mAux, 0, 16);
	memset(bAux, 0,  9);
	mob_len = strlen(mobin);
	for (int i = 0; i < mob_len*4; i++) {
		//parse binary
		if(!bin_len)
			hexToBin(mobin[mob_pos++], bAux, &bin_len);

		// parse binary
		if(bAux[0] == '1') {
			one++;
			zero = 0;

		} else { //if a zero is found
			zero++;

			switch (zero) {
			case 1: // store morse digit
				if(one == 2)
					mAux[mor_pos++] = '-';
				else if(one == 1)
					mAux[mor_pos++] = '.';
				else
					return 1;

				one = 0;
				break;
			case 2:
				if(out_pos >= slen)
					return -1;
				
				one = 0;
				char chr = morseToChar(mAux);

				if(!chr) // Invalid character
					return 1; 

				str[out_pos++] = chr; // Parse and store letter
			
				memset(mAux, 0, 16);
				mor_pos = 0;
				break;

			case 3:
				if(out_pos < slen)
				str[out_pos++] = ' '; //Add a space
				break;
			default:
				return 1;
			}
		} 

		//flush the read binary digits
		for (int i = 1; i <= bin_len; i++) {
			bAux[i-1] = bAux[i];
			bAux[i] = 0;
		}

		bin_len -= 1;
		
	} // for (int i = 0; i < mob_len; i++)

	if(one) {
		if(one == 2)
			mAux[mor_pos++] = '-';
		else if(one == 1)
			mAux[mor_pos++] = '.';
		else
			return 1;
	}
	
	if(strlen(mAux)) {
		char chr = morseToChar(mAux);
		if(chr)
			str[out_pos++] = chr; // Parse and store letter
		else
			return 1;

	}


	return 0;
}
