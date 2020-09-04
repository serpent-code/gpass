#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLEN 64
#define ALPHAS_NUMBERS_LEN 62
#define ALPHAS_NUMBERS_SPECIALS_LEN 87
#define ALPHAS_LEN 52
#define NUMBERS_LEN 10


static char alphas_numbers[ALPHAS_NUMBERS_LEN] = {'a','b','c','d','e','f','g','h','i',
	'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
	'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0',
	'1','2','3','4','5','6','7','8','9'};

static char alphas_numbers_specials[ALPHAS_NUMBERS_SPECIALS_LEN] = {'a','b','c','d','e','f','g','h','i','j',
	'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F',
	'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1',
	'2','3','4','5','6','7','8','9','~','`','!','@','#','$','%','^','&','*','(',')','_','-',
	'=','+','[',']','{','}',':',';','?','<','>'};

static char alphas[ALPHAS_LEN] = {'a','b','c','d','e','f','g','h','i',
	'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
	'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

static char numbers[NUMBERS_LEN] = {'0','1','2','3','4','5','6','7','8','9'};

int main(int argc, char *argv[]) {

	void *ptr;
	char *rand_stream;
	char *charset;
	char *input_len;
	int index_array[MAXLEN];
	int charset_len;
	int username_password_format = 0;
	int username_len = 10;
	int password_len = 0;
	int lflag = 0;
	int i = 0;

	int opt;
	enum {
		ALPHAS,
		ALPHAS_NUMBERS,
		ALPHAS_NUMBERS_SPECIALS,
		NUMBERS
	} mode = ALPHAS_NUMBERS;

	while ((opt = getopt(argc, argv, "maunsl:")) != -1) {
	    switch (opt) {
	    case 'a': mode = ALPHAS; break;
	    case 'm': mode = ALPHAS_NUMBERS; break;
	    case 's': mode = ALPHAS_NUMBERS_SPECIALS; break;
	    case 'n': mode = NUMBERS; break;
	    case 'u': username_password_format = 1; break;
	    case 'l': lflag = 1; input_len = optarg; break;
	    case '?': 
		    if (optopt == 'l')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt)) {
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				fprintf(stderr, "Usage: %s [-OPTION]\n-a\tAlphabets\n-m\tAlphabets and numbers\n\
-s\tAlphabets and numbers and special chars\n-n\tNumbers\n-u\tUsername and password format\n\
-l <length>\tPassword length\n", argv[0]);
			} else
				fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
			return 1;
		default:
	        exit(EXIT_FAILURE);
	    }
	}
	if (lflag) {
		password_len = atoi(input_len);
		if (username_password_format) {
			if (password_len + username_len > MAXLEN) {
				fprintf (stderr, "Max password length is %d, given username and password combined is %d\n",
					MAXLEN, password_len + username_len);
				exit(EXIT_FAILURE);
			}
		} else {
			if (password_len > MAXLEN) {
				fprintf (stderr, "Max password length is %d, password length given is %d\n",
					MAXLEN, password_len);
				exit(EXIT_FAILURE);
			}
		}
		
	} else
		password_len = 40;

	switch (mode) {
		case ALPHAS:
			charset = alphas;
			charset_len = ALPHAS_LEN;
			break;
		case ALPHAS_NUMBERS_SPECIALS:
			charset = alphas_numbers_specials;
			charset_len = ALPHAS_NUMBERS_SPECIALS_LEN;
			break;
		case ALPHAS_NUMBERS:
			charset = alphas_numbers;
			charset_len = ALPHAS_NUMBERS_LEN;
			break;
		case NUMBERS:
			charset = numbers;
			charset_len = NUMBERS_LEN;
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

	if (username_password_format) {
		printf("username: ");

		for(i=0 ; i < username_len ; i++)
			printf("%c", charset[index_array[i]]);

		printf("\npassword: ");

		for(i=username_len ; i < password_len + username_len ; i++)
			printf("%c", charset[index_array[i]]);
	} else {
		for(i=0 ; i < password_len ; i++)
			printf("%c", charset[index_array[i]]);
	}
	

	printf("\n");

	free(ptr);

	return 0;
}
