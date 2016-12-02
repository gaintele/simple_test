#ifndef _TEST_H_
#define _TEST_H_
#include <iostream>

struct iituple {
        int a;
        int b;
};

struct redisObj {
	int a;
	void* ptr;
};

class A
{
public:
    void p() {std::cout << "A" << std::endl;}
};

class B:public A
{
public:
    void p() {std::cout << "B" << std::endl;}
};

int test(void);

int AssertSorted(const int& len, int array[]);
int TestBubbleSort(void);
int TestBinarySearch(void);
int TestSelectionSort(void);
int TestInsertionSort(void);
int TestQuickSort(void);
int TestHeapSort(void);
int TestMergeSort(void);
int TestGetMemory();
char* getMemory1();
int TestPointer();
int TestLog();
int TestMaxSumSubSequnce();
int TestLongestAscSubSequnce();
int TestVirtualClass();
int TestLongestCommonSubstring(void);
int TestBinaryExchange();
int TestSwap();
int TestMap();
int TestStringSize();
bool IsPrime(int nr);
void PrintPrime();
void* foo(void* arg);
void TestMultiThread();

#endif
