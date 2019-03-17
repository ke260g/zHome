#include<iterator>
#include<iostream>
#include<type_traits>
#include<vector>
#include<list>
using namespace std;

// original test list
list<int> list_int;

void iterator_operations(void) {
    // advance(), distance()
    auto it = list_int.begin();
    advance(it, 4);
    cout << "it is >> " << *it << endl;

    cout << "begin to end >> " << distance(list_int.begin(), list_int.end()) << endl;
    cout << "end to begin >> " << distance(list_int.end(), list_int.begin()) << endl;
    cout << "it to begin >> " << distance(it, list_int.begin()) << endl;
    cout << "begin to it >> " << distance(list_int.begin(), it) << endl;

    // begin(), end()
    cout << *begin(list_int) << endl;
    cout << *(--list_int.end()) << endl;

    // prev(), next()
    cout << *next(begin(list_int))    << endl;
    cout << *prev((--list_int.end())) << endl;
}

void iterator_generators(void) {
    // back_inserter()
    list<int> bfoo_list;
    copy(list_int.begin(), list_int.end(),
            back_inserter(bfoo_list));
    for(const auto & elem : bfoo_list)
        cout << elem << " ";
    cout << endl;
    cout << "-------------------------" << endl;

    //  front_inserter()
    list<int> ffoo_list;
    copy(list_int.begin(), list_int.end(),
            front_inserter(ffoo_list));
    for(const auto & elem : ffoo_list)
        cout << elem << " ";
    cout << endl;
    cout << "-------------------------" << endl;

    // inserter()
    list<int> ifoo_list;
    copy(list_int.begin(), list_int.end(),
            inserter(ifoo_list, ifoo_list.begin()));
    for(const auto & elem : ifoo_list)
        cout << elem << " ";
    cout << endl;
    cout << "-------------------------" << endl;

    // back_insert_iterator()
    list<int> li_a;
    back_insert_iterator<list<int>> b_i_it(li_a);
    copy(list_int.begin(), list_int.end(), b_i_it);
    for(const auto & elem : li_a)
        cout << elem << " ";
    cout << endl;
    cout << "-------------------------" << endl;

    // front_insert_iterator()
    list<int> li_b;
    front_insert_iterator<list<int>> f_i_it(li_b);
    copy(list_int.begin(), list_int.end(), f_i_it);
    for(const auto & elem : li_b)
        cout << elem << " ";
    cout << endl;
    cout << "-------------------------" << endl;
}

void stream_iterators() {
#if 0 /* istream_iterator, needs console input */
    int value1, value2;
    istream_iterator<int> eos;           // end-of-stream iterator
    cout << *eos << endl;
    cout << "Please, insert two values: ";
    istream_iterator<int> iit(std::cin); // stdin iterator

    if(iit != eos)
        value1 = *iit;
    ++iit;
    if(iit != eos)
        value2 = *iit;

    cout << "value1 is " << value1 << endl;
    cout << "value2 is " << value2 << endl;
#endif
    ostream_iterator<int> out_it(cout, ", ");
    copy(list_int.begin(), list_int.end(), out_it);
    out_it;
    cout << endl;

    ostream_iterator<int> out_it2(cout, " # ");
    out_it2 = 20;
    out_it2 = 400;
    out_it2 = 3045;
    out_it2;
    cout << endl;
}

int main(int argc, char **argv) {
    // build original test list
    for(unsigned int i = 0; i < 10; i++)
        list_int.push_back(i*i);
    for(const auto & elem : list_int)
        cout << elem << " ";
    cout << endl;
    cout << "-------------------------" << endl;

    // iterator_operations();
    iterator_generators();
    // stream_iterators();
    return 0;
}
