#ifndef _BASIC_ALGO_H_
#define _BASIC_ALGO_H_

//Swap two integer
int Swap(int& a, int& b);
int Swap(char& a, char& b);
void PrintArray(const int array[], const int& len);

//Bubble Sort
int BubbleSort(const int& len, int array[]);

int BinarySearch(const int& e, const int& len, int array[]);
int SelectionSort(const int& len, int array[]);

int InsertionSort(const int& len,  int array[]);

int Partition(int low, int high, int array[]);
int QuickSort(int low, int high, int array[]);

int MaxHeap(const int& idx, const int& len, int array[]);
int HeadAdjust(const int& idx, const int& len, int array[]);
int HeapSort(const int& len, int array[]);

int MergeSort(const int& len, int array[]);
int MSort(int low, int high, int array[], int temp_array[]);
int Merge(int low, int mid, int high, int array[], int tmp_array[]);

/*
 * 最大子数组和
 * End[i]=max(End[i-1]+arr[i], arr[i])
 * All[i]=max(End[i], All[i-1])
 */
int MaxSumSubSequnce(int array[], const int& len);

/*
 *最长递增子序列
 */
int LongestAscSubSequnce(int array[], const int len, int sub_array[], int& sub_len);

/*
 * 最长公共子串
 *          |-     0             xi!=yj
 *   c[i,j]=|_     c[i-1,j-1]+1  xi=yj
 */
int longest_common_substring(char *str1, char *str2);

/*
 * 最长公共子序列
 *         |-  0                         xi=yi=0
 * c[i,j]= |   c[i-1, j-1]+1             xi=yj
 *         |_  max(c[i, j-1], c[i-1, j]) xi!=yj
 */

bool AnyBinaryExchange(const char* binary_in, const int& rbi, char* binary_out, const int& rbo);

#endif

