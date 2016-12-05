#ifndef _SIMPLE_QUEUE_H_
#define _SIMPLE_QUEUE_H_

#include <stdio.h>

template<typename T> 
struct QNode
{
    T data;
    QNode<T>* next;
};

template<typename T>
class LinkQueue
{
public:
    LinkQueue();
    ~LinkQueue();

    bool empty() const;
    int size() const;

    bool dequeue(const T& e);
    bool enqueue(const T& e);

private:
    QNode<T>* front;
    QNode<T>* rear;

};

template<typename T>
LinkQueue<T>::LinkQueue()
{
    printf("%s:\n", __FUNCTION__);
    QNode<T> *qnode=new QNode<T>();
    qnode->next=NULL;
    front=rear=qnode;
}

template<typename T>
LinkQueue<T>::~LinkQueue()
{
    printf("%s:\n", __FUNCTION__);
}

template<typename T>
bool LinkQueue<T>::empty() const
{
    if (front == rear)
        return true;

    return false;
}

template<typename T>
int LinkQueue<T>::size() const
{
    QNode<T>* p = front;
    if(empty())
        return 0;
    else
    {
        int i=1;
        while(p->next != rear)
        {
            p=p->next;
            i++;
        }
        return i;
    }
}

template<typename T>
bool LinkQueue<T>::dequeue(const T& e) 
{
    if (empty())
        return false;

    QNode<T>* p = front->next;
    front->next = p->next;
    e = p->data;
    if(p == rear)
        rear = front;
    delete p;
    p=NULL;

    return true;
}

template<typename T>
bool LinkQueue<T>::enqueue(const T& e)
{
    QNode<T>* node = new QNode<T>;
    node->data = e;
    node->next = NULL;
    rear->next = node;
    rear = node;

    return true;
}

#endif
