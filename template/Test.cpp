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

// һ����ģ�庯�����Ժ�һ��ͬ���ĺ���ģ��ͬʱ���ڣ�
// ���Ҹú���ģ�廹���Ա�ʵ����Ϊ�����ģ�庯��

// ר�Ŵ���int�ļӷ�����
int Add(int left, int right)
{
	return left + right;
}
// ͨ�üӷ�����
template<class T>
T Add(T left, T right)
{
	return left + right;
}

// ģ�庯���������Զ�����ת��������ͨ�������Խ����Զ�����ת��

void Test()
{
	cout << Add(1, 2); // ���ģ�庯��ƥ�䣬����������Ҫ�ػ�
	//Add<int>(1, 2); // ���ñ������ػ���Add�汾
	// ����ƥ������б�(int, int)��ʱ
}

//int main()
//{
//	Test();
//	return 0;
//}

// ��̬˳���
// ע�⣺Vector���Ǿ�����࣬�Ǳ��������ݱ�ʵ�������������ɾ������ģ��
template<class T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}
	// ʹ������������ʾ�������������������ⶨ�塣
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

// ע�⣺��ģ���к�������������ж���ʱ����Ҫ��ģ������б�
template <class T>
Vector<T>::~Vector()
{
	if (_pData)
		// ע��ƥ�䣬new��ʱ������ţ�deleteʱҲҪ������
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

	// ̫�����ʺ��������������������ⶨ��
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

	// �Է���topԪ�ؽ���++�Ȳ���
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
// ע�����ģ�����
void Stack<T>::Push(const T& x)
{
	if (_top == _capacity)
	{
		size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
		T* tmp = new T[newCapacity];
		// ���_a��Ϊ���򿽱�ԭ���ݵ��¿ռ�
		if (_a)
		{
			memcpy(tmp, _a, sizeof(T) * _top);
			// �ͷ�ԭ�ռ�
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