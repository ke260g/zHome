#include<vector>
#include<iostream>
using namespace std;

int sequence_search(vector<int> v, int key) {
    int i;

    for(i = 0; i < v.size(); i++) {
        if(v[i] == key)
            return i;
    }
    return -1;
}

// BigO(log2(n))
int binary_search(vector<int> v, int key) {
    int l = 0,              // low
        h = v.size() - 1;   // high
    int m;                  // middle

    // key not in range
    if(key < v[l] || key > v[h])
        return -1;

    while(l <= h) {
        m = (l + h) / 2;
        if(v[m] == key)
            return m;
        else if(v[m] > key)
            h = m - 1;
        else if(v[m] < key)
            l = m + 1;
    }
    return -1;
}

// BigO(log2(log2(n)))
int insert_search(vector<int> v, int key) {
    int l = 0,
        h = v.size() - 1;
    int m;

    // key not in range
    if(key < v[l] || key > v[h])
        return -1;

    while(l <= h) {
        m = l + (h - l) * (key - v[l]) / (v[h] - v[l]);

        if(v[m] > key)
            h = m - 1;
        else if(v[m] < key)
            l = m + 1;
        else
            return m;
    }
    return -1;
}

int s(vector<int> v, int key) {
}

// BigO(log2(n)) Bugs: not find every key
int fibonacci_search(vector<int> v, int key) {
    int len = v.size();
    int l = 0,
        h = len - 1;

    // key not in range
    if(key < v[l] || key > v[h])
        return -1;

    // build fibonacci array
    int F_max_size = 40;
    vector<int> F(F_max_size);
    F[0] = 0;
    F[1] = 1;
    for(int i = 2; i < F_max_size; i++)
        F[i] = F[i - 1] + F[i - 2];

    // find position of len in fibonacci
    int k = 0;
    while(F[k] - 1< len)
        k++;

    // construct a extended vector
    vector<int> t = v;
    t.resize(F[k] - 1, v[len -1]);

    while(l < h) {
        int m = l + (F[k -1] - 1);
        if(key < t[m]) {
            h = m - 1;
            k -= 1;
        } else if(key > t[m]) {
            l = m + 1;
            k -= 2;
        } else { // ==
            if(m < len)
                return m;
            else // m >= n, find the extend-value
                return len - 1;
        }
    }
    return -1;
}

int main( int argc, char **argv ) {
    vector<int> vec = { 1, 5, 17, 25, 33, 38, 46, 55, 69, 75, 99 };
    int key = 99;
    int pos;
    //pos = fibonacci_search(vec, key);
    pos = s(vec, key);
    cout << "found position is " << pos << endl;

    return 0;
}
