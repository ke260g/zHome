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
    v = {3, 6, 2, 1, 5, 7, 9, 4, 9, 6, 5};

    void sortSelectEasy(vector<int> & v);
    sortSelectEasy(v);

    for(const auto elem: v)
        cout << elem << ", ";
    cout << '\n';

    v  = {1, 6, 2, 3, 5, 7, 9, 4, 9, 6, 5};

    void sortSelectEasy2(vector<int> & v);
    sortSelectEasy2(v);

    for(const auto elem: v)
        cout << elem << ", ";
    cout << '\n';

    return 0;
}
/* monadic method, each loop select one min value */
void sortSelectEasy(vector<int> & v) {
    for(int i = 0; i < v.size(); i++) {
        int min = i;
        for(int j = i + 1; j < v.size(); j++) {
            if(v[j] < v[min]) {
                min = j;
            }
        }
        swap(v[min], v[i]);
    }
}

#if 0 /* no great promotion */
/* dualistic method, each loop select min and max value */
void sortSelectEasy2(vector<int> & v) {
    for(int i = 0; i <= v.size()/2; i++) {
        int min = i,
            max = i;
        int j;
        for(j = i + 1; j <= v.size() - i - 1; j++) {
            if(v[min] > v[j]) {
                min = j;
                continue;
            }
            if(v[max] < v[j]) {
                max = j;
            }
        }
        swap(v[i], v[min]);
        swap(v[j-1], v[max]);
    }
}
#endif
