#include "kernel.h"

#define STACKSIZE 20
int main(void)
{
    k_stack_t test_stack;
    stack_data_t buffer[STACKSIZE] = {0};
    k_stack_t *ptest = &test_stack;

    initStack(ptest, buffer, STACKSIZE);

    
    readStack(ptest);
    printf("==================================\n");
    for (int i = 0; i < STACKSIZE + 1; i++) {
        pushStack(ptest, (stack_data_t)i);
    }
    
    readStack(ptest);
    printf("==================================\n");
    stack_data_t getdata = 0;
    for (int i = 0; i < STACKSIZE + 1; i++) {
        popStack(ptest, &getdata);
        printf("getdata = %ld\n", getdata);
    }
     printf("==================================\n");
    readStack(ptest);
    printf("==================================\n");
    for (int i = 0; i < STACKSIZE/2; i++) {
        pushStack(ptest, (stack_data_t)i + 100);
    }
   
    readStack(ptest);
     printf("==================================\n");


     for (int i = 0; i < STACKSIZE + 1; i++) {
        popStack(ptest, &getdata);
        printf("getdata = %ld\n", getdata);
    }
     printf("==================================\n");
    readStack(ptest);
    printf("==================================\n");
}
