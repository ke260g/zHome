#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char **argv ) {
    vector<int> v  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    void sortInsertEasy(vector<int> & v);
    sortInsertEasy(v);

    for(const auto elem: v)
        cout << elem << ", ";

    return 0;
}

void sortInsertEasy(vector<int> & v) {
    for(int i = 1; i < v.size(); i++) {
        if(v[i-1] > v[i]) {
            int key = v[i];
            int j = i - 1;
            for(; j > -1; j--) {
                v[j + 1] = v[j];
                if(v[j] < key)
                    break;
            }
            v[j + 1] = key;
        }
    }
}
