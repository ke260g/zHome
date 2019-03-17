#include<math.h>
#include<stdio.h>

#define INPUT 0xfda0000

void DisplaySizeFromHex(const int input) {
    int remainer = input,
        level = 0;

    char *LevelChar[] =
    {"Byte", "Kb", "Mb", "Gb", "Tb"};

    while(remainer > 1024 && level < 6) {
        remainer = remainer / 1024;
        level++;
    }

    printf("%d %s\n", remainer, LevelChar[level]);
}

int main(int argc, char **argv) {
    DisplaySizeFromHex(INPUT);
    return 0;
}
