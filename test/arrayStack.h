#pragma once
#include "ArrayStack.h"

void arrayStack(){
	cm::ArrayStack<int>arrayStack1;
	arrayStack1.push(1);
	arrayStack1.push(2);
	arrayStack1.push(3);
	arrayStack1.push(4);
	std::cout<<arrayStack1<<std::endl;
}