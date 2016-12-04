#ifndef _SIMPLE_STACK_H_
#define _SIMPLE_STACK_H_

#include <stdio.h>

#define STACK_INIT_SIZE 100
#define STACK_INC_SIZE 10

typedef struct SqStack
{
    int* top;
    int* base;
    int capacity;
}SqStack;

int StackInit(SqStack* s)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;

    s->base = (int*)malloc(sizeof(int)*STACK_INIT_SIZE);
    if (!s->base) exit(OVERFLOW);
    s->top = s->base;
    s->capacity = STACK_INIT_SIZE;
    return 0;
}

int StackInit(SqStack* s, int array[], int size)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;

    int sz = STACK_INIT_SIZE;
    if (size > STACK_INIT_SIZE)
    {
        sz = STACK_INIT_SIZE 
        + ((size - STACK_INIT_SIZE)/STACK_INC_SIZE + 1) * STACK_INC_SIZE;
    }
    s->base = (int*)malloc(sizeof(int)*sz);
    if (!s->base) exit(OVERFLOW);
    s->top = s->base;
    s->capacity = sz;

    for (size_t i = 0; i < size; ++i)
        *(s->top++) = array[i];

    return 0;
}

int StackDestroy(SqStack* s)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;

    free(s->base);
    s->base = NULL;
    s->top = NULL;
    s->capacity = 0;

    return 0;
}

int StackSize(SqStack* s)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;
    return (s->top - s->base);
}

int StackCapacity(SqStack* s)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;
    return s->capacity;
}

int StackEmpty(SqStack* s)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;

    if (s->top == s->base)
        return 1;
    else
        return 0;
}

int StackPrint(SqStack* s)
{
    if (!s) return -1;

    int* p = s->base;
    while (p != s->top)
    {
        printf("%d ", *p);
        ++p;
    }
    printf("\n");
    
    return 0;
}

int StackGetTop(SqStack* s, int& e)
{
    printf("%s:\n", __FUNCTION__);
    if (!s || s->top == s->base) return -1;
    e = *(s->top - 1);
    return 0;
}

int StackPush(SqStack* s, int& e)
{
    printf("%s:\n", __FUNCTION__);
    if (!s) return -1;
    if (s->top - s->base >= s->capacity)
    {
        s->base = (int*)realloc(s->base, (s->capacity+STACK_INC_SIZE)*sizeof(int));
        s->top = s->base + s->capacity;
        s->capacity += STACK_INC_SIZE;
    }
    *(s->top++) = e;

    return 0;
}

int StackPop(SqStack* s, int& e)
{
    printf("%s:\n", __FUNCTION__);
    if (!s || s->top == s->base) return -1;
    
    e = *(--(s->top));

    return 0;
}
#endif
