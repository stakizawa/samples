#include <stdio.h>

void
print_calc(int a, int b, int (*func)(int, int))
{
	printf("%3d is generated from %3d and %3d\n", func(a,b), a, b);
}

int
sum(int a, int b)
{
    return a + b;
}

int
sub(int a, int b)
{
	return a - b;
}


#if 0
int
main(int argc, char **argv)
{
	int a = 10, b = 5;
	printf("%d + %d = %d\n", a, b, sum(a, b));
	printf("%d - %d = %d\n", a, b, sub(a, b));
	print_calc(a, b, sum);
	print_calc(a, b, sub);
}
#endif
