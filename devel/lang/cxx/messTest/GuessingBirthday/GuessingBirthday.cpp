#include<iostream>
using namespace std;

/*
 * There are 5 sets of numbers, which are between 1 and 31;
 * By asking  question 'is your birthday in such set?' 5 times in these sets,
 * the program can get the actually birthday.
 *
 * These 5 sets are designed to implement such functionality:
 * The birthday is the sum of the first numbers in the sets where the day appears.
 * Each set includes 16 numbers.
 *
 * Here is the formula:
 * int SetFirstNum[5]; is an array for presenting the First Number in each sets,
 * bool Module[5]; is the modules for each FirstNumSets, either 1 or 0, but one member is 1 at least.
 *
 * int day = 0;
 * for(int i = 0; i < 5; i++)
 *     day += SetFirstNum[i] * Module[i];
 *
 * Given the SetFirstNum[i] value, different value for Module[i] makes the 'day' different;
 * There are (2**5 - 1) == 31 kinds of combination.
 */
int main(int argc, char **argv){
    int day = 0; // day to be determined
    char answer;
    // prompt the user for Set1
    cout << "Is your birthday in Set1?" << endl;
    cout << " 1  3  5  7\n" <<
            " 9 11 13 15\n" <<
            "17 19 21 23\n" <<
            "25 27 29 31\n" << endl;
    cout << "Enter N/n for No and Y/y for Yes: ";
    cin >> answer;

    if(answer == 'Y' || answer == 'y')
        day += 1;

    // prompt the user for Set2
    cout << "Is your birthday in Set2?" << endl;
    cout << " 2  3  6  7\n" <<
            "10 11 14 15\n" <<
            "18 19 22 23\n" <<
            "26 27 30 31\n" << endl;
    cout << "Enter N/n for No and Y/y for Yes: ";
    cin >> answer;

    if(answer == 'Y' || answer == 'y')
        day += 2;

    // prompt the user for Set3
    cout << "Is your birthday in Set3?" << endl;
    cout << " 4  5  6  7\n" <<
            "12 13 14 15\n" <<
            "20 21 22 23\n" <<
            "28 29 30 31\n" << endl;
    cout << "Enter N/n for No and Y/y for Yes: ";
    cin >> answer;

    if(answer == 'Y' || answer == 'y')
        day += 4;

    // prompt the user for Set4
    cout << "Is your birthday in Set4?" << endl;
    cout << " 8  9 10 11\n" <<
            "12 13 14 15\n" <<
            "24 25 26 27\n" <<
            "28 29 30 31\n" << endl;
    cout << "Enter N/n for No and Y/y for Yes: ";
    cin >> answer;

    if(answer == 'Y' || answer == 'y')
        day += 8;

    // prompt the user for Set5
    cout << "Is your birthday in Set5?" << endl;
    cout << "16 17 18 19\n" <<
            "20 21 22 23\n" <<
            "24 25 26 27\n" <<
            "28 29 30 31\n" << endl;
    cout << "Enter N/n for No and Y/y for Yes: ";
    cin >> answer;

    if(answer == 'Y' || answer == 'y')
        day += 16;

    cout << "Your birthday is " << day << endl;
    return 0;
}
