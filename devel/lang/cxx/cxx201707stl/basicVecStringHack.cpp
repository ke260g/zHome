#include<cstdio>
#include<cstdlib>
#include<cctype>

#include<iterator>
#include<string>
#include<iostream>

#include<vector>
#include<list>
#include<forward_list>
#include<deque>
#include<set>
#include<map>

#include<algorithm>
#include<functional>
#include<utility>

#include<memory>

using std::set;
using std::map;
using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::forward_list;
using std::list;

using std::remove_if;
using std::bind;
using std::ref;
using std::swap;

using std::shared_ptr;
using std::make_shared;

#if !(__cplusplus >= 201103L)
# error
#endif

class cls_dat {
    public:
        int idx;
        std::string val;
        explicit cls_dat(const int & idx, const std::string & val = "darkness") : idx(idx), val(val) { }
#if 1
        cls_dat & operator= (cls_dat & src) {
            idx = src.idx;
            val = src.val;
            return *this;
        }
#endif
};

void strAppend(string & src, string & append, const string & end) {
    src += append;
    src += end;
    append = "sonata";
}

using namespace std::placeholders;

int main(int argc, char **argv) {
#if 0 /* cls_dat */ /* emplace example */
    std::forward_list<cls_dat> arv;
    arv.emplace_front(2046, "poem");
    arv.emplace_front(1024, "symphony");
    arv.emplace_front(711, "concerto");
    for(const auto & elem: arv)
        std::cout << elem.idx << " " << elem.val << std::endl;
    printf("-------\n");

    std::deque<cls_dat> dqv;
    dqv.emplace_front(97, "opera");
    dqv.emplace_front(89, "viola");
    dqv.emplace_back(12, "cello");
    dqv.emplace_front(17, "woodwind");
    for(int i = 0; i < dqv.size(); i++)
        std::cout << dqv[i].idx << " " << dqv[i].val << std::endl;
#endif
    cls_dat a{ 10, "oo"};

#if 0 /* extract value from string */
    std::string orbits("365.24 29.53 3.14");
    std::string::size_type szL, szR;
    double earth = std::stod(orbits.substr(6), &szL);
    cout << szL << " earth " << earth << endl;
    cout << " ---> " << orbits.substr(szL) << " <--- " << endl;
    double moon = std::stod(&(orbits[szL]), &szR);
    cout << szR << " moon " << moon << endl;
    cout << " ---> " << orbits.substr(szR) << " <--- " << endl;
    double pi = std::stod(orbits.substr(szR), &szL);
    cout << "pi " << pi << endl;
#endif

#if 0 /* vector - string test */
    printf(" !!!!!!!!!!!!!!!! \n");
    std::vector<std::string> sv = {"darkness", "corruption", "chaos"};
    sv.insert(sv.begin(), "poetry");
    sv.push_back("implementation");

    printf("--------\n");
    std::vector<std::string> svdup(sv.rbegin(), sv.rend());
    for(auto & elem : svdup) {
        if(elem == "darkness")
            elem = "luminosity";
        cout << elem << endl;
    }
    cout << "--------\n";

    std::deque<std::string> sDeq(svdup.cbegin(), svdup.cend());
    for(const auto & elem : sDeq)
        cout << elem << endl;

    std::list<const char *> slist_l = { "violin", "viola", "cello" };
    vector<string> svec_r;
    svec_r.assign(slist_l.cbegin(), slist_l.cend());

    for(const auto & elem : svec_r)
        cout << elem << endl;
#endif

#if 0
    shared_ptr<int> p(new int[3]{30, 40, 50}, [](int *p) { delete [] p;});
    cout << (p.get())[0] << endl;
    cout << (p.get())[1] << endl;
    cout << (p.get())[2] << endl;
    //cls_dat obj_a = { 1}; // implicitly copy, error
    cls_dat obj_a = cls_dat(1); // with '=' overload
    cls_dat obj_b(1);
    cout << obj_a.idx << obj_a.val << endl;
#endif
    for(int j = 0; j < 9999; j++) {
        for(int k = 0; k < 1000; k++) {
            string tesString(std::move(string("gg"))); // low performance
            //string tesString(string("gg")); // high performance
        }
    }
    return 0;
}
