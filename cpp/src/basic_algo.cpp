#include <iostream>
#include <assert.h>
#include "stdio.h"  
#include "string.h"  
#include "stdlib.h" 
#include "basic_algo.h"
#include <stack>

using namespace std;

void PrintArray(const int array[], const int& len)
{
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int Swap(int& a, int& b)
{
    if (a == b)
        return 0;

    a ^= b;
    b ^= a;
    a ^= b;

    return 0;
}

int Swap(char& a, char& b)
{
    if (a == b)
        return 0;

    a ^= b;
    b ^= a;
    a ^= b;

    return 0;
}

int BubbleSort(const int& len, int array[])
{
    if (array == NULL)
    {
        return -1;
    }

    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < (len-i-1); ++j)
        {
            if (array[j] > array[j+1])
            {
                swap(array[j], array[j+1]);
            }
        }
    }

    return 0;
}

int BinarySearch(const int& e, const int& len, int array[])
{
    if (array == NULL)
    {
        return -2;
    }

    int low = 0, high = len - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (e == array[middle])
        {
            return middle;
        }
        else if (e < array[middle])
        {
            high = middle - 1;
        }
        else
        {
            low = middle + 1;
        }

    }

    return -1;
}

int SelectionSort(const int& len, int array[])
{
    if (array == NULL || len <= 1)
        return -1;

    for (int i = 0; i < len; ++i)
    {
        int min = i;
        for (int j = i+1; j < len; ++j)
        {
            if (array[j] < array[min])
                min = j;
        }
        swap(array[i], array[min]);
    }
    return 0;
}

int InsertionSort(const int& len, int array[])
{
    if (array == NULL)
    {
        return -1;
    }

    for (int i = 1; i < len; ++i)
    {
        int e = array[i];
        if (e >= array[i-1])
        {
            continue;
        }
        int low = 0, high = i-1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (e < array[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (int j = i; j > low; --j)
        {
            array[j] = array[j-1];
        }
        array[low] = e;
    }
    return 0;
}

int Partition(int low, int high, int array[])
{
    int pivot = array[low];
    while (low < high)
    {
        while (low < high && array[high] >= pivot)
        {
            --high;
        }
        array[low] = array[high];

        while (low < high && array[low] <= pivot)
        {
            ++low;
        }
        array[high] = array[low];
    }
    array[low] = pivot;

    return low;
}

int QuickSort(int low, int high, int array[])
{
    if (low < high)
    {
        int pivot = Partition(low, high, array);
        QuickSort(low, pivot-1, array);
        QuickSort(pivot+1, high, array);
    }

    return 0;
}

int HeadAdjust(const int& idx, const int& len, int array[])
{
    if (idx >= len)
    {
        return -1;
    }

    int pos;
    if (2*idx+2 < len)
    {
        pos = array[2*idx+1] > array[2*idx+2] ? 2*idx+1 : 2*idx+2;
    }
    else if (2*idx+1 < len)
    {
        pos = 2*idx+1;
    }
    else
    {
        pos = idx;
    }

    if (array[pos] > array[idx])
    {
        Swap(array[pos], array[idx]);
    }

    return 0;
} 

int MaxHeap(const int& idx, const int& len, int array[])
{
    int i = 2*idx+1;
    if (i+1 < len && array[i+1] > array[i])
    {
        ++i;
    }

    if (i < len && array[i] > array[idx])
    {
        Swap(array[i], array[idx]);
        MaxHeap(i, len, array);
    }

    return 0;
}

int HeapSort(const int& len, int array[])
{
//    for (int i = len/2; i >= 0; --i)
//    {
//        HeadAdjust(i, len, array);
//    }
//    for (int i = len-1; i >= 0; --i)
//    {
//        Swap(array[0], array[i]);
//        for (int j = i/2; j >= 0; --j)
//        {
//            HeadAdjust(j, i, array);
//        }
//    }

    for (int i = len/2; i >=0; --i)
    {
        MaxHeap(i, len, array);
//        PrintArray(array, len);
    }

    for (int i = len-1; i >= 0; --i)
    {
        Swap(array[0], array[i]);
        MaxHeap(0, i, array);
    }

        
    return 0;
}

int MergeSort(const int& len, int array[])
{
    if (array == NULL)
    {
        return -1;
    }
    int tmp_array[len];
    MSort(0, len-1, array, tmp_array);

    return 0;
}

int MSort(int low, int high, int array[], int tmp_array[])
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MSort(low, mid, array, tmp_array);
        MSort(mid+1, high, array, tmp_array);
        Merge(low, mid, high, array, tmp_array);
    }
    return 0;
}

int Merge(int low, int mid, int high, int array[], int tmp_array[])
{
    int i = low, m = mid, j = mid+1, n = high, k = low;
    while (i <= m && j <= n)
    {
        if (array[i] < array[j])
        {
            tmp_array[k++] = array[i++];
        }
        else
        {
            tmp_array[k++] = array[j++];
        }
    }
    while (i <= m)
    {
        tmp_array[k++] = array[i++];
    }

    while (j <= n)
    {
        tmp_array[k++] = array[j++];
    }

    assert(k == high+1);

    for (i = low; i < k; ++i)
    {
        array[i] = tmp_array[i];
    }


    return 0;
}

/*
 *和最大子序列
 */
int MaxSumSubSequnce(int array[], const int& len)
{
    int sum = 0;
    int max_sum = array[0];

    for (int i = 0; i < len; ++i)
    {
        if (sum < 0)
        {
            sum = array[i];
        }
        else
        {
            sum += array[i];
        }

        if (sum > max_sum)
        {
            max_sum = sum;
        }
    }

    return max_sum;
}

/*
 *最长递增子序列
 */
int LongestAscSubSequnce(int array[], const int len, int sub_array[], int& sub_len)
{
    int longest_sub_sequnce[len];
    int pre_index[len];
    for (size_t i = 0; i < len; ++i)
    {
        longest_sub_sequnce[i] = 1;
        pre_index[i] = -1;
    }

    for (size_t i = 0; i < len; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            if (array[j] < array[i])
            {
                int msl = longest_sub_sequnce[j] + 1;
                if (msl > longest_sub_sequnce[i])
                {
                    longest_sub_sequnce[i] = msl;
                    pre_index[i] = j;
                }
            }
        }
    }

    int msl = 1;
    int pre_idx = -1;
    for (size_t i = 0; i < len; ++i)
    {
        if (longest_sub_sequnce[i] > msl)
        {
            msl = longest_sub_sequnce[i];
            pre_idx = i;
        }
    }
    
    sub_len = msl;

    int cnt = 0;
    while(pre_idx != -1)
    {
//        cout << pre_idx << ":" << array[pre_idx] << endl;
        ++cnt;
        sub_array[sub_len-cnt] = array[pre_idx];
        pre_idx = pre_index[pre_idx];
    }

    assert(sub_len == cnt);

    return 0;
}

int longest_common_substring(const char *str1, const char *str2)
{
    int i,j,k,len1,len2,max,x,y;
    len1 = strlen(str1);
    len2 = strlen(str2);
    int **c = new int*[len1+1];
    for(i = 0; i < len1+1; i++)
        c[i] = new int[len2+1];
    for(i = 0; i < len1+1; i++)
        c[i][0]=0;        //第0列都初始化为0
    for(j = 0; j < len2+1; j++)
        c[0][j]=0;        //第0行都初始化为0 
    max = -1;
    for(i = 1 ; i < len1+1 ; i++)
    {
        for(j = 1; j < len2+1; j++)
        {
            if(str1[i-1]==str2[j-1])     //只需要跟左上方的c[i-1][j-1]比较就可以了
                c[i][j]=c[i-1][j-1]+1;
            else                         //不连续的时候还要跟左边的c[i][j-1]、上边的c[i-1][j]值比较，这里不需要
                c[i][j]=0;
            if(c[i][j]>max)
            {
                max=c[i][j];
                x=i;
                y=j;
            }
        }
    }

    //输出公共子串
    char s[1000];
    k=max;
    i=x-1,j=y-1;
    s[k--]='\0';
    while(i>=0 && j>=0)
    {
        if(str1[i]==str2[j])
        {
            s[k--]=str1[i];
            i--;
            j--;
        }
        else       //只要有一个不相等，就说明相等的公共字符断了，不连续了
            break;
    }
    printf("最长公共子串为：");
    puts(s);
    for(i = 0; i < len1+1; i++)         //释放动态申请的二维数组
        delete[] c[i];
    delete[] c;
    return max;
}

/*
* 任意进制数转换
*/
bool AnyBinaryExchange(const char* binary_in, const int& rbi, char* binary_out, const int& rbo)
{
    if (binary_in == NULL || binary_out == NULL)
        return false;

    //change any_binary num of string format to a dec num
    const char* addr_in = binary_in;
    int dec = 0;
    char a;
    int b = 0;
    while ((a=(*binary_in)) != '\0')
    {
        if (a <= '9' && a >= '0')
        {
            b = a - '0';
        }
        else if (a <= 'f' && a >= 'a')
        {
            b = a - 'a' + 10;
        }
        else if (a <= 'F' && a >= 'A')
        {
            b = a - 'A' + 10;
        }
        else
        {
            b = 0;
        }
        dec = dec*rbi + b;
        ++binary_in;
    }
    cout << addr_in << ":" << rbi << " " << dec << ":" << 10 << " ";

    char* addr_out = binary_out;
    char code[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::stack<char> s;
    while (dec != 0)
    {
        b = dec % rbo;
        dec = dec / rbo;
        if (b > 15 || b < 0)
        {
            continue;
        }
        s.push(code[b]);
    }

    while (!s.empty())
    {
        *binary_out++ = s.top();
        s.pop();
    }

    *binary_out++ = '\0';
    cout << addr_out << ":" << rbo << endl;
    
    return true;
}
