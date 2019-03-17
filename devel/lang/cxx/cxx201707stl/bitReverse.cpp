/*
 * bit reverse
 * generate a c/c++ array
 * value of each element is bit-reverse value of its index
 *
 * implement details:
 *      value -> bitset -> string -reverse->
 *      string -> bitset -> value
 * Note:
 *      typeName should be large enough for bit number,
 *      otherwise, behavior is undefined.
 */

#include<algorithm>
#include<bitset>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

/* It's highly recommended that
 * the array should be in the heap
 * and initialized at the beginning */
#define typeName "static unsigned char"

// Reverse the bit of the input value
// returns the new value
template <size_t BN> unsigned long bitReverse(
        const unsigned long val) {
    bitset<BN> bit;
    string str;

    bit = val;
    str = bit.to_string();
    reverse(str.begin(), str.end());
    bit = bitset<BN>(str);

    return bit.to_ulong();
}

// bit reverse array generate
// cout an array in c/c++,
// each element is the bit-reverse value of its index
template <size_t BN> void bitRevAryGen(
        const char *arrayName) {
    string tabs("\t");
    string space(" ");

    bitset<BN> b_Max;

    b_Max.set();
    unsigned long iMax = b_Max.to_ulong() + 1;
    unsigned long valn; // value new

    cout << typeName << " " << arrayName << "[" << iMax << "] = {" << endl;

    for(unsigned long i = 0; i < iMax; i++) {
        valn = bitReverse<BN>(i);
        //printf("\t%lu, // [%lu] %s to %s\n", nb.to_ulong(), i, s.c_str(), ns.c_str());
        cout << tabs << valn << ",";
        cout << tabs << "// [" << i << "] " << bitset<BN>(i) << " to " << bitset<BN>(valn) << endl;
    }
    cout << "};" << endl;
}

int main( int argc, char **argv ) {
    //cout << bitReverse<8>(128) << endl; // will be `1'
    //cout << bitReverse<8>(2) << endl; // will be `64'

    bitRevAryGen<8>("ary");
    return 0;
}
