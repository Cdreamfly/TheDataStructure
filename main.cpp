#include "Sort.h"
#include "SortTestHelper.h"

using namespace std;
// 比较Merge Sort和双路快速排序和三路快排三种排序算法的性能效率
// 对于包含有大量重复数据的数组, 三路快排有巨大的优势
// 对于一般性的随机数组和近乎有序的数组, 三路快排的效率虽然不是最优的, 但是是在非常可以接受的范围里
// 因此, 在一些语言中, 三路快排是默认的语言库函数中使用的排序算法。比如Java:)
int main() {

    int n = 200000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1,n);
    int* arr3 = SortTestHelper::copyIntArray(arr1,n);

    SortTestHelper::testSort("Merge Sort", Sort::mergeSort, arr1, n);
    SortTestHelper::testSort("heapSort Sort", Sort::heapSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", Sort::quickSort3Ways, arr3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    int swapTimes = 100;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", Sort::mergeSort, arr1, n);
    SortTestHelper::testSort("heapSort Sort", Sort::heapSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", Sort::quickSort3Ways, arr3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    cout<<endl;


    // 测试3 测试存在包含大量相同元素的数组
    cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
    arr1 = SortTestHelper::generateRandomArray(n,0,10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", Sort::mergeSort, arr1, n);
    SortTestHelper::testSort("heapSort Sort", Sort::heapSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", Sort::quickSort3Ways, arr3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;


    return 0;
}