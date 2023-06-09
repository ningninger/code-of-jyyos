#include <stdio.h>
#include <string.h>

int main()
{
    char stack[5];
    char heap[5];
    char object[5];
    char mm[5];
    memset(stack, 0xcc, 4);stack[4] = '\0';
    memset(heap, 0xcd, 4);heap[4] = '\0';
    memset(object, 0xfd, 4);heap[4] = '\0';
    memset(mm, 0xdd, 4);mm[4] = '\0';

    printf(" stack = %s, \n heap = %s, \n object = %s, \n mm = %s;", stack, heap, object, mm);
    return 0;
}