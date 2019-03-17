#include "com_func.h"

int main(void) {
    int target[num_memb];

    init_array(target, num_memb);

    display_array(target, num_memb);
    quick_sort(target, 0, sizeof(target)/sizeof(target[0]) - 1);
    display_array(target, num_memb);
    return 0;
}
