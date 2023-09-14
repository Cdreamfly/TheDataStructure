#pragma once

#include "Array.h"
#include "Queue.h"

namespace cm {
	template<typename T>
	class ArrayQueue : public Queue<T> {
	public:
		ArrayQueue() : array(new Array<T>()) {}

		explicit ArrayQueue(const int capacity) : array(new Array<T>(capacity)) {}

		[[nodiscard]] constexpr int getSize() const {
			return array->getSize();
		}

		[[nodiscard]] constexpr int getCapacity() const {
			return array->getCapacity();
		}

		[[nodiscard]] constexpr bool isEmpty() const {
			return array->isEmpty();
		}

		void enqueue(const T &e) {
			array->addLast(e);
		}

		constexpr T dequeue() {
			return array->removeFirst();    //时间复杂度:O(n)
		}

		constexpr T getFront() const {
			return array->getFirst();
		}

		~ArrayQueue() {
			delete[] array;
			array = nullptr;
		}

		friend std::ostream &operator<<(std::ostream &stream, const ArrayQueue &arr) {
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