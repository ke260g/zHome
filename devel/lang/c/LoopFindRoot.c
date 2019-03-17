#include<math.h>
#include<stdio.h>
#include<time.h>

int main(void) {
	FILE *dev_null = fopen("/dev/null", "w");
	unsigned int i;
	double result;
	time_t timeOld, timeCurrent;
	while(1) {
		time(&timeOld);
		for(i = 1; i < 20 * 1000 * 1000; i++) {
			//result = sqrt(i);
			result = log(i);
			fwrite(&result, 4, 1, dev_null);
		}
		time(&timeCurrent);
		printf("/* ==> stop to sqrt, %s", ctime(&timeCurrent));
		printf("/* ==> have elapsed %lf second.\n\n", difftime(timeCurrent, timeOld));
	}
	return 0;
}
