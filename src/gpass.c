#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLEN 64
#define STR_CHARSET_LEN 62
#define SPC_CHARSET_LEN 87


static char standard_charset[STR_CHARSET_LEN] = {'a','b','c','d','e','f','g','h','i',
	'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
	'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0',
	'1','2','3','4','5','6','7','8','9'};

static char special_charset[SPC_CHARSET_LEN] = {'a','b','c','d','e','f','g','h','i','j',
	'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F',
	'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1',
	'2','3','4','5','6','7','8','9','~','`','!','@','#','$','%','^','&','*','(',')','_','-',
	'=','+','[',']','{','}',':',';','?','<','>'};


int main(int argc, char *argv[]) {

	void *ptr;
	char *rand_stream;
	char *charset;
	int index_array[MAXLEN];
	int charset_len;
	int i = 0;

	int opt;
	enum { STANDARD_CHARS, SPECIAL_CHARS, } mode = STANDARD_CHARS;

	while ((opt = getopt(argc, argv, "s")) != -1) {
	    switch (opt) {
	    case 's': mode = SPECIAL_CHARS; break;
	    default:
	        fprintf(stderr, "Usage: %s [-s]\n", argv[0]);
	        exit(EXIT_FAILURE);
	    }
	}

	switch (mode) {
		case STANDARD_CHARS:
			charset = standard_charset;
			charset_len = STR_CHARSET_LEN;
			break;
		case SPECIAL_CHARS:
			charset = special_charset;
			charset_len = SPC_CHARSET_LEN;
			break;
	}


	ptr = malloc(256 * sizeof(char));

	int res = getentropy(ptr, 256);

	if (res!=0) {
		puts("getentropy failed.");
		exit(1);
	}

	rand_stream = (char *) ptr;


	for(i=0 ; i < MAXLEN ; i++)
		*(index_array + i) = abs(*(rand_stream + i)) % charset_len;


	printf("username: ");

	for(i=0 ; i < 10 ; i++)
		printf("%c", charset[index_array[i]]);

	printf("\npassword: ");

	for(i=10 ; i < 50 ; i++)
		printf("%c", charset[index_array[i]]);

	printf("\n");

	free(ptr);

	return 0;
}
