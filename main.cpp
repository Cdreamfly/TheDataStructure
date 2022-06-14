#include <iostream>
#include "Array.h"
using namespace std;
int main() {
    Array<int> *array = new Array<int>();
    for (int i = 0; i < 10; ++i) {
        array->addLast(i);
        array->print();
    }
    array->add(1,100);
    array->print();
    array->addFirst(-1);
    array->print();
    array->remove(2);
    array->print();
    cout<<"---------"<<endl;
    cout<<array->removeElement(4);
    cout<<"---------"<<endl;
    array->print();
    array->removeLast();
    array->print();
    array->removeFirst();
    array->print();
    cout<<"---------"<<endl;
    for(int i = 0; i < 4; ++i) {
        array->removeFirst();
        array->print();
    }
    array = nullptr;
    delete array;
    return 0;
}