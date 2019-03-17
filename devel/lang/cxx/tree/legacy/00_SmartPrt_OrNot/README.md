# difference between using smart\_ptr and not
+ Mon, 19 Jun 2017 19:10:57 +0800

### at the very beginning of this project
+ the methods in the class(bTreeNode) are really simple
+ I try to re-implement with **smart pointer**
+ in *new_delete* is the version using **new and delete**
+ in *smart_ptr* is the version using **smart pointer**

### Notable points
+ *smart_ptr* can be a simple demo about how to use **smart pointer**
+ destructor of class(bTreeNode) in *new_delete* is a notable algorithm,</br>
    which is really simple but shows how to release a btree

### check memory overflow with valgrind
+ `$>_ valgrind --leak-check=summary --tool=memcheck ./a.out`
