#ifndef _BASIC_STRUCT_H_
#define _BASIC_STRUCT_H_

#include <sys/types.h>
#include <stdio.h>

typedef struct LNode
{
    int data;           //头指针中存储链表的长度
    struct LNode* next;
}LNode, *LinkList;

LNode* LinkListCreate()
{
    LNode* head = (LNode*)malloc(sizeof(LNode));
    head->data = 0;
    head->next = NULL;

    return head;
}

int LinkListInit(LNode* head)
{
    if (!head) return -1;

    int e = 0;
    while (scanf("%d", &e))
    {
        LNode* p = (LNode*)malloc(sizeof(LNode));
        p->data = e;
        p->next = head->next;
        head->next = p;
        head->data++;
    }

    return 0;
}

int LinkListInit(LNode* head, int array[], int size)
{
    if (!head) return -1;

    for (int i = 0; i < size; ++i)
    {
        LNode* p = (LNode*)malloc(sizeof(LNode));
        p->data = array[i];
        p->next = head->next;
        head->next = p;
        head->data++;
    }

    return 0;
}

void LinkListPrint(LNode* head)
{
    if (!head) return;

    printf("LinkList:");
    int size = head->data;
    LNode* p = head->next;
    while (p && size--)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    return;
    
}

void LinkListDestroy(LNode* head)
{
    if (!head) return;

    int size = head->data;
    LNode* p = head->next;;

    while (p && size--)
    {
        LNode* c = p;
        p = p->next;
        free(c);
        c = NULL;
    }
    free(head);
    head = NULL;

    return;
}

int LinkListSize(LNode* head)
{
    if (!head) return 0;

    return head->data;
}

int LinkListPushFront(LNode* head, int e)
{
    if (!head) return -1;

    LNode* n = (LNode*)malloc(sizeof(LNode));
    n->data = e;
    n->next = head->next;
    head->next = n;

    head->data++;

    return 0;
}

int LinkListPushBack(LNode* head, int e)
{
    if (!head) return -1;

    LNode* p = head;
    while (p->next) p = p->next;
    LNode* n = (LNode*)malloc(sizeof(LNode));
    n->data = e;
    n->next = p->next;
    p->next = n;

    head->data++;

    return 0;
}

int LinkListInsert(LNode* head, int i, int e)
{
    if (!head) return -1;

    int j = 0;
    LNode* p = head->next;
    while (p && j < i-1)
        p = p->next, ++j;

    if (!p) return -1;

    LNode* n = (LNode*)malloc(sizeof(LNode));
    n->data = e;
    n->next = p->next;
    p->next = n;

    head->data++;

    return 0;
}

//////////////////
int LinkListReverse(LNode* head)
{
    if (!head) return -1;

    LNode* pre = NULL;
    LNode* p = head->next;
    while (p)
    {
        LNode* cur = p;
        p = p->next;
        cur->next = pre;
        pre = cur;
    }

    head->next = pre;
    return 0;
}

int LinkListBuildRing(LNode* head, int i)
{
    if (!head || i < 0 || i >= head->data) return -1;

    int j = 0;
    LNode* entry = NULL;
    LNode* p = head;
    while (p->next)
    {
        p = p->next;
        if (j == i)
            entry = p;
        ++j;
    }

    if (!entry || entry == p) return -1;

    p->next = entry;

    return 0;
}

int LinkListDetechRing(LNode* head)
{
    if (!head) return -1;

    size_t i = 0;
    LNode* slow = head->next;
    LNode* fast = head->next;
    while (slow && fast && fast->next)
    {
        printf("step %d, slow %x, data %d, fast %x, data %d\n", 
                i, (unsigned)slow, slow->data, (unsigned)fast, fast->data);

        if (i > 0 && slow == fast)
            break;

        slow = slow->next;
        fast = fast->next->next;
        ++i;
    }

    if (slow != fast) return -1;

    i = 0;
    LNode* p = head->next;
    while (p && slow && p != slow)
    {
        p = p->next;
        slow = slow->next;
        ++i;
    }

    return i;
}


#endif
