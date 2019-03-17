#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

int main( int argc, char **argv ) {
    vector<int> vec  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    void sortSwapQuick(vector<int> & v);
    sortSwapQuick(vec);
    for(const auto elem: vec)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}

// return key index
int part(vector<int> & v, int l, int h) {
    // low-index, high-index(not the size)
    srand(rand() * time(NULL));
    int key = l + rand() % (h + 1 - l);
    while(l < h) {
        while(key < h && v[h] >= v[key])
            h--;
        swap(v[key], v[h]);
        key = h;

        while(l < key && v[l] <= v[key])
            l++;
        swap(v[l], v[key]);
        key = l;
    }
    return key;
}

void sort_quick_core(vector<int> &v, int l, int h) {
    // low-index, high-index(not the size)
    if(l < h) {
        int keyIdx = part(v, l, h);
        sort_quick_core(v, l, keyIdx - 1);
        sort_quick_core(v, keyIdx + 1, h);
    }
}

void sortSwapQuick(vector<int> & v) {
    sort_quick_core(v, 0, v.size() - 1);
}
