# c++ advance learning
### OOP
+ **derivation access specifier** does not affect the derived class</br>
but the objects of the derived class.
+ dynamic binding happens when a virtual function is called</br>
through a reference(or a pointer) to a base class
+ static member defined inside classes should be defined externally
```c
    class cls {
        static int val; // only means being declared but not defined
    };
    // static int cls::val; // error
    int cls::val; // ok 
```
### function 修饰符
+ `noexcept` keyword, avoid function **throw exception**
+ `override` keyword, tell compiler function is overriding the virtual one in base-class
+ `final` keyword, avoid derived class overriding member function
+ `explicit` 在class构造函数只有一个非default-parameter时才有用
```c
    // CxString's constructor 加了explicit keyword
    CxString string1(24);     // ok, direct initialization
    CxString string2 = 10;    // error, explicit prevents implicitly converting
    CxString string3;         // error, do not have default constructor
    string1 = 2;              // error, explicit prevents implicitly converting
    string2 = 3;              // error, explicit prevents implicitly converting
    string3 = string1;        // ok when overload '=', otherwise error
```

### string details
+ string = string 是深复制，QString 是浅复制
+ 用iterator以for形式访问string，vector，map等时，用auto超级方便
+ string 的 末iterator是空, 即::end()为"\0"
+ 用两个iterator定义范围初始化string时,第二个iterator会被转为"\0"
```c
    string srcSTR("hello");
    auto delim = find(srcSTR.begin(), srcSTR.end(), 'o');
    string dstSTR(srcSTR.begin(), delim);
    cout << dstSTR << endl; // display "hell"
```
+ string iterator 的特性在insert(),assign()也会体现

### file to string
```c
std::ifstream inFile("filename");
std::stringstream buffer;
buffer << inFile.rdbuf();
std::string fstr = buffer.str();
```

### lambda
+ specify the return type
    `[](int i) -> long { return (long)i; };`
+ capture list:
    + `[]`, empty
    + `[names, ...]`, capture as value
    + `[&names, ...]`, capture as reference
    + `[&]`, all variables from enclosing function as reference
    + `[=]`, all variables from enclosing function as value
    + `[&, identiferList]`</br>
        only identiferList captured as value, the others as reference
    + `[=, referenceList]`</br>
        only referenceList captured as reference, the others as value

### shared\_ptr pitfalls
+ don't shared\_ptr::reset() object itself
+ don't delete pointer returned from shared\_ptr::get()
+ don't init/reset() smart pointer with shared\_ptr::get()
+ need to pass a delete-func when points to a resource
    + 即class的析构函数没有delete构造或操作时所申请的资源
+ shared\_ptr默认不支持数组的delete, 需要传delete-func
    + `shared_ptr<int> p(new int[2]{30, 40}, [](int *p) { delete [] p;});`
+ 不该用shared_ptr 的场景: 大量小数据