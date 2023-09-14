#pragma once

#include "Array.h"

void arrayTest() {
	cm::Array<int> array;
	array.addFirst(0);
	array.addFirst(1);
	array.addFirst(2);
	array.addFirst(3);
	array.addFirst(4);
	array.addFirst(5);
	array.removeLast();
	array.removeFirst();
	std::cout << array << std::endl;
}