#pragma once
#include <iostream>
#include "ArrayQueue.h"
void test(){
	cm::ArrayQueue<int>arr;
	arr.enqueue(1);
	arr.enqueue(2);
	arr.enqueue(3);
	arr.enqueue(4);
	arr.enqueue(5);

	std::cout<<arr<<std::endl;
	std::cout<<"123"<<std::endl;
	std::cin.get();
}