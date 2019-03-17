/*
 * many details about l-value / r-value
 */
#include<iostream>
#include<utility>
using namespace std;

class cls {
    public:
        int & val() { return Val; }
        cls(const int & inVal):Val(inVal) { };
        int & get() & { return Val; }; // ::get() = 100;
        // int getValConst() & const { }; // error order
        int getValConst() const & { };
    private:
        int Val;
};

int & func(void) {
    int *a = new int(10);
    return *a;
}

int entry(void) {
#if 0
    all variables are l-value
    all impilicit data are r-value

    (l-value * 42) is an r-value
    30 is an r-value
    const char *s = "ooo"; //is an r-value
    int i; // then i is an l-value

    int & i;        // l-value reference        => can bind to l-value
    const int & i;  // const l-value reference  => can bind to r-value
    int && i;       // r-value reference        => can bind to r-value
#endif
    int i = 10;
    int & r = i;                // ok: r refers to i, like (*r = &i)
    // int && rr = i;           // error: can't bind an r-value reference to an l-value

    // int & r2 = i * 42;        // error: i*42 is a r-value
    const int & r3 = i * 42;     // ok: bind const l-value reference r-value
    int && rr2 = i * 42;         // ok: bind r-value reference to r-value
    // int && rr3 = rr2;         // error: rr2 is an l-value
    int && rr3 = std::move(rr2);
    // ok: std::move() returns an r-value reference of the given object,
    // which is an l-value, then the given object's value is undefined.
    // However, it consume the performance

    cout << rr2 << endl;
    int &&g = [](void)->int { int g = 10; return g;}();

    cls obj(2046);
    int j = obj.val();
    int & k = obj.val();
    obj.get() = 10099;
    cout << obj.val() << endl;

    return 0;
}

int main( int argc, char **argv ) {
    entry();
    return 0;
}
