#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>

using namespace std;

int Swap(int& a, int&b)
{
    if (a == b)
        return -1;

    a ^= b;
    b ^= a;
    a ^= b;

    return 0;
}

int CopyArray(int len, int array[], int array_cp[])
{
    if (array == NULL || array_cp == NULL)
        return -1;

    while (--len >= 0)
        array_cp[len] = array[len];

    return 0;
}

void RandomArray(int len, int array[])
{
    if (array == NULL)
        return;

    int mod = len > 100 ? len : 100;
    srand(time(0));
    for (int i = 0; i < len; ++i)
    {
        array[i] = rand() % mod;
    }

    return; 
}

void PrintArray(int len, int array[])
{
    if (array == NULL)
        return;

    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    return; 
}

int CheckAscArray(int len, int array[])
{
    if (array == NULL)
        return -1;

    for (int i = 0; i < len-1; ++i)
    {
        if (array[i] > array[i+1])
            return -1;
    }

    return 0; 
}

int Merge(int low, int mid, int high, int array[], int tmp_array[])
{
    for (int i = low; i <= high; ++i)
        tmp_array[i] = array[i];

    for (int i = low, j = mid+1, k = low; k <= high; ++k)
    {
        if (i > mid)
            array[k] = tmp_array[j++];
        else if (j > high)
            array[k] = tmp_array[i++];
        else if (tmp_array[i] < tmp_array[j])
            array[k] = tmp_array[i++];
        else
            array[k] = tmp_array[j++];
    }

    return 0;
}

int MergeSort(int low, int high, int array[], int tmp_array[])
{
    if (low < high)
    {
        int mid = (low+high) >> 1;
        MergeSort(low, mid, array, tmp_array);
        MergeSort(mid+1, high, array, tmp_array);
        Merge(low, mid, high, array, tmp_array);
    }

    return 0;
}

int Partition(int low, int high, int array[])
{
    int p = array[low];
    int i = low, j = high;
    while (i < j)
    {
        while (i < j && array[j] >= p) j--;
        while (i < j && array[i] <= p) i++;
        Swap(array[i], array[j]);
    }
    Swap(array[i], array[low]);

    for (int i = low; i <= high ; ++i)
    {
        cout << array[i] << " ";
    }
    cout << ": array[" << i << "] : " << array[i] << endl;

    return i;
}

int Partition1(int low, int high, int array[])
{
    int p = array[high];
    int i = low;

    for (int j = low; j < high; ++j)
    {
        if (array[j] <= p)
        {
            Swap(array[i], array[j]);
            ++i;
        }
    }
    Swap(array[i], array[high]);

    for (int i = low; i <= high ; ++i)
    {
        cout << array[i] << " ";
    }
    cout << ": array[" << i << "] : " << array[i] << endl;

    return i;
}

int QuickSort(int low, int high, int array[])
{
    if (low >= high)
        return -1;

    int pivot = Partition(low, high, array);
    QuickSort(low, pivot-1, array);
    QuickSort(pivot+1, high, array);

    return 0;
}

int QuickSort1(int low, int high, int array[])
{
    if (low >= high)
        return -1;

    int pivot = Partition1(low, high, array);
    QuickSort(low, pivot-1, array);
    QuickSort(pivot+1, high, array);

    return 0;
}

void TestSort()
{
    time_t begin, diff;
    int len = 10;
    int array[len];
    RandomArray(len, array);
    PrintArray(len, array);
    int tmp_array[len];
    CopyArray(len, array, tmp_array);
//    MergeSort(0, len-1, array, cpy_array);
    QuickSort(0, len-1, array);
    PrintArray(len, array);
    cout << "CheckAscArray:" << (CheckAscArray(len, array) == 0 ? "true" : "false") << endl;
    cout << endl;

    PrintArray(len, tmp_array);
    QuickSort1(0, len-1, tmp_array);
    PrintArray(len, tmp_array);
    cout << "CheckAscArray:" << (CheckAscArray(len, array) == 0 ? "true" : "false") << endl;
    return;
}

int main(int argc, char** argv)
{
    TestSort();
    return 0;
}

