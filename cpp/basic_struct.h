#ifndef _BASIC_STRUCT_H_
#define _BASIC_STRUCT_H_

#include <sys/types.h>
#include <stdio.h>

typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, *LinkList;

LNode* LinkListCreate()
{
    LNode* head = (LNode*)malloc(sizeof(LNode));
    head->next = NULL;

    return head;
}

int LinkListInit(LNode* head)
{
    if (NULL == head)
        return -1;

    int e = 0;
    while (scanf("%d", &e))
    {
        LNode* p = (LNode*)malloc(sizeof(LNode));
        p->data = e;
        p->next = head->next;
        head->next = p;
    }

    return 0;
}

void LinkListPrint(LNode* head)
{
    if (NULL == head)
        return;

    printf("LinkList:");
    LNode* p = head->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    return;
    
}

void LinkListDestroy(LNode* head)
{
    size_t size = 0;
    LNode* p = head;
    while (p != NULL)
    {
        LNode* c = p;
        p = p->next;
        delete c;
        c = NULL;
        ++size;
    }
    printf("free %d LNodes(include head)\n", size);

    return;
}

size_t LinkListSize(LNode* head)
{
    if (NULL == head)
        return 0;

    size_t size = 0;
    LNode* p = head->next;
    while (p != NULL) 
    {
        size++;
        p = p->next;
    }

    return size;
}

int LinkListInsert(LNode* head, int i, int e)
{
    if (NULL == head)
        return -1;

    int j = 0;
    LNode* p = head->next;
    while (p != NULL && j < i-1)
        p = p->next, ++j;

    if (NULL == p)
        return -1;

//    printf("i=%d, j=%d, data=%d\n", i, j, p->data);
    LNode* n = (LNode*)malloc(sizeof(LNode));
    n->data = e;
    n->next = p->next;
    p->next = n;

    return 0;
}

#endif
