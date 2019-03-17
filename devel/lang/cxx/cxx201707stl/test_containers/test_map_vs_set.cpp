#include<set>
#include<map>
#include<list>
#include<iostream>
#include<algorithm>
#include<utility>
using namespace std;

int map_vs_set(void) {
    set<int> myset;
    std::set<int>::iterator it;
    std::pair<set<int>::iterator, bool> set_ret;
    for(int i = 1; i <= 5; i++) {
        // set_ret.second indicates whether insert successfully
        set_ret = myset.insert(i * 10);
        cout << set_ret.second << " # " << *(set_ret.first) << endl;
    }
    cout << " ###### " << endl;
    for(const auto & elem : myset) {
        if(elem == 20) {
            myset.erase(elem);
            myset.insert(elem * 10);
        }
    }

    for(const auto & elem : myset)
        cout << elem << endl;

    cout << " ###### " << endl;

    cout << "--------" << endl;
    map<char, int> mary;
    mary['a'] = 10;
    mary['b'] = 25;
    mary['c'] = 33;
    mary['d'] = 42;
    for(const auto & elem : mary)
        cout << elem.first << " # " << elem.second << endl;

    mary.erase('a');
    for(const auto & elem : mary)
        cout << elem.first << " # " << elem.second << endl;
    cout << "--------\n";
    cout << mary.find('d')->second << endl;
}

int multimap_test(void) {
    multimap<string, int> mmp;
    mmp.insert({"Darkness", 20});
    mmp.insert({"Darkness", 30});
    mmp.insert({"Chaos", 48});
    mmp.insert({"Chaos", 76});

    cout << endl << "extract all pairs with a Key from a multimap" << endl;
#if 1 /* extract all pairs with a Key from a multimap */
    list<pair<string, int>> pl; // pair list

    auto keyCnt = mmp.count("Darkness");
    auto itStep = mmp.begin();
    for(int i = 0; i < keyCnt; i++) {
        itStep = find_if(itStep, mmp.end(),
                [](const pair<string, int> & p) {
                return (p.first == string("Darkness"));
                });
        pl.push_back(*itStep);
        itStep++;
    }

    for(const auto & elem : pl)
        cout << elem.first << " => " << elem.second << endl;
#endif
}

int main( int argc, char **argv ) {
    map_vs_set();
    //multimap_test();
    return 0;
}
