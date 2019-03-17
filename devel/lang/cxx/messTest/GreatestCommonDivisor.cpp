#include<iostream>
using namespace std;

int main(int argc, char **argv){
    int gcd = 1, /* final result */
        tmp = 2;

    int num1, num2;
    cout << "Enter the first integer: ";
    cin >> num1;

    cout << "Enter the second integer: ";
    cin >> num2;

    while(tmp <= num1 && tmp <= num2) {
        if(num1 % tmp == 0 && num2 % tmp == 0)
            gcd = tmp;
        tmp++;
    }

    cout << "The greatest common divisor for " <<
        num1 << " and " << num2 << " is " << gcd;

    return 0;
}
