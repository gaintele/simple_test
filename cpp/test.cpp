#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp> 
#include <zlib.h>
#include <pthread.h>

#include "test.h"
#include "basic_algo.h"
#include "simple_list.h"
#include "simple_stack.h"
#include "simple_queue.h"

#define SZ10 10
#define SZ1K 1024
#define SZ1M 1024*1024
#define SZ1G 1024*1024*1024

using namespace std;

int AssertSorted(const int& len, int array[])
{
    if (array == NULL)
    {
        return -1;
    }

    for (int i = 0; i < len-1; ++i)
    {
        if (array[i] > array[i+1])
        {
            return -2;
        }
    }

    return 0;
}

int test(void)
{
    map<int, vector<iituple> > queryRs;
    iituple ab;
    vector<iituple> vecRs;
    int mapCap = 0;

    for (int i = 0; i < SZ1K; i++)
    {
        vecRs.push_back(ab); 
    }

    for (int i = 0; i < SZ10; i++)
    {
        srand(time(NULL));
        for (int j = 0; j < SZ1G; j++)
        {
            usleep(1);
            int a = rand();
            queryRs[a] = vecRs;
            mapCap += (vecRs.size()*sizeof(iituple));
            if (mapCap > SZ1G)
            {
                printf("i=%d, j=%d, clear map capacity:%d, map size:%lu\n", i, j, mapCap, queryRs.size());
                mapCap = 0;
                //queryRs.clear();
                //map<int, vector<iituple> >().swap(queryRs);
                queryRs.erase(queryRs.begin(), queryRs.end());
            }
        }
    }
    return 0;
}

int TestBubbleSort(void)
{
    int len = 20;
    int array[len];
    srand(time(0));
    cout << "Test BubbleSort" << endl << "Before:";
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand() % 100;
        cout << array[i] << " ";
    }
    cout << endl;
    BubbleSort(len, array);
    cout << "After:";
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}

int TestSelectionSort(void)
{
    int len = 20;
    int array[len];
    srand(time(NULL));
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand() % 100;
        cout << array[i] << " ";
    }
    cout << endl;
    SelectionSort(len, array);
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    cout << "AssertSorted:" << (AssertSorted(len, array) == 0 ? "true" : "false") << endl;
    return 0;
}

int TestBinarySearch(void)
{
    int len = 20;
    int array[len];
    srand(time(0));
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand() % (len*5);
    }
    BubbleSort(len, array);
    cout << "Sorted Array:";
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    int index = rand() % len;
    int e = array[index] - 2;
    int pos = BinarySearch(e, len, array);
    cout << "Target:" << e << " Position:" << pos << endl;

    return 0;
}

int TestInsertionSort(void)
{
    int len = 200000;
    int array[len];
    cout << "Test InsertionSort" << endl << "Before:";
    for (int i = 0; i < len; ++i)
    {
        srand(time(0)+i);
        array[i] = rand() % len;
//        cout << array[i] << " ";
    }
//    cout << endl;
    time_t t_start = time(NULL);
    InsertionSort(len, array);
    time_t t_end = time(NULL);
//    cout << "After:";
//    for (int i = 0; i < len; ++i)
//    {
//        cout << array[i] << " ";
//    }
//    cout << endl;

    cout << "AssertSorted:" << (AssertSorted(len, array) == 0 ? "true" : "false")
         << " TimeCost:" << (t_end-t_start) << endl;

    return 0;
}

int TestQuickSort(void)
{
    int len = 20;
    int array[len];
    cout << "Test QuickSort" << endl << "Before:";
    for (int i = 0; i < len; ++i)
    {
        srand(time(0)+i);
        array[i] = rand() % len;
        cout << array[i] << " ";
    }
    cout << endl;
    time_t t_start = time(NULL);
    QuickSort(0, len-1, array);
    sleep(1);
    time_t t_end = time(NULL);
//    cout << "After:";
//    for (int i = 0; i < len; ++i)
//    {
//        cout << array[i] << " ";
//    }
//    cout << endl;

    cout << "AssertSorted:" << (AssertSorted(len, array) == 0 ? "true" : "false") 
         << " TimeCost:" << (t_end-t_start) << endl;

    return 0;
}

int TestHeapSort(void)
{
    int len = 50;
    int array[len];
    cout << "Test HeapSort" << endl << "Before:";
    srand(time(0));
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand() % 100;
        cout << array[i] << " ";
    }
    cout << endl;
    HeapSort(len, array);
    cout << "After:";
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    int asrt = AssertSorted(len, array);
    cout << "AssertSorted:" << (asrt == 0 ? "true" : "false") << endl;

    return asrt;
}

int TestMergeSort(void)
{
    int len = 20;
    int array[len];
    cout << "Test MergeSort" << endl << "Before:";
    srand(time(0));
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand() % 100;
        cout << array[i] << " ";
    }
    cout << endl;
    MergeSort(len, array);
    cout << "After:";
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    int asrt = AssertSorted(len, array);
    cout << "AssertSorted:" << (asrt == 0 ? "true" : "false") << endl;

    return asrt;
}

int TestGetMemory()
{
    char* p;
    printf("%p %p\n", &p, p);
    p = getMemory1();
    printf("%p %p\n", &p, p);
    cout << p << endl;

    char a = 'a';
    char A = 'A';
    cout << (int)a << " " << (int)A << endl;
    return 0;
}

char* getMemory1()
{
    char p1[] = "hello world";
    const char* p2 = "hello world";
    printf("%p %p\n", p1, p2);
    return const_cast<char*>(p2);
}

int TestPointer()
{
    char* p = new char;;
    printf("&p(%p) p(%p)\n", &p, p);
    char* q = p;
    printf("&q(%p) q(%p)\n", &q, q);
    p = new char;
    printf("&p(%p) p(%p)\n", &p, p);
    delete q;
    printf("&q(%p) q(%p)\n", &q, q);
    return 0;
}

int TestLog()
{
    for (int i = 0; i < 50; ++i)
    {
        double N = i*i;
        double x = log(N);
        cout << "log(" << N << ")=" << x << endl;
    }
    return 0;
}

int TestMaxSumSubSequnce()
{
    int len = 10;
//    int array[] = {1, 5, -3, 0, 9, 4, -10, 4, 7, -3};
    int array[] = {-6, -1, -3, -2, -9, -4, -10, -4, -7, -3};
    PrintArray(array, len);

    int max_sum = MaxSumSubSequnce(array, len);
    cout << "MaxSum=" << max_sum << endl;

    return 0;
}

int TestLongestAscSubSequnce()
{
    int len = 14;
//    int array[] = {1, 5, -3, 0, 9, 4, -10, 4, 7, -3};
    int array[] = {1, 9, 3, 8, 11, 4, 5, 6, 4, 1, 9, 10, 1, 7};
    PrintArray(array, len);

    int sub_array[len];
    int sub_len;
    LongestAscSubSequnce(array, len, sub_array, sub_len);
    PrintArray(sub_array, sub_len);

    return 0;
}

int TestVirtualClass()
{
    A* a = new A();
    A* b = new B();
    a->p();
    b->p();
    delete a;
    delete b;

    return 0;
}

int TestLongestCommonSubstring(void)
{
    char str1[1000],str2[1000];
    printf("请输入第一个字符串：");
    gets(str1);
    printf("请输入第二个字符串：");
    gets(str2);
    int len = longest_common_substring(str1, str2);
    printf("最长公共连续子串的长度为：%d\n",len);
    return 0;
}

int TestBinaryExchange()
{
//    char binary_in[] = "2a8f";
//    char binary_in[] = "10101010001111";
    char binary_in[] = "1011";
    int rbi = 2;
    char binary_out[128]; 
    int rbo = 16;
    AnyBinaryExchange(binary_in, rbi, binary_out, rbo);
    return 0;
}

int TestSwap()
{
    char a = 'a', b = 'b';
    cout << "a=" << a << ", b=" << b << endl;
    Swap(a, b);
    cout << "a=" << a << ", b=" << b << endl;
    return 0;
}

int TestMap()
{
    time_t now;
    time(&now);
    cout << now << endl;
    int len = 64*SZ1M;
    int* array = (int*)malloc(sizeof(int)*len);
    srand(time(0));
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand();
    }
    time(&now);
    cout << now << endl;

    boost::unordered_map<int, int> _map;
    for (int i = 0; i < len; ++i)
    {
        _map[array[i]] = i;
    }
    cout << "_map.size:" << _map.size() << endl;
    time(&now);
    cout << now << endl;

    int cnt = 0;
    boost::unordered_map<int, int>::iterator it;
    for (int i = 0; i < len; ++i)
    {
        int item = array[i];
        it = _map.find(item);
        if (it != _map.end())
        {
            int index = it->second;
            ++cnt;
        }
    }
    time(&now);
    cout << now << ":" << cnt << endl;

    cnt = 0;
    for (int i = 0; i < len; ++i)
    {
        int item = array[i];
        if (_map.find(item) != _map.end())
        {
            int index = _map[item];
            ++cnt;
        }
    }
    time(&now);
    cout << now << ":" << cnt << endl;

    free(array);

    return 0;
}

int TestStringSize()
{
    int64_t skuid = 1000000000;
    int cnt = 2;
    int64_t timed = 7*24*3600;
    
    std::string log = boost::lexical_cast<std::string>(skuid) + ":" + boost::lexical_cast<std::string>(cnt) + ":" + boost::lexical_cast<std::string>(timed) + ",";
    log += boost::lexical_cast<std::string>(skuid+1) + ":" + boost::lexical_cast<std::string>(cnt) + ":" + boost::lexical_cast<std::string>(timed);
    cout << log << endl;
    const char* str = log.c_str();
    cout << log.size() << " " << log.length() << " " << strlen(str) <<  endl;

    uLong tlen = strlen(str)+1;
    uLong blen = tlen; //compressBound(tlen);
    char* buf = (char*)malloc(sizeof(char)*blen);
    //if(compress(buf, &blen, str, tlen) != Z_OK) {
    //    printf(stderr, "error\n");
    //}
    free(buf);

    return 0;
}

bool IsPrime(int nr)
{
    for (int d = 2; (d * d) < (nr + 1); ++d) {
        if (!(nr % d)) {
            return false;
        }
    }
    return true;
}

void PrintPrime()
{
    for (int i = 0; i < 50; ++i) {
        if (IsPrime(i)) {
            cout << i << endl;
        }
    }
}

void* foo(void* arg)
{
    int i = 0;
    while (1) {
        printf("child thread pid %d, tid %lu, cnt %d: hello world!\n", getpid(), (unsigned long)pthread_self(), i++);
        sleep(2);
    }

    return 0;
}

void TestMultiThread()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, foo, NULL);
    if (ret) {
        printf("pthread_create failed\n");
        return;
    }

    sleep(1);
    int i = 0;
    while (1) {
        printf("main  thread pid %d, tid %lu, cnt %d: hello world!\n", getpid(), (unsigned long)pthread_self(), i++);
        sleep(2);
    }

    pthread_join(tid, NULL);

    return;
}

void TestLinkList()
{
    LNode* head = LinkListCreate();
    //int array[] = {1, 9, 3, 8, 6, 4, 5, 6, 4, 1, 9, 0, 1, 7};
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15};
    int size = 14;

    LinkListInit(head, array, size);
    printf("LinkListSize:%d\n", LinkListSize(head));
    LinkListPrint(head);

    int insert_idx = 4;
    int e = 11;
    LinkListInsert(head, insert_idx, e);
    LinkListPrint(head);

    e = 16;
    LinkListPushFront(head, e);
    LinkListPrint(head);

    e = 0;
    LinkListPushBack(head, e);
    LinkListPrint(head);

    LinkListReverse(head);
    LinkListPrint(head);

    LinkListPopFront(head, e);
    LinkListPrint(head);

    LinkListPopBack(head, e);
    LinkListPrint(head);

    int delete_idx = 5;
    LinkListDelete(head, delete_idx, e);
    LinkListPrint(head);

    insert_idx = 5;
    LinkListInsert(head, insert_idx, e);
    LinkListPrint(head);

    int cross_idx = 7;
    printf("build ring, cross idx %d\n", cross_idx);
    LinkListBuildRing(head, cross_idx);
    LinkListPrint(head);

    int ci = LinkListDetechRing(head);
    printf("cross idx %d\n", ci);

    LinkListDestroy(head);

    return;
}

void TestSqStack()
{
    SqStack s;
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int size = 15;
    StackInit(&s, array, size);
    StackPrint(&s);

    printf("%d\n", StackCapacity(&s));
    printf("%d\n", StackSize(&s));

    int e;
    StackGetTop(&s, e);
    printf("%d\n", e);

    StackPush(&s, e);
    StackPrint(&s);

    StackPop(&s, e);
    StackPrint(&s);

    StackDestroy(&s);
    return;
}

void TestLinkQueue()
{
    LinkQueue<int> Q;
    return;
}
