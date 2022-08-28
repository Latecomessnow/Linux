#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

typedef int DataType;

struct Stack
{
	void Init(size_t capacity)
	{
		_array = (DataType*)malloc(sizeof(DataType) * capacity);
		if (nullptr == _array)
		{
			perror("malloc…Í«Îø’º‰ ß∞‹");
			return;
		}
		_capacity = capacity;
		_size = 0;
	}
	void Push(const DataType& data)
	{
		// ¿©»›
		_array[_size] = data; ++_size;
	}
	DataType Top()
	{
		return _array[_size - 1];
	}
	void Destroy()
	{
		if (_array)
		{
			free(_array);
			_array = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}
	DataType* _array;
	size_t _capacity;
	size_t _size;
};

int main()
{
	Stack s;
	s.Init(10);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	cout << s.Top() << endl;
	s.Destroy();
	return 0;
}