#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char **argv ) {
    vector<int> vec  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    for(const auto elem: vec)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}

void radix_sort(vector<int> & v);

