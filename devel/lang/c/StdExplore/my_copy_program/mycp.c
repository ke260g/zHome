#include<stdio.h>
#include<stdlib.h>

#define ERROR_EXIT \
		exit(EXIT_FAILURE)

int main(int argc, char *argv[]) {
	if ( argc != 3) {
		fprintf(stderr, "Usage: %s <path/to/src_file> <path/to/dst_file>\n", argv[0]);
		ERROR_EXIT;
	}

	FILE *src_file, *dst_file;
	if ((src_file = fopen(argv[1], "r")) == NULL){
		perror("Open src_file");
		ERROR_EXIT;
	}
	if ((dst_file = fopen(argv[2], "w")) == NULL){
		perror("Open dst_file");
		ERROR_EXIT;
	}

	int trans_char;
	while ((trans_char = fgetc(src_file)) != EOF)
		fputc(trans_char, dst_file);

	printf("Copy successfully\n");
    fcloseall();

	return 0;
}
