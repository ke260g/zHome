# Copy and Move Issue
### class copy initialization
```c
    /* five init types */
    string dots(10, '.'); 		        // direct init
    string s(dots); 			        // direct init
    string s2 = dots; 			        // copy init
    string null_book = "9-9999-99"; 	// copy init
    string nines = string(100, '9'); 	// copy init
```
### copy, copy-assignment, move, move-assignment
```c
class StrVec {
    public:
    StrVec(); // constructor, default-able
    StrVec(const StrVec&);                  // copy, default-able
    StrVec & operator=(const StrVec &);     // copy assignment, default-able
    StrVec(StrVec &&) noexcept;             // move
    StrVec & operator=(StrVec &&) noexcept; // move assignment
    StrVec(); // desctrutor, default-able
};
```

+ when we do not define a copy constructor for a class</br>
the compiler synthesizes one for us.
+ **the synthesized copy constructor** for some classes prevents us</br>
from copying objects of that class type.
+ most classes should define **either implicityly or explicitly** </br>
the default and copy constructors and the copy-assignment operator.

### move circumstance
+ IO objects, like fstream
+ **unique_ptr** objects
+ **realloc()** like operation
