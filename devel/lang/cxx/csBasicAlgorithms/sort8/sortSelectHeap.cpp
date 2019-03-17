#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char **argv ) {
    // vector<int> vec  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    vector<int> vec = {16, 7, 3, 20, 17, 8};
    void sortSelectHeap(vector<int> & v);
    sortSelectHeap(vec);

    for(const auto elem: vec)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}

static void swap(int & l, int & r) {
    int t = l;
    l = r;
    r = t;
}

static void heapAdjust(vector<int> & v, int i, int len) {
    // len is not the last-index
    if(i <= len/2 - 1) {
        int max = i;
        if(v[max] < v[2*i + 1])
            max = 2*i + 1;

        if(2*i + 2 < len) // out of range
            if(v[max] < v[2*i + 2])
                max = 2*i + 2;

        if(max != i) {
            swap(v[i], v[max]);
            heapAdjust(v, max, len);
        }
    }
}

void sortSelectHeap(vector<int> & v) {
    // build heap
    for(int i = v.size()/2 - 1; i >= 0; i--)
        heapAdjust(v, i, v.size());

    // sort
    for(int i = v.size() - 1; i > 0; i--) {
        swap(v[0], v[i]);
        heapAdjust(v, 0, i);
    }
}
