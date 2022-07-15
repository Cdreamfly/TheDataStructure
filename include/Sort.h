#pragma once

#include <algorithm>

namespace Sort {
    //选择排序
    /*template<typename T>
    void selectionSort(T arr[], int n) {
        for (int i = 0; i < n; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[minIndex] > arr[j]) {
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]);
        }
    }*/
    //优化
    // 在每一轮中, 可以同时找到当前未处理元素的最大值和最小值
    template<typename T>
    void selectionSort(T arr[], const int n) {
        int left = 0, right = n - 1;
        while (left < right) {
            int minIndex = left;
            int maxIndex = right;
            // 在每一轮查找时, 要保证arr[minIndex] <= arr[maxIndex]
            if (arr[minIndex] > arr[maxIndex]) {
                std::swap(arr[minIndex], arr[maxIndex]);
            }
            for (int i = left + 1; i < right; i++) {
                if (arr[i] < arr[minIndex]) {
                    minIndex = i;
                } else if (arr[i] > arr[maxIndex]) {
                    maxIndex = i;
                }
            }
            std::swap(arr[left], arr[minIndex]);
            std::swap(arr[right], arr[maxIndex]);
            left++;
            right--;
        }
    }

    //插入排序
    template<typename T>
    void insertionSort(T arr[], const int n) {
        for (int i = 1; i < n; i++) {
            // 寻找元素arr[i]合适的插入位置
            // 写法1
//        for( int j = i ; j > 0 ; j-- )
//            if( arr[j] < arr[j-1] )
//                swap( arr[j] , arr[j-1] );
//            else
//                break;

            // 写法2
            //for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j) {
            //    std::swap(arr[j], arr[j - 1]);
            //}
            // 写法3
            T e = arr[i];
            int j; // j保存元素e应该插入的位置
            for (j = i; j > 0 && arr[j - 1] > e; j--) {
                arr[j] = arr[j - 1];
            }
            arr[j] = e;
        }
    }
    //冒泡排序
    /*template<typename T>
    void bubbleSort(T arr[], const int n) {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }*/
    //优化
    template<typename T>
    void bubbleSort(T arr[], const int n) {
        bool isSwapped;
        int lastSwap = 0;
        int k = n - 1;
        for (int i = 0; i < n; ++i) {
            isSwapped = false;
            for (int j = 0; j < k; ++j) {
                if (arr[j] > arr[j + 1]) {
                    arr[j] = arr[j] ^ arr[j + 1];
                    arr[j + 1] = arr[j + 1] ^ arr[j];
                    arr[j] = arr[j] ^ arr[j + 1];
                    isSwapped = true;
                    //lastSwap之后的数都是排好序的
                    lastSwap = j;
                }
            }
            if (!isSwapped) break;
            k = lastSwap;
        }
    }

    //希尔排序
    template<typename T>
    void shellSort(T arr[], const int n) {
        // 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
        int h = 1;
        while (h < n / 3) {
            h = 3 * h + 1;
        }
        while (h >= 1) {
            // h-sort the array
            for (int i = h; i < n; i++) {
                // 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
                T e = arr[i];
                int j;
                for (j = i; j >= h && e < arr[j - h]; j -= h) {
                    arr[j] = arr[j - h];
                }
                arr[j] = e;
            }
            h /= 3;
        }
    }
};