#pragma once

#include "MaxHeap.h"
#include "Queue.h"

namespace cm {
	template<typename T>
	class PriorityQueue : public Queue<T> {

	private:
		MaxHeap<T> *maxHeap;

	public:
		PriorityQueue() {
			maxHeap = new MaxHeap<T>();
		}

		constexpr int getSize() {
			return maxHeap->getSize();
		}

		constexpr bool isEmpty() {
			return maxHeap->isEmpty();
		}

		void enqueue(const T &e) {
			maxHeap->add(e);
		}

		T dequeue() {
			return maxHeap->extractMax();
		}

		T getFront() {
			return maxHeap->findMax();
		}

		~PriorityQueue() {
			delete maxHeap;
			maxHeap = nullptr;
		}

		void print() {
			std::cout << "Queue: size = " << maxHeap->getSize() << std::endl;
			std::cout << "front ";
			maxHeap->print();
			std::cout << " tail" << std::endl;
		}
	};
}