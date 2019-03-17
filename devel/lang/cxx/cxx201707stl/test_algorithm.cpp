/* algorithm _never_ change the size of container!!! */
#if 0 /* algorithm parameter patterns */
    alg(srcBegin, srcEnd, other args);
    alg(srcBegin, srcEnd, dest, other args);
    alg(begin1, end1, begin2, other args);
    alg(begin1, end1, begin2, end2, other args);
#endif

#if 0 /* algorithm catalog */
    + Non-modifying sequence operations
    + Modifying sequence operations
    + Partitions
    + Sorting
    + Binary Search(operating on partitioned/sorted ranges)
    + Merge(operating on sorted ranges)
    + Heap
    + Min/Max
#endif

#include<iostream>
#include<vector>
#include<array>
#include<list>
#include<chrono> // c++11 std-time-lib
#include<random> // random

#include<functional>
#include<algorithm>
#include<numeric>

using namespace std;


template<class InputIterator>
void cout_container(InputIterator first, InputIterator last) {
    while(first != last) {
        cout << *first << ' ';
        ++first;
    }
    cout << '\n';
}

void nonModifyingSequenceOperations(void) {
    bool retBoolVal = false;
    // for_each()
    vector<int> eggs = { 3, 5, 7, 11, 13, 17, 19, 23};
    vector<int>::iterator it;

    for_each(eggs.begin(), eggs.end(), [](int & i){ ++i; });
    cout_container(eggs.begin(), eggs.end());

#if 1 // all_of(), any_of(), none_of(),  return true or false
    cout_container(eggs.begin(), eggs.end());
    retBoolVal = all_of(eggs.begin(), eggs.end(), [](int i){return i%2;});
    if(retBoolVal)
        cout << "All the elements are odd" << endl;

    retBoolVal = any_of(eggs.begin(), eggs.end(), [](int i){return i == 11;});
    if(retBoolVal)
        cout << "There is 11 in the range" << endl;

    retBoolVal  = none_of(eggs.begin(), eggs.end(), [](int i){return !(i%2);});
    if(retBoolVal)
        cout << "none of the elements is even" << endl;
#endif

#if 1 // finds() return iterator
    // find(), find_if(), find_if_not(), find_end(),
    // find_first_of(), adjacent_find(),

    eggs = { 2, 4, 3, 3, 5, 8, 3, 5, 9 };
    vector<int> noodles = { 3, 5 };

    retBoolVal = find(eggs.begin(), eggs.end(), 4) != eggs.end();
    if(retBoolVal)
        cout << "find() 4 " << endl;

    it = find_if(eggs.begin(), eggs.end(), [](int i){ return i == 4;});
    cout << "find_if() 4, return a iterator: "
        << *it << endl; // 4

    it = find_if_not(eggs.begin(), eggs.end(), [](int i){return !(i%2);});
    cout << "find_if_not() even number, return a iterator: "
        << *it << endl; // first 3 in eggs

    // find any one elements of noodles
    it = find_first_of(eggs.begin(), eggs.end(), noodles.begin(), noodles.end());
    cout << "find_first_of() noodles "
        << *it << endl;

    // find the last subsequence, vs search()
    // there is two noodles{3, 5} in eggs
    // {3, 5, 8}, {3, 5, 9}
    it = find_end(eggs.begin(), eggs.end(), noodles.begin(), noodles.end());
    cout << "find_end() noodles ";
    cout  << *it;       // 3
    ++it;
    cout << ' ' << *it; // 5
    ++it;
    cout << ' ' << *it; // 9
    cout << endl;

    it = adjacent_find(eggs.begin(), eggs.end());
    cout << "adjacent_find() " << *it; ++it;
    cout << ' ' << *it << endl;
#endif

#if 1 /* count(), count_if(), mismatch(), equal(), is_permutation() */
    /* search(), search_n() */
    eggs = { 10, 20, 30, 30, 20, 10, 10, 20 }; // 8 elements
    int cnt;
    cnt = count(eggs.begin(), eggs.end(), 10);
    cout << "count() 10 >> "
        << cnt      // 3
        << endl;

    cnt = count_if(eggs.begin(), eggs.end(), [](int i){return (i/10 == 2);});
    cout << "count_if() (i/10 == 2) >> "
        << cnt      // 8
        << endl;

    noodles = { 30, 30, 20 };
    it = search(eggs.begin(), eggs.end(),
            noodles.begin(), noodles.end());
    cout << "search()> " <<
        *it << ' ';
    it++;
    cout << *it << ' ';
    ++it;
    cout << *it << endl;

    it = search_n(eggs.begin(), eggs.end(), 2, 30);
    cout << "search_n() two 30s #> "
        << *it << ' ';
    it++;
    cout << *it << endl;

    vector<int> ivl = { 3, 7, 8, 6, 9, 0, 10 };
    list<int> ilr = { 3, 7, 8, 10, 0, 6, 9 };

    pair<vector<int>::iterator, list<int>::iterator> mypair;
    // problem about out-of range should be careful
    mypair = mismatch(ivl.begin(), ivl.end(), ilr.begin());
    cout << "mismatch() " << *(mypair.first) << " vs " << *(mypair.second) << endl;

    bool ret = equal(ivl.begin(), ivl.end(), ilr.begin());
    cout << "equal() " << boolalpha << ret << noboolalpha << endl;

    if(is_permutation(ivl.begin(), ivl.end(), ilr.begin()))
        cout << "is_permutation() return true" << endl;

#endif
}

void modifyingSequenceOperations(void) {
    int myints[] = { 10, 20, 30, 40, 50 };
    vector<int> myvec;
    auto f_print_myvec = [&](){
        for(const auto & elem : myvec)
            cout << elem << ' ';
        cout << endl;
    };

#if 0 /* copy(), copy_if(), copy_n(), copy_backward() */
    copy(myints, myints + 5, back_inserter(myvec));
    f_print_myvec();

    myvec.clear();
    copy_n(myints, 3, back_inserter(myvec));
    f_print_myvec();

    myvec.clear();
    copy_if(myints, myints+5, back_inserter(myvec),
            [](int i){ return !((i/10) % 2);} );
    f_print_myvec(); // myvec = { 20, 40 }

myvec.resize(myvec.size() + 4); // myvec = { 20, 40, 0, 0, 0, 0 }
copy_backward(myints+2, myints+5, myvec.end());
// myvec = { 20, 40, 0, 30, 40, 50 }
f_print_myvec();
#endif

#if 1 /* transform() */
vector<int> fo(myints, myints + 5);
myvec.clear();
myvec.resize(fo.size());

// transform(firts1, last1, result, unary-op)
transform(fo.begin(), fo.end(), myvec.begin(), [](int i) { return ++i; });
f_print_myvec();

// transform(first1, last1, first2, result, binary-op)
transform(fo.begin(), fo.end(), myvec.begin(), myvec.begin(), [](int l, int r) {return (l+r);});
f_print_myvec();
#endif

#if 1 /* unique(), rotate(), random_shuffle(), shuffle() */
// unique, it's highly suggested use unique() after sort()
myvec = { 10,20,20,20,30,30,20,20,10 };
myvec.resize(distance(myvec.begin(), unique(myvec.begin(), myvec.end())));
f_print_myvec();

/* rotate implement details
 * when middle  < (last + first) / 2
 * middle point to begin of b
 * {a} {b} {c} ->
 * {b} {a} {c} ->
 * {b} {c} {a}
 *
 * when middle  > (last + first) / 2
 * middle point to begin of {c}
 * {a} {b} {c} ->
 * {c} {b} {a} ->
 * {c} {a} {b}
 */
myvec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
f_print_myvec();
rotate(myvec.begin(), myvec.begin() + 3, myvec.end());
f_print_myvec();

//random_shuffle
random_shuffle(myvec.begin(), myvec.end());
f_print_myvec();

// shuffle
vector<int> sfl_iv = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
unsigned int seed =
    std::chrono::system_clock::now().time_since_epoch().count();
shuffle(sfl_iv.begin(), sfl_iv.end(), std::default_random_engine(seed));
for(const auto & elem: sfl_iv) cout << elem << ' '; cout << endl;
#endif

#if 0
swap();
swap_ranges();
iter_swap();
#endif
}

void partitions(void) {
    // is_partitioned()
    vector<int> is_pt_iv = { 1, 3, 5, 8, 10, 20 };
    vector<int> no_pt_iv = { 1, 8, 5, 3, 10, 20 };
    cout << "is_pt_iv: "; cout_container(is_pt_iv.begin(), is_pt_iv.end());
    cout << "no_pt_iv: "; cout_container(no_pt_iv.begin(), no_pt_iv.end());
    if(is_partitioned(is_pt_iv.begin(), is_pt_iv.end(), [](int i){return i%2;}))
        cout << "is_pt_iv{} is partitioned" << endl;
    if(! is_partitioned(no_pt_iv.begin(), no_pt_iv.end(), [](int i){return i%2;}))
        cout << "no_pt_iv{} is not partitioned" << endl;

    // partition()
    auto odd_bound = partition(no_pt_iv.begin(), no_pt_iv.end(), [](int i){return i%2;});

    cout << "odd elements(partition()): ";
    for(auto it = no_pt_iv.begin(); it != odd_bound; it++)
        cout << *it << ' ';
    cout << endl;

    cout << "even elements(partition()): " ;
    for(auto it = odd_bound; it != no_pt_iv.end(); it++)
        cout << *it << ' ';
    cout << endl;

    // partition_point()
    if(odd_bound == partition_point(no_pt_iv.begin(), no_pt_iv.end(), [](int i){return i%2;}))
        cout << "partions_point() returns here " << __LINE__ << endl;
    // statble_partion()

    // partition_copy()
    random_shuffle(no_pt_iv.begin(), no_pt_iv.end());
    list<int> odd_il, even_il;
    partition_copy(no_pt_iv.begin(), no_pt_iv.end(),
            back_inserter(odd_il), back_inserter(even_il),
            [](int i){return i%2;});

    cout << "odd elements(partition_copy(): ";
    for(const auto & elem: odd_il) cout << elem << ' ';
    cout << endl;

    cout << "even elements(partition_copy()): ";
    for(const auto & elem: even_il) cout << elem << ' ';
    cout << endl;

}

void sorts(void) {
    // sort()
    vector<int> dup_iv = { 10,20,20,20,30,30,20,20,10 };
    sort(dup_iv.begin(), dup_iv.end(), [](int l, int r){return (l > r);});
    dup_iv.resize(distance(dup_iv.begin(), unique(dup_iv.begin(), dup_iv.end())));
    cout_container(dup_iv.begin(), dup_iv.end());

    // stable_sort(); /* Sort elements preserving order of equivalents */
    vector<int> psort_iv = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    partial_sort(psort_iv.begin(), psort_iv.begin()+5, psort_iv.end());
    cout_container(psort_iv.begin(), psort_iv.end());

    // partial_sort_copy();
    vector<int> ivSortUntil= { 1, 2, 3, 4, 5, 4, 7, 8 };
    auto retIter = is_sorted_until(ivSortUntil.begin(), ivSortUntil.end());
    cout << "is_sorted_until() "
        << distance(ivSortUntil.begin(), retIter)
        << " value is " << *retIter
        << endl;
}

void bSearch(void) {
    vector<int> v = { 10, 10, 10, 20, 20, 20, 30, 30 };
    auto low = lower_bound(v.begin(), v.end(), 20); //
    auto up  = upper_bound(v.begin(), v.end(), 20); //

    cout_container(v.begin(), v.end());
    cout << "lower_bound(20) at position " << distance(v.begin(), low) << '\n';
    cout << "upper_bound(20) at position " << distance(v.begin(), up) << '\n';

    pair<vector<int>::iterator, vector<int>::iterator> bounds =
        equal_range(v.begin(), v.end(), 20);
    if(bounds.first == low && bounds.second == up)
        cout << "equal_range() returns pair(lower_bound, upper_bound)" << '\n';

    vector<int> v20(low, up); // each element is 20
    cout_container(v20.begin(), v20.end());
    // binary_search();
}

void merges(void) {
    vector<int>::iterator iv_it;
    vector<int> vResult;
    vector<int> first = { 5, 10, 15, 20, 25 };
    vector<int> second = { 50, 40, 30, 20, 10 };
    sort(first.begin(), first.end());   //  5, 10, 15, 20, 25
    sort(second.begin(), second.end()); // 10, 20, 30, 40, 50

    cout << "first : " << endl;
    for(const auto & elem : first) cout << elem << ' '; cout << '\n';
    cout << "second: " << endl;
    for(const auto & elem : second) cout << elem << ' '; cout << '\n';

    auto f_display_result = [&vResult]() {
        for(const auto & elem : vResult) cout << elem << ' ';
        cout << endl;
    };

#if 1 /* merge(), inplace_merge() */
    vResult.resize(first.size() + second.size());
    merge(first.begin(), first.end(),
            second.begin(), second.end(),
            vResult.begin());
    cout << "merge(): " << '\n';
    f_display_result();

    vResult.resize(first.size() + second.size());
    iv_it = copy(first.begin(), first.end(), vResult.begin());
    copy(second.begin(), second.end(), iv_it);
    inplace_merge(vResult.begin(),
            vResult.begin() + first.size(),
            vResult.end());
    cout << "inplace_merge(): " << '\n';
    f_display_result();
#endif

#if 1 /* set_ */
    // set_union()
    vResult.resize(first.size() + second.size());
    iv_it = set_union(first.begin(), first.end(),
            second.begin(), second.end(),
            vResult.begin());
    vResult.resize(distance(vResult.begin(), iv_it));
    cout << "set_union(): " << '\n';
    f_display_result();

    // set_intersection
    vResult.resize(first.size() + second.size());
    iv_it = set_intersection(first.begin(), first.end(),
            second.begin(), second.end(),
            vResult.begin());
    vResult.resize(distance(vResult.begin(), iv_it));
    cout << "set_intersection(): " << '\n';
    f_display_result();

    // set_difference()
    vResult.resize(first.size() + second.size());
    iv_it = set_difference(first.begin(), first.end(),
            second.begin(), second.end(),
            vResult.begin());
    vResult.resize(distance(vResult.begin(), iv_it));
    cout << "set_difference(): " << '\n';
    f_display_result();

    // set_symmetric_difference():
    vResult.resize(first.size() + second.size());
    iv_it = set_symmetric_difference(first.begin(), first.end(),
            second.begin(), second.end(),
            vResult.begin());
    vResult.resize(distance(vResult.begin(), iv_it));
    cout << "set_symmetric_difference(): " << '\n';
    f_display_result();
#endif

#if 1 /* includes */
    vector<int> container = {5,10,15,20,25,30,35,40,45,50};
    vector<int> containent = {10,20,30,40};

    cout_container(container.begin(), container.end());
    cout_container(containent.begin(), containent.end());

    if(includes(container.begin(), container.end(),
                containent.begin(), containent.end()))
        cout << '\n' << "container[] includes continent[]" << '\n';
#endif
}

void heaps(void) {
    /* init     : make_heap()
     * io       : push_heap(), pop_heap()
     * sort     : sort_heap()
     * check    : is_heap(), is_heap_until()
     */
    // make_heap()
    vector<int> iv = { 10, 20, 30, 5, 15 };
    auto f_display_iv = [&iv]() {
        for(const auto & elem : iv) cout << elem << ' ';
        cout << '\n';
    };
    make_heap(iv.begin(), iv.end());
    f_display_iv();
    cout << "heap head:" << *(iv.begin()) << '\n';
    cout << "--------" << endl;

    // pop_heap()
    pop_heap(iv.begin(), iv.end()); cout << "pop_heap()\n"; f_display_iv();
    iv.pop_back(); cout << "pop_back()\n"; f_display_iv();
    cout << "heap head:" << *(iv.begin()) << '\n';
    cout << "--------" << endl;

    // push_heap()
    iv.push_back(90); cout << "push_back()\n"; f_display_iv();
    push_heap(iv.begin(), iv.end()); cout << "push_heap()\n"; f_display_iv();
    cout << "heap head:" << *(iv.begin()) << '\n';
    cout << "--------" << endl;

    // sort_heap
    sort_heap(iv.begin(), iv.end());
    cout << "sort_heap()\n";
    f_display_iv();
}

template<class T> struct classTest {
    T operator()(T l, T r) { return (l + r*3); }
};

void numerics(void) {
    int init = 100;
#if 1 /* accumulate() */
    vector<int> nums = { 10, 20, 30 };
    cout << "default accumulate(): "
        << accumulate(nums.begin(), nums.end(), init) << '\n';
    cout << "accumulate() with minus: "
        << accumulate(nums.begin(), nums.end(), init, minus<int>()) << '\n';
    cout << "accumulate() with lambda: "
        << accumulate(nums.begin(), nums.end(), init,
                [](int l, int r) { return (l + 2*r); })
        << '\n';
    cout << "accumulate() with custom funtion object: "
        << accumulate(nums.begin(), nums.end(), init,
                classTest<int>())
        << '\n';
    // cout << classTest<int>()(10, 30); // function object usage
#endif
    // adjacent_difference()
    vector<int> val = { 101, 102, 103, 105, 109, 111, 112 };
    vector<int> result;
    result.resize(val.size());
    adjacent_difference(val.begin(), val.end(), result.begin());
    for(const auto & elem : result) cout << elem << ' '; cout << '\n';

#if 1 /* inner_product(), init+{series1.each + series2.each } */
    vector<int> series1 = { 10, 20, 30 };
    vector<int> series2 = {  1,  2,  3 };
    cout << "using default inner_product: "
        << inner_product(series1.begin(), series1.end(),
                series2.begin(), 0)
        << '\n';

    cout << "using functional operations: "
        << inner_product(series1.begin(), series1.end(),
                series2.begin(), init,
                minus<int>(), divides<int>())
        << '\n';

    cout << "using custom functions: "
        << inner_product(series1.begin(), series1.end(),
                series2.begin(), init,
                [](int l, int r){return l - r;},
                [](int l, int r){return l + r;})
        << '\n';
#endif

#if 1 /* partial_sum() */
    /*
     * Y0 = X0;
     * Y1 = X0 + X1
     * Y2 = X0 + X1 + X2
     * Yn = X0 + X1 + X2 + Xn
     */
    cout << "-^-^- important calculation -^-^-" << endl;
    vector<int> Xs = {1, 2, 3, 4, 5};
    vector<int> Ys(Xs.size());

    for(const auto & elem : Xs) cout << elem << ' '; cout << '\n';

    partial_sum(Xs.begin(), Xs.end(), Ys.begin());
    cout << "using default partial_sum():\n";
    for(const auto & elem : Ys) cout << elem << ' '; cout << '\n';

    partial_sum(Xs.begin(), Xs.end(), Ys.begin(), multiplies<int>());
    cout << "using partial_sum() with multiplies<T>():\n";
    for(const auto & elem : Ys) cout << elem << ' '; cout << '\n';
#endif

    // iota()
    vector<int> numsIOTA(10);
    iota(numsIOTA.begin(), numsIOTA.end(), 100);
    cout << "iota():\n";
    cout_container(numsIOTA.begin(), numsIOTA.end());
}

int main(int argc, char **argv) {
#if 0 /* rbegin(), rend()  test */
    vector<int> myvec = {10, 20, 30, 40, 50};
    if(*(--myvec.rend()) == *(myvec.begin()))
        cout << "--rend == begin ? " << boolalpha << true << noboolalpha << endl;
    if(*(myvec.rend()) == *(--myvec.begin()))
        cout << "rend == --begin ? (not safe access) " << boolalpha << true << noboolalpha << endl;
    if(*(myvec.rbegin()) == *(--myvec.end()))
        cout << "rbegin == --end ? " << boolalpha << true << noboolalpha << endl;
    if(*(--myvec.rbegin()) == *(myvec.end()))
        cout << "--rbegin == end ? (not safe access) " << boolalpha << true << noboolalpha << endl;
#endif
    // nonModifyingSequenceOperations();
    // modifyingSequenceOperations();
    partitions();
    // sorts();
    // bSearch();
    // merges();
    // heaps();
    // numerics();
    return 0;
}
