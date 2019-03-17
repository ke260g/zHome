#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) {
    void *handle;
    void (*func_pt)(int);
    char *error;

    // [1] load the dynamic-library to the mem
    handle = dlopen("./lib_dir/local_lib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\en", dlerror());
        exit(EXIT_FAILURE);
    }

    // [2] error clearing is recommand
    dlerror();    /* Clear any existing error */

    // [3] find the function in the loaded-dynamic-library
    func_pt = (void (*)(int))dlsym(handle, "real_func");

    // [4] recommand error checking, or will cause the program crash
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    // [5] invoke the real-function by the function-pointer
    func_pt(2046);

    // [6] unload the dynamic-library from the mem
    dlclose(handle);

    exit(EXIT_SUCCESS);
}
