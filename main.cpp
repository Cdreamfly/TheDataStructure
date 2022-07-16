#include "Sort.h"
#include "SortTestHelper.h"

using namespace std;

int main() {
    int n = 2000000;

    cout << "Test for random array, size = " << n << ", random range [0, " << n << "]" << endl;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0,n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::copyIntArray(arr1, n);
    int *arr5 = SortTestHelper::copyIntArray(arr1, n);

//    SortTestHelper::printArray(arr1, n);
//    SortTestHelper::printArray(arr2, n);
//    SortTestHelper::printArray(arr3, n);
//    SortTestHelper::printArray(arr4, n);
//    SortTestHelper::printArray(arr5, n);


    //SortTestHelper::testSort("Insertion Sort", Sort::insertionSort, arr1, n);
    //SortTestHelper::testSort("Selection Sort", Sort::selectionSort, arr2, n);
    //SortTestHelper::testSort("bubbleSort Sort", Sort::bubbleSort, arr3, n);
    SortTestHelper::testSort("shellSort Sort", Sort::shellSort, arr4, n);
    SortTestHelper::testSort("mergeSort Sort", Sort::mergeSort, arr5, n);

//    SortTestHelper::printArray(arr1, n);
//    SortTestHelper::printArray(arr2, n);
//    SortTestHelper::printArray(arr3, n);
//    SortTestHelper::printArray(arr4, n);
//    SortTestHelper::printArray(arr5, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr4;

    cout << endl;
}