#pragma once

#include "Stack.h"
#include "Array.h"

namespace cm {
	template<typename T>
	class ArrayStack : public Stack<T> {
	public:
		explicit ArrayStack(const int capacity) : array(new Array<T>(capacity)) {}

		ArrayStack() : array(new Array<T>()) {}

		//返回大小
		constexpr int getSize() const {
			return array->getSize();
		}

		//判空
		constexpr bool isEmpty() const {
			return array->isEmpty();
		}

		//返回栈容积
		constexpr int getCapacity() const {
			return array->getCapacity();
		}

		//入栈
		void push(const T &e) {
			array->addLast(e);
		}

		//出栈
		constexpr T pop() {
			return array->removeLast();
		}

		//返回栈顶元素
		constexpr T peek() const {
			return array->getLast();
		}

		~ArrayStack() {
			delete[] array;
			array = nullptr;
		}

		friend std::ostream &operator<<(std::ostream &stream, const ArrayStack &arr) {
			stream << "Array: size = " << arr.getSize() << ", capacity = " << arr.getCapacity() << std::endl;
			stream << "[";
			for (int i = 0; i < arr.getSize(); ++i) {
				stream << arr.array->get(i);
				if (i != arr.getSize() - 1) {
					stream << ",";
				}
			}
			stream << "]";
			stream << std::endl;
			return stream;
		}

	private:
		Array<T> *array;
	};
}