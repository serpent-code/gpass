#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static char charset[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t',
	'u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9'};



int main() {

	void *ptr;
	int *rand_stream_int;
	int index_array[64];
	int i = 0;

	ptr = malloc(33 * sizeof(size_t));

	size_t size=256;
	int res = getentropy(ptr, size);

	if (res!=0) {
		puts("getentropy failed.");
		exit(1);
	}

	rand_stream_int = (int *) ptr;

	for(i=0 ; i < 64 ; i++) {
		index_array[i] = abs(rand_stream_int[i]) % 62;
	}

	printf("username: ");

	for(i=0 ; i < 10 ; i++) {
		printf("%c", charset[index_array[i]]);
	}

	printf("\npassword: ");

	for(i=10 ; i < 50 ; i++) {
		printf("%c", charset[index_array[i]]);
	}

	printf("\n");

	free(ptr);

	return 0;
}
