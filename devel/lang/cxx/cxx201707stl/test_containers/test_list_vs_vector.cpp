/*
 * using gprof
 * g++ -gp file.cpp -lc
 * ./a.out # then will generate a log-file
 * gprof a.out log-file
 */
#include<vector>
#include<list>
#include<iostream>
#include<time.h>
#include<mcheck.h>
#include<cstdlib>
using namespace std;

double timeBegin, timeEnd;

void list_push_back(list<int> & l) {
    timeBegin = clock();
    for(long i = 0; i < 10000000; ++i)
        l.push_back(0);
    timeEnd = clock();
    cout << "push_back of list: " << (1000 * (timeEnd - timeBegin) / CLOCKS_PER_SEC) << "ms\n";
}

void vector_push_back(vector<int> & v) {
    timeBegin = clock();
    for(long i = 0; i < 10000000; ++i)
        v.push_back(0);
    timeEnd = clock();
    cout << "push_back of vector: " << (1000 * (timeEnd - timeBegin) / CLOCKS_PER_SEC) << "ms\n";

}

void list_erase_begin(list<int> & l) {
    // erase begin of list
    timeBegin = clock();
    for(long i = 0; i < 10000000; ++i)
        l.erase(l.begin());
    timeEnd = clock();
    cout << "erase begin of list: " << (1000 * (timeEnd - timeBegin) / CLOCKS_PER_SEC) << "ms\n";
}

void vector_erase_begin(vector<int> & v) {
    // erase begin of vector
    timeBegin = clock();
    for(long i = 0; i < 200; ++i)
        v.erase(v.begin());
    timeEnd = clock();
    cout << "erase begin of vector: " << (1000 * (timeEnd - timeBegin) / CLOCKS_PER_SEC) << "ms\n";
}

void new_1000_pt(int **p, int len) {
    timeBegin = clock();
    for(int i = 0; i < len; ++i)
        p[i] = new int;
    timeEnd = clock();
    cout << "continue new 1000 times: " << (1000 * (timeEnd - timeBegin) / CLOCKS_PER_SEC) << "ms\n";

}

void del_1000_pt(int **p, int len) {
    timeBegin = clock();
    for(int i = 0; i < len; ++i)
        delete p[i];
    timeEnd = clock();
    cout << "continue new 1000 times: " << (1000 * (timeEnd - timeBegin) / CLOCKS_PER_SEC) << "ms\n";
}

int main( int argc, char **argv ) {
    setenv("MALLOC_TRACE","mtrace.dump", 1);
    mtrace();
    vector<int> v;
    list<int> l;

    int len = 1000;
    int *p[len];
    new_1000_pt(p, len);
    del_1000_pt(p, len);

    list_push_back(l);
    vector_push_back(v);

    list_erase_begin(l);
    vector_erase_begin(v);

    return 0;
}
