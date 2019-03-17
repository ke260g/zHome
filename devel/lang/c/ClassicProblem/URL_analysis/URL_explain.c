#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int URL_length;
char *URL;

char *malloc_cp_URL(void) {
/* 
 * return a pointer to a new mem_space,
 * where store a copy of the URL.
 * Callers are supposed to free manaully.
 */
	char *cp_URL_str = malloc(URL_length+1);
	strcpy(cp_URL_str, URL);
	return cp_URL_str;
}
	
void is_URL_legal(const char *URL_str) {
/*
 * check whether the URL is legal by testing several header characters.
 * http, https are legal.
 */
	if( (strstr(URL_str, "http://") != NULL) || (strstr(URL_str, "https://") != NULL) )
		printf("The URL is legal.\n"
				"Now explain.\n");
	else {
		fprintf(stderr,
				"The URL is illegal.\n"
				"Please try again.\n");
		exit(EXIT_FAILURE);
	}
}

void display_URL_dir(const char *URL_str) {
	char *tmp_URL_str = malloc_cp_URL();
	char *position = NULL;
	char *token_dir = strtok_r(tmp_URL_str, "?", &position);
	printf("URL_dir : %s\n", token_dir);
	free(tmp_URL_str);
}

void display_URL_search(const char *URL_str) {
	char *rest_URL = NULL;
	char *tmp_URL_str = malloc_cp_URL();
	char *str = strtok_r(tmp_URL_str, "?", &rest_URL);
	char *value_pair = NULL;
	int counter = 1;
	while (1) {
		value_pair = strtok_r(rest_URL, "&", &rest_URL);
		if (value_pair == NULL) 
			break;
		printf("%d : %s\n", counter, value_pair);
		counter++;
	}

	free(tmp_URL_str);
}

int main(int argc, char *argv[]) {
	int argv_count = 1;
	URL = argv[argv_count];
	URL_length = strlen(argv[argv_count]);

	is_URL_legal(URL);
	display_URL_dir(URL);
	display_URL_search(URL);
	return 0;
}
