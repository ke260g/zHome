#include<string>
#include<cstddef>
#include<memory>
#include<utility>
#include<iostream>
#include<functional>
#include<type_traits>
using namespace std;

class StrVec {
    public:
        StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) { }

        StrVec(const StrVec&);                  // copy
        StrVec & operator=(const StrVec &);     // copy assignment
        StrVec(StrVec &&s) noexcept;            // move
        StrVec & operator=(StrVec &&s) noexcept;// move assignment
        //////////////////
        void push_back(const std::string &);  // copy the elements, l-value assign
        void push_back(const std::string &&); // move the elements, r-value assign
        //////////////////
        StrVec &operator=(std::initializer_list<std::string>);
        std::string &operator[](std::size_t n) { return elements[n]; }
        //const std::string &operator[](std::size_t n) { return elements[n]; } // error
        // StrVec & operator++() {} StrVec & operator++(int) {}
        // StrVec & operator--() {} StrVec & operator--(int) {}
        // StrVec & operator*() const {}
        // StrVec * operator->() const { return & this->operator*(); }
        //////////////////

        size_t size() const { return first_free - elements; }
        size_t capacity() const { return cap - elements; }
        std::string *begin() const { return elements; }
        std::string *end() const { return first_free; }

        ~StrVec(); // destructor
    private:
        static std::allocator<std::string> alloc;
        void chk_n_alloc() { if (size() == capacity()) { reallocate(); }}
        std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
        void free();
        void reallocate();
        std::string *elements;
        std::string *first_free;
        std::string *cap;

};

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(const StrVec &s) {
    // call alloc_n_copy to allocate exactly as man elements as in s
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
    first_free = cap;
}

StrVec & StrVec::operator=(const StrVec &rhs) {
    // call alloc_n_copy to allocate exactly as many elements as in rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    cap = data.second;
    first_free = cap;
    return *this;
}

StrVec::StrVec(StrVec &&s) noexcept :
elements(s.elements), first_free(s.first_free), cap(s.cap) {
    s.elements = nullptr;
    s.first_free = nullptr;
    s.cap = nullptr;

};

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    if(this != &rhs) {
        free();
        this->elements = rhs.elements;
        this->first_free = rhs.elements;
        this->cap = rhs.cap;

        rhs.elements = nullptr;
        rhs.first_free = nullptr;
        rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::reallocate() {
    // we'll allocate space for twice as many elements as the current size
    auto newcapacity = size() ? 2 * size() : 1;
    // allcoate new memory
    auto newdata = alloc.allocate(newcapacity);
    // move the data from the old memory to the new
    auto dest = newdata; // points to the next free position in the new array
    auto elem = elements; // points to the next element in the old array
    for(size_t i = 0; i != size(); i++)
        alloc.construct(dest++, std::move(*(elem++)));
    free(); // free the old space once we've move
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

// l-value push_back
void StrVec::push_back(const string &s) {
    chk_n_alloc(); // ensure that there is room for another elements
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}

// r-value push_back
void StrVec::push_back(const string &&s) {
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

StrVec & StrVec::operator=(initializer_list<string> il) {
    // alloc_n_copy() allocates space and copies elements from the given range
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = data.second;
    cap = data.second;
    return *this;
}

pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e) {
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialzed_copy
    return { data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // may not pass deallocate a nullptr; if elements is nullptr,
    // there's no work to do
    if(elements) {
        // destroy the old elements in reverse order
        for(auto p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::~StrVec() { free(); }
// double the capacity of the StrVec if the space is not large enough
////////////////////////

int main( int argc, char **argv ) {
    StrVec obj;

    obj = {"concerto", "quartet"};
    cout << obj[0] << endl;
    cout << obj[1] << endl;

    function<int(int, int, int)> fn = [](int i, int j, int k) -> int { return i * j + k; };
    cout << fn(3, 5, 10) << endl;
    return 0;
}
