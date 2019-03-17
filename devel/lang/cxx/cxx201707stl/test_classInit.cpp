#include<iostream>
#include<string>
#include<functional>

using namespace std;

class ClsTest {
    private:
        int iVal;
        std::string sVal;
    public:
        ClsTest() {
            iVal = 0;
            sVal = "nil";
            cout << this->sVal << " ClsTest()\n";
        }

        ClsTest(int iVal_in, string sVal_in) :
            iVal(iVal_in), sVal(sVal_in) {
                cout << this->sVal << " ClsTest(int,string)\n";
            };

        // copy constructor
        ClsTest(const ClsTest & obj) {
            this->iVal = obj.iVal;
            this->sVal = obj.sVal;
            cout << this->sVal << " " << &obj << " copy-constructor " << this << "\n";
        }

        // reload assignment-operator
        ClsTest & operator=(const ClsTest & obj) {
            this->iVal = obj.iVal;
            this->sVal = obj.sVal;
            cout << this->sVal << " operator=\n";
            return *this;
        };
};

ClsTest func(ClsTest &tmp) {
    cout << __LINE__ << " " << &tmp << endl;
    return tmp;
}

void entry(void) {
    cout << "\n----------\n";
    function<ClsTest(ClsTest &)> f = [&](ClsTest &tmp) {
        return tmp;
    };

    ClsTest x = { 2046, "2046" };
    cout << &x << " -\n";

    ClsTest y;
    cout << "-\n";

    y = f(x);
    /*
     * first copy-constructor:
     *      from x to special-lambda-stack
     * second copy-constructor:
     *      from special-lambda-stack to input-param in f
     * third copy-constructor:
     *      from input-param to func()-previous-stack, which is entry()
     *
     * operator= : returned-object in entry, perform `operator=` to y
     */
    cout << "-\n";

    y = func(x);
    /*
     * first copy-constructor:
     *      from x to input-param in func()
     * second copy-constructor:
     *      from input-param to func()-previous-stack, which is entry()
     *
     * operator= : returned-object in entry, perform `operator=` to y
     */
    cout << "-\n";
}

int main(int argc, char **argv) {
    /* 0 */
    ClsTest a(10, "Darkness");
    // never call `operator=`, as optimization
    // same as previous init-method
    ClsTest a2 = {20, "concerto" };

    /* 1 */
    ClsTest a3;
    a3 = {20, "concerto" }; // call `operator=`
    cout << "\n----------\n";

    /* 2 */
    ClsTest b = a; // is equal to `ClsTest b(a);`
    ClsTest b2(a);
    cout << "\n----------\n";

    /* 3 */
    ClsTest c;
    ClsTest c2 = ClsTest(); // stupid writing!!
    cout << "\n----------\n";

    entry();
    return 0;
}
