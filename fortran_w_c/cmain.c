#include <stdio.h>

void print_sum4_(int *, int *, int *, int *);
void __simple_MOD_print_sum3(int *, int *, int *);
int  __simple_MOD_sum3(int *, int *, int *);

int
main(int argc, char **argv)
{
    int a = 1, b = 2, c = 3, d = 4;
    int val;

    printf("call a fortran subroutine: print_sum4()\n");
    print_sum4_(&a, &b, &c, &d);

    printf("call a fortran module subroutine: simple.print_sum3()\n");
    __simple_MOD_print_sum3(&a, &b, &c);

    printf("call a fortran module function: simple.sum3()\n");
    val = __simple_MOD_sum3(&a, &b, &c);
    printf("%d + %d + %d = %d\n", a, b, c, val);

    return 0;
}
