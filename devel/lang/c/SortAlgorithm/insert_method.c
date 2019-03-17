#include "com_func.h"

void insert_sort(int *const target, int const head_suffix, int const tail_suffix) {
	signed key_index = head_suffix + 1;
	signed position = 0;
    int key;

	for(; key_index <= tail_suffix; key_index++) {
		position = key_index - 1;
        key = target[key_index];

        while(position >= 0 && target[position] > key) {
            target[position + 1] = target[position];
            position--;
        }
        target[position + 1] = key;
	}
}

int main(void) {
	int target[num_memb];
	init_array( target, num_memb);
	display_array( target, num_memb);
	insert_sort(target, 0, num_memb-1);
	display_array( target, num_memb);
	return 0;
}
