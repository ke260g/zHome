#include<iostream>
#include<vector>
using namespace std;

void swap(int & l, int & r) {
    int t = l;
    l = r;
    r = t;
}

int main( int argc, char **argv ) {
    vector<int> v;

    v  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};
    void bubbleSort(vector<int> & v);
    bubbleSort(v);
    for(const auto elem: v)
        cout << elem << ", ";
    cout << '\n';

    v  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};
    void bubbleSort_2(vector<int> & v);
    bubbleSort_2(v);
    for(const auto elem: v)
        cout << elem << ", ";
    cout << '\n';

    v  = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};
    void bubbleSort_3(vector<int> & v);
    bubbleSort_3(v);
    for(const auto elem: v)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}



/* raw method, BigO(n ^ 2) */
void bubbleSort(vector<int> & v) {
    for(int j = v.size(); j > 0; j--) {
        int key = 0;
        for(int i = 0; i < j - 1; i++) {
            if(v[i] > v[i + 1]) {
                swap(v[i], v[i + 1]);
            }
        }
    }
}

/* use a flag to indicate a block of elements
 * have been sorted
 */
void bubbleSort_2(vector<int> & v) {
    for(int j = v.size(); j > 0; ) {
        int key = 0;
        for(int i = 0; i < j - 1; i++) {
            if(v[i] > v[i + 1]) {
                swap(v[i], v[i + 1]);
                key = i + 1;
            }
        }
        j = key; // to stop the loop earlier
    }
}

/* dualistic method,
 * find the min and max
 * inside a single loop
 * BigO( 0.5 * n ^ 2)
 */
void bubbleSort_3(vector<int> & v) {
    int min = 0;
    int max = v.size() - 1;
    int tmp, j;
    while(min < max) {
        for(j = min; j < max; j++)
            if(v[j] > v[j+1])
                swap(v[j], v[j+1]);
        max--;
        for(j = max; j > min; j--)
            if(v[j] < v[j-1])
                swap(v[j], v[j-1]);
        min++;

    }
}
