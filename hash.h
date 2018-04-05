#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define MAX 6000
#define N 823
#define TEST_NUM 3// amount of tests of current function
#define RAND srand(time(0))
                                                    //hash   key  comp   copy
void h_gen_rand(void * hash, int max, void (* func) (void *, int, int *, int *)) { //testing func
    int i;
    int cop_sum, cmp_sum;
    cop_sum = cmp_sum = 0;

    for(i = 0; i < max; i++)
        func(hash, rand() % max, &cmp_sum, &cop_sum);

    printf("~Copies: %d\n", cop_sum);
    printf("~Compares: %d\n", cmp_sum);
}