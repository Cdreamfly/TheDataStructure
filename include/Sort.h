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

    // 对arr[l...r]范围的数组进行插入排序
    template<typename T>
    void insertionSort(T arr[], int l, int r) {
        for (int i = l + 1; i <= r; i++) {
            T e = arr[i];
            int j;
            for (j = i; j > l && arr[j - 1] > e; j--) {
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

    // 将arr[l...mid]和arr[mid+1...r]两部分进行归并
    template<typename T>
    void __merge(T arr[], const int l, const int mid, const int r) {
        T aux[r - l + 1];
        for (int i = l; i <= r; ++i) {
            aux[i - l] = arr[i];
        }
        // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
        int i = l, j = mid + 1;
        for (int k = l; k <= r; k++) {
            if (i > mid) {  // 如果左半部分元素已经全部处理完毕
                arr[k] = aux[j - l];
                ++j;
            } else if (j > r) {  // 如果右半部分元素已经全部处理完毕
                arr[k] = aux[i - l];
                ++i;
            } else if (aux[i - l] < aux[j - l]) {  // 左半部分所指元素 < 右半部分所指元素
                arr[k] = aux[i - l];
                ++i;
            } else {  // 左半部分所指元素 >= 右半部分所指元素
                arr[k] = aux[j - l];
                ++j;
            }
        }
    }

    // 递归使用归并排序,对arr[l...r]的范围进行排序
    template<typename T>
    void __mergeSort(T arr[], const int l, const int r) {
        /*if (l >= r) {
            return;
        }*/
        // 优化2: 对于小规模数组, 使用插入排序
        if (r - l <= 15) {
            insertionSort(arr, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        __mergeSort(arr, l, mid);
        __mergeSort(arr, mid + 1, r);
        // 优化1: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
        // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
        if (arr[mid] > arr[mid + 1]) {
            __merge(arr, l, mid, r);
        }
    }

    //归并排序
    template<typename T>
    void mergeSort(T arr[], const int n) {
        __mergeSort(arr, 0, n - 1);
    }

    // 使用自底向上的归并排序算法
    // Merge Sort BU 也是一个O(nlogn)复杂度的算法，虽然只使用两重for循环
    // 所以，Merge Sort BU也可以在1秒之内轻松处理100万数量级的数据
    // 注意：不要轻易根据循环层数来判断算法的复杂度，Merge Sort BU就是一个反例
    // 比较Merge Sort和Merge Sort Bottom Up两种排序算法的性能效率
    // 整体而言, 两种算法的效率是差不多的。但是如果进行仔细测试, 自底向上的归并排序会略胜一筹。
    // 不过Merge Sort Bottom Up 有一个非常重要的作用，这个代码中没有使用数组的索引获取元素特性，就因如此可以非常好的在nlog(n)的时间对链表这样的数据结构进行排序
    template<typename T>
    void mergeSortBU(T arr[], const int n) {
        // Merge Sort Bottom Up 优化
        // 对于小数组, 使用插入排序优化
        for (int i = 0; i < n; i += 16) {
            insertionSort(arr, i, std::min(i + 15, n - 1));
        }
        for (int sz = 16; sz < n; sz += sz) {
            for (int i = 0; i < n - sz; i += sz + sz) {
                // 对于arr[mid] <= arr[mid+1]的情况,不进行merge
                if (arr[i + sz - 1] > arr[i + sz]) {
                    __merge(arr, i, i + sz - 1, std::min(i + sz + sz - 1, n - 1));
                }
            }
        }
    }

    // 对arr[l...r]部分进行partition操作
    // 返回p, 使得arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
    template<typename T>
    int __partition1(T arr[], const int l, const int r) {
        // 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
        std::swap(arr[l], arr[rand() % (r - l + 1) + l]);
        const T v = arr[l];
        int j = l;
        // arr[l+1...j] < v ; arr[j+1...i) > v
        for (int i = l + 1; i <= r; i++) {
            if (arr[i] < v) {
                std::swap(arr[++j], arr[i]);
            }
        }
        std::swap(arr[l], arr[j]);
        return j;
    }

    // 双路快速排序的partition
    // 返回p, 使得arr[l...p-1] <= arr[p] ; arr[p+1...r] >= arr[p]
    // 双路快排处理的元素正好等于arr[p]的时候要注意，详见下面的注释：）
    template<typename T>
    int __partition2(T arr[], int l, int r) {
        // 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
        std::swap(arr[l], arr[rand() % (r - l + 1) + l]);
        const T v = arr[l];
        // arr[l+1...i) <= v; arr(j...r] >= v
        int i = l + 1, j = r;
        while (true) {
            // 注意这里的边界, arr[i] < v, 不能是arr[i] <= v
            // 思考一下为什么?
            while (i <= r && arr[i] < v)++i;
            // 注意这里的边界, arr[j] > v, 不能是arr[j] >= v
            // 思考一下为什么?
            while (j >= l + 1 && arr[j] > v)--j;
            if (i > j)break;
            std::swap(arr[i], arr[j]);
            //arr[i] < v. 在碰到很多连续相同数字的情况下，i只向后移动一次，同时j至少向前移动一次，相对平衡。
            //arr[i] <= vb, 在碰到很多连续相同数字的情况下, i首先不停向后移动，直到满足条件为止，造成不平衡。
            ++i;
            --j;
        }
        std::swap(arr[l], arr[j]);
        return j;
    }

    // 对arr[l...r]部分进行快速排序
    template<typename T>
    void __quickSort(T arr[], const int l, const int r) {
        // 对于小规模数组, 使用插入排序进行优化
        if (r - l <= 15) {
            insertionSort(arr, l, r);
            return;
        }
        const int p = __partition2(arr, l, r);
        __quickSort(arr, l, p - 1);
        __quickSort(arr, p + 1, r);
    }

    //快速排序
    template<typename T>
    void quickSort(T arr[], const int n) {
        srand(time(NULL));
        __quickSort(arr, 0, n - 1);
    }

    // 递归的三路快速排序算法
    template<typename T>
    void __quickSort3Ways(T arr[], const int l, const int r) {

        // 对于小规模数组, 使用插入排序进行优化
        if (r - l <= 15) {
            insertionSort(arr, l, r);
            return;
        }

        // 随机在arr[l...r]的范围中, 选择一个数值作为标定点pivot
        std::swap(arr[l], arr[rand() % (r - l + 1) + l]);

        T v = arr[l];

        int lt = l;     // arr[l+1...lt] < v
        int gt = r + 1; // arr[gt...r] > v
        int i = l + 1;    // arr[lt+1...i) == v
        while (i < gt) {
            if (arr[i] < v) {
                std::swap(arr[i], arr[lt + 1]);
                i++;
                lt++;
            } else if (arr[i] > v) {
                std::swap(arr[i], arr[gt - 1]);
                gt--;
            } else { // arr[i] == v
                i++;
            }
        }
        std::swap(arr[l], arr[lt]);
        __quickSort3Ways(arr, l, lt - 1);
        __quickSort3Ways(arr, gt, r);
    }
    // 对于包含有大量重复数据的数组, 三路快排有巨大的优势
    template<typename T>
    void quickSort3Ways(T arr[], const int n) {
        srand(time(nullptr));
        __quickSort3Ways(arr, 0, n - 1);
    }
};