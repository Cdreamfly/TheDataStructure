#include <iostream>
#include "UnionFind.h"

template<typename T>
double testUF(T *uf, int m) {
    int size = uf->getSize();
    clock_t startTime = clock();
    for (int i = 0; i < m; ++i) {
        int a = rand() % size;
        int b = rand() % size;
        uf->unionElements(a, b);
        uf->isConnected(a, b);
    }
    clock_t endTime = clock();
    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

int main() {
    int size = 10000000;
    int m = 10000000;
    srand(10);
    UnionFind *uf = new UnionFind(size);
    std::cout << "UnionFind : " << testUF(uf, m) << " s " << std::endl;

    delete[] uf;
    return 0;
}
