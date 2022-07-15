#pragma once

#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
#include <memory>

namespace SortTestHelper {
    // 生成有n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
    int *generateRandomArray(const int n, const int rangeL, const int rangeR) {
        assert(rangeL <= rangeR);
        int *arr = new int[n];
        std::default_random_engine e(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> u(rangeL, rangeR);
        for (int i = 0; i < n; ++i) {
            arr[i] = u(e);
        }
        return arr;
    }

    // 生成一个近乎有序的数组
    // 首先生成一个含有[0...n-1]的完全有序数组, 之后随机交换swapTimes对数据
    // swapTimes定义了数组的无序程度:
    // swapTimes == 0 时, 数组完全有序
    // swapTimes 越大, 数组越趋向于无序
    int *generateNearlyOrderedArray(const int n, const int swapTimes) {
        int *arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
        for (int i = 0; i < swapTimes; ++i) {
            int posx = rand() % n;
            int posy = rand() % n;
            std::swap(arr[posx], arr[posy]);
        }
        return arr;
    }

    // 打印arr数组的所有内容
    template<typename T>
    void printArray(const T arr[], const int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    // 判断arr数组是否是升序
    template<typename T>
    bool isSorted(const T arr[], const int n) {
        for (int i = 0; i < n - 1; i++)
            if (arr[i] > arr[i + 1])
                return false;

        return true;
    }

    // 测试sort排序算法排序arr数组所得到结果的正确性和算法运行时间
    template<typename T>
    void testSort(const std::string &sortName, void(*sort)(T[], const int), T arr[], const int n) {
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
        sort(arr, n);
        std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        std::chrono::duration<float> duration = end - start;
        assert(isSorted(arr, n));
        std::cout << sortName << " Timer took " << duration.count() * 1.0f << " s" << std::endl;
    }

    // 拷贝整型数组a中的所有元素到一个新的数组, 并返回新的数组
    int *copyIntArray(const int arr[], const int n) {
        int *res = new int[n];
        for (int i = 0; i < n; ++i) {
            res[i] = arr[i];
        }
        return res;
    }
};