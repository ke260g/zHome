#include "com_func.h"

int main(void) {
	int target[num_memb];
	init_array(target, num_memb);
	display_array(target, num_memb);
	merge_sort(target, 0, num_memb-1);
	display_array( target, num_memb);
	return 0;
}
