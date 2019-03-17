#include<forward_list>
#include<iostream>
using namespace std;

void f_list_test(void) {
    forward_list<int> il;
    srand(time(NULL));
    for(int i = 0; i < 10; i++)
        il.push_front(rand() % 30);

    for(const auto & elem : il)
        cout << elem << " ";
    cout << endl;

    /* remove the odd number in a forward_list */
    for(auto elem = il.before_begin(), elem_prev = elem; ; ) {
        elem_prev = elem;
        ++elem;

        if(elem == il.end())
            break;

        if(*elem % 2) {
            il.erase_after(elem_prev);
            elem = elem_prev;
        } else
            elem = ++elem_prev;
    }

    for(const auto & elem : il)
        cout << elem << " ";
    cout << endl;
}

int main( int argc, char **argv ) {
    f_list_test();
    return 0;
}
