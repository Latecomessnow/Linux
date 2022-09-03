#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 实现小根堆
 * 将完全二叉树从上到下、从左到右插入vector中，可以通过父节点获取子节点，也可通过子节点获取父节点
 * parent = (chhild - 1) >> 1
 * child1 = (parent << 1) + 1
 * child2 = child1 + 1
 * */

template<class T>
class Heap
{
public:
	Heap(const vector<T>& element_vec) {
		for (const T& element : element_vec) {
			_element_vec.emplace_back(element);
		}
		createHeap();
	}
	Heap(const T* element, size_t len) {
		for (size_t i = 0; i < len; i++) {
			_element_vec.emplace_back(*(element + i));
		}
		createHeap();
	}
	~Heap() {}

	void operator=(const vector<T>& element_vec) {
		for (const T& element : element_vec) {
			_element_vec.emplace_back(element);
		}
		createHeap();
	}

	//堆排序，从大到小
	void sort() {
		cout << "=====before sort=====" << endl;
		for (int i : _element_vec) {
			cout << i << " ";
		}
		cout << endl;
		createHeap();
		//last index
		int index = _element_vec.size() - 1;
		cout << "=====after sort=====" << endl;
		for (; index > 0; index--) {
			swap(_element_vec.at(0), _element_vec.at(index));
			cout << _element_vec.at(index) << " ";
			_element_vec.pop_back();
			adjustDown(0);
		}
		cout << _element_vec.at(0) << endl;
	}
	//插入元素
	void push(T element) {
		_element_vec.emplace_back(element);
		adjustUp(_element_vec.size() - 1);
	}
	//删除元素
	void pop() {
		swap(_element_vec.at(0), _element_vec.at(_element_vec.size() - 1));
		_element_vec.pop_back();
		adjustDown(0);
	}
	//是否为空
	inline bool empty() {
		return _element_vec.empty();
	}
	//返回堆元素个数
	inline int size() {
		return _element_vec.size();
	}
	//返回堆顶元素
	inline T top() {
		if (_element_vec.empty()) {
			return static_cast<T>(-1);
		}
		return _element_vec.at(0);
	}

private:
	void createHeap() {
		int len = _element_vec.size();
		if (len <= 1) {
			return;
		}
		//从最后一个子节点的父节点开始，依次往上调整
		int parent = (len - 1 - 1) >> 1;
		for (int i = parent; i >= 0; i--) {
			adjustDown(i);
		}
	}
	//向上调整
	void adjustUp(int child) {
		int parent = (child - 1) >> 1;
		while (parent >= 0) {
			if (_element_vec.at(parent) <= _element_vec.at(child)) {
				break;
			}
			swap(_element_vec.at(parent), _element_vec.at(child));
			child = parent;
			parent = (child - 1) >> 1;
		}
	}
	//向下调整
	void adjustDown(int parent) {
		int len = _element_vec.size();
		int child = parent * 2 + 1;
		while (child < len) {
			if (child + 1 < len && _element_vec.at(child + 1) < _element_vec.at(child)) {
				child++;
			}
			if (_element_vec.at(parent) <= _element_vec.at(child)) {
				break;
			}
			swap(_element_vec.at(parent), _element_vec.at(child));
			parent = child;
			child = parent * 2 + 1;
		}
	}

private:
	vector<T> _element_vec;
};

int main(void) {
	vector<int> element_vec{ 4,1,6,3,9,7,5 };
	Heap<int> my_heap(element_vec);
	my_heap.push(11);
	cout << my_heap.top() << endl;
	my_heap.push(2);
	my_heap.push(0);
	cout << my_heap.top() << endl;
	my_heap.pop();
	cout << my_heap.size() << endl;
	my_heap.sort();
	cout << my_heap.empty() << endl;
	my_heap = element_vec;
	cout << my_heap.size() << endl;
	return 0;
}