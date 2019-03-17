#if 0
This is a test program, helping to view several stack structure in the virtual memory
while function is being called.

It also helps to know the different so-called ask-address-implement methods
between x86 and x86_64.
Using #if 0 && #if 1.
Compile the proper code for your arch or emulating-arch

               Indeed, it is without any static_var inside the function or global var.

Adjust the amount of locale var inside the function (using #if 0 <= - => #if 1)
or arguments, then analyze the addresses.
#endif


#include <stdio.h>

void func(int argu1, int argu2, int argu3 ) {

#if 1
	int func_local_var_i = 5; printf("&func_local_var_i == %p\n", &func_local_var_i);
#endif
#if 1
	int func_local_var_j = 10; printf("&func_local_var_j == %p\n", &func_local_var_j);
#endif
#if 1
	int func_local_var_k = 20; printf("&func_local_var_k == %p\n", &func_local_var_k);
#endif
#if 1
	int func_local_var_l = 30; printf("&func_local_var_l == %p\n", &func_local_var_l);
#endif
#if 1
	int func_local_var_m = 40; printf("&func_local_var_m == %p\n", &func_local_var_m);
#endif
#if 1
	int func_local_var_n = 50; printf("&func_local_var_n == %p\n", &func_local_var_n);
#endif
	printf("&argu1 == %p\n", &argu1);
	printf("&argu2 == %p\n", &argu2);

#if 1                   // for x86_64
	printf("*(&argu1+8) == %d\n", *(&argu1+8));
	printf("*(&argu1+7) == %d\n", *(&argu1+7));
	printf("*(&argu1+6) == %d\n", *(&argu1+6));
	printf("*(&argu1+5) == %d\n", *(&argu1+5));
	printf("*(&argu1+4) == %d\n", *(&argu1+4));
	printf("*(&argu1+3) == %d\n", *(&argu1+3));
	printf("*(&argu1+2) == %d\n", *(&argu1+2));
	printf("*(&argu1+1) == %d\n", *(&argu1+1));

	printf("These are the code for x86_64,\n"
	       "If you're in a x86_64 arch,\n"
	       "Do not compile with x86-emulating.\n");
	printf("sizeof(void *) == %d\n", sizeof(void *));
	printf("sizeof(int)    == %d\n", sizeof(int));
#endif
#if 0                   // for x86
	printf("*(&argu1-5) == %d\n", *(&argu1-5));
	printf("*(&argu1-6) == %d\n", *(&argu1-6));
	printf("*(&argu1-7) == %d\n", *(&argu1-7));
	printf("*(&argu1-8) == %d\n", *(&argu1-8));
	printf("*(&argu1-9) == %d\n", *(&argu1-9));
	printf("*(&argu1-10) == %d\n", *(&argu1-10));

	printf("These are the code for x86 not x86_64,\n"
	       "If you're seeing this but compile in x86_64,\n"
	       "Please re-compile with x86-emulating.\n");
	printf("sizeof(void *) == %d\n", sizeof(void *));
	printf("sizeof(int)    == %d\n", sizeof(int));
#endif
	printf("\n");

}

int main(void)
{
	int integer1 = 19;
	int integer2 = 30;

	func(integer1, integer2, 30);
	printf("\n" "%p\n", &func);
	return 0;
}
