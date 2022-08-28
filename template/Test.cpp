#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>

using namespace std;

//template<typename T>
template<class T>

void Swap(T& left, T& right)
{
	T tmp = left;
	left = right;
	right = tmp;
}

template<class T>
T& Add(const T& left, const T& right)
{
	return left + right;
}

//int main()
//{
//	int a = 10, b = 20;
//	double x = 1.1, y = 2.2;
//	char m = 'a', n = 'b';
//	Swap(a, b);
//	Swap(x, y);
//	Swap(m, n);
//	cout << a << " " << b << endl;
//	cout << x << " " << y << endl;
//	cout << m << " " << n << endl;
//	cout << a + b << endl;
//	return 0;
//}

// 一个非模板函数可以和一个同名的函数模板同时存在，
// 而且该函数模板还可以被实例化为这个非模板函数

// 专门处理int的加法函数
int Add(int left, int right)
{
	return left + right;
}
// 通用加法函数
template<class T>
T Add(T left, T right)
{
	return left + right;
}

// 模板函数不允许自动类型转换，但普通函数可以进行自动类型转换

void Test()
{
	cout << Add(1, 2); // 与非模板函数匹配，编译器不需要特化
	//Add<int>(1, 2); // 调用编译器特化的Add版本
	// 尝试匹配参数列表“(int, int)”时
}

//int main()
//{
//	Test();
//	return 0;
//}

// 动态顺序表
// 注意：Vector不是具体的类，是编译器根据被实例化的类型生成具体类的模具
template<class T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}
	// 使用析构函数演示：在类中声明，在类外定义。
	~Vector();
	void PushBack(const T& data);
	void PopBack();
		// ...

		size_t Size() { return _size; }

	T& operator[](size_t pos) {
		assert(pos < _size);
		return _pData[pos];
	}

private:
	T* _pData;
	size_t _size;
	size_t _capacity;
};

// 注意：类模板中函数放在类外进行定义时，需要加模板参数列表
template <class T>
Vector<T>::~Vector()
{
	if (_pData)
		// 注意匹配，new的时候带括号，delete时也要带括号
		delete[] _pData;
	_size = _capacity = 0;
}

////////////////////////////////////////////////////////////////////////////////

//template<class T>
//
//class Satck
//{
//private:
//	T* _a;
//	int _top;
//	int _capacity;
//};
//
//int main()
//{
//	Satck<int> s1;
//	Satck<char> s2;
//	return 0;
//}

template<typename T>
class Stack
{
public:
	Stack(int capacity = 0)
		: _a(nullptr)
		, _top(0)
		, _capacity(0)
	{
		if (capacity > 0)
		{
			_a = new T[capacity];
			_top = 0;
			_capacity = capacity;
		}
	}

	~Stack()
	{
		delete[] _a;
		_a = nullptr;
		_top = _capacity = 0;
	}

	// 太长不适合内敛，类内声明，类外定义
	void Push(const T& x);

	bool Empty()
	{
		return _top == 0;
	}

	void Pop()
	{
		assert(!Empty());
		_top--;
	}

	// 以防对top元素进行++等操作
	const T& Top()
	{
		assert(!Empty());
		return _a[_top - 1];
	}

	int Size()
	{
		return _top;
	}

private:
	T* _a;
	int _top;
	int _capacity;
};

template<class T>
// 注意加上模板参数
void Stack<T>::Push(const T& x)
{
	if (_top == _capacity)
	{
		size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
		T* tmp = new T[newCapacity];
		// 如果_a不为空则拷贝原数据到新空间
		if (_a)
		{
			memcpy(tmp, _a, sizeof(T) * _top);
			// 释放原空间
			delete[] _a;
		}
		_a = tmp;
		_capacity = newCapacity;
	}
	_a[_top++] = x;
}

int main()
{
	Stack<int> st1;
	st1.Push(1);
	st1.Push(2);
	st1.Push(3);
	st1.Push(4);
	st1.Push(5);
	cout << st1.Size() << endl;
	while (!st1.Empty())
	{
		cout << st1.Top() << " ";
		st1.Pop();
	}
	cout << endl;
	//st1.Pop();
	cout << st1.Size() << endl;
	return 0;
}