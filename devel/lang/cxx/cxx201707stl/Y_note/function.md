# header functional
`#include<functional>`

+ bind();
    ```
    using namespace std::placeholders; // all placeholders
    using std::placeholders::_1; // single placeholder
    using std::placeholders::_2; // single placeholder

    func(string val, int size) { };
    string st = "concerto";
    auto fn = bind(func, _1, 6); // then second param can be omitted
    fn(st);
    ```
    + 传入bind的第二个param以及后面,会以同样的顺序传入第一param(func)
    + 传入新函数(fn)的param,第n个param就代表_n传入到bind那里
    + typical usage:
        + re-order parameters
        + set default parameters externally

+ ref(), cref()
    + 使用bind传入不为_n的参数时,默认是复制出新实例,
    + 只有加了ref(), cref()才能传入"原始的"引用
    ```c
    func(const string & left, string & right) { }
    string lt("left");
    string rt("right");
    auto fn(func, cref(lt), ref(rt));
    不加cref(),ref(), 函数会隐式复制出一份相应的实例,然后传入
    ```