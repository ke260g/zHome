#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char **argv ) {
    vector<int> vec  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    void sortInsertShell(vector<int> & v);
    sortInsertShell(vec);

    for(const auto elem: vec)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}

void sortInsertShell(vector<int> & v) {
    int N = v.size();
    for(int div = N / 2; div > 0; div /= 2) {
        for(int i = 0; i < div; i++) { // each group
            // do insert sort
            for(int j = i + div; j < N; j += div) {
                int key = v[j];
                int k = j - div;
                for(; k > i - 1; k -= div) {
                    v[k + div] = v[k];
                    if(v[k] < key)
                        break;
                }
                v[k + div] = key;
            }
        }
    }
}
