#include<iostream>
#include<vector>
using namespace std;

int main( int argc, char **argv ) {
    vector<int> vec  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    void sortzMerge(vector<int> & v);
    sortzMerge(vec);

    for(const auto elem: vec)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}

void merge_sort(vector<int> & v,
        vector<int> & r,
        int b, int e) {
    // @param b begin index
    // @param e end index
    if(b < e) {
        int m = (b + e) / 2;
        merge_sort(v, r, b, m);
        merge_sort(v, r, m + 1, e);

        int i = b,
            j = b,
            k = m + 1;
        while(j <= m && k <= e) {
            if(v[j] > v[k])
                r[i++] = v[k++];
            else
                r[i++] = v[j++];
        }

        while(j <= m)
            r[i++] = v[j++];
        while(k <= e)
            r[i++] = v[k++];

        for(int i = b; i <= e; i++) {
            v[i] = r[i];
        }
    }
}

void sortzMerge(vector<int> & v) {
    vector<int> r(v.size());
    merge_sort(v, r, 0, v.size() - 1);
}
