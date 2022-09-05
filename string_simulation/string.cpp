#define _CRT_SECURE_NO_WARNINGS 1

#include"string.h"
using namespace HuiGu;

// tradition
// 
// 1. s2(s1)
//string::string(const string& s)
//{
//	_str = new char[s._capacity + 1];
//	_size = s._size;
//	_capacity = s._capacity;
//	strcpy(_str, s._str);
//}

// 2. s2(s1)
//string::string(const string& s)
//	: _str(new char[s._capacity + 1])
//	, _size(s._size)
//	, _capacity(s._capacity)
//{
//	// 拷贝数据
//	strcpy(_str, s._str);
//}

// 3. s2(s1)
string::string(const string& s)
	: _str(nullptr)
	, _size(0)
	, _capacity(0)
{
	// 调用构造和交换实现拷贝构造
	// 调给常量字符串进行初始化的构造函数
	string tmp(s._str);
	swap(tmp);
	cout << "string(const string& s)" << endl;
}

// 1. s2 = s1
// s3 = s2 = s1, 连续赋值给一个传引用返回
//string& string::operator=(const string& s)
//{
//	// 判断一下自己给自己赋值的情况
//	if (this != &s)
//	{
//      // 先开足够的空间用于拷贝
//		char* tmp = new char[s._capacity + 1];
//		strcpy(tmp, s._str);
//		// 记得删除原空间
//		delete[] _str;
//		_str = tmp;
//		_capacity = s._capacity;
//		_size = s._size;
//	}
//	return *this;
//}

// modern

// 通过交换进行赋值
void string::swap(string& s)
{
	// 指定类域调用全局的swap
	::swap(_str, s._str);
	::swap(_size, s._size);
	::swap(_capacity, s._capacity);
}

// 2. s2 = s1
//string& string::operator=(const string& s)
//{
//	if (this != &s)
//	{
//		// 调用构造函数进行赋值重载
//		string tmp(s);
//		swap(tmp);
//	}
//	return *this;
//}

// 3. s2 = s1 
// 直接通过传参进行拷贝构造再进行交换
string& string::operator=(string s)
{
	swap(s);
	cout << "string& operator=(string s)" << endl;
	return *this;
}

//string& string::operator=(const char* s)
//{
//	string tmp(s);
//	swap(tmp);
//	return *this;
//}

// 返回字符串首元素的地址
const char* string::c_str() const
{
	return _str;
}

size_t string::size() const
{
	return _size;
}

size_t string::capacity() const
{
	return _capacity;
}

char& string::operator[](size_t pos) 
{
	assert(pos < _size);
	// string更喜欢用下标的方式去访问
	return _str[pos];
}

const char& string::operator[](size_t pos) const
{
	assert(pos < _size);
	return _str[pos];
}

void string::reserve(size_t n)
{
	if (n > _capacity)
	{
		char* tmp = new char[n + 1];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
		_capacity = n;
	}
}

//void string::resize(size_t n, char ch = '\0')
//{
//	if (n > _size)
//	{
//		reserve(n);
//		// 大于，插入数据
//		for (size_t i = _size; i < n; i++)
//		{
//			_str[i] = ch;
//		}
//		_str[n] = '\0';
//		_size = n;
//	}
//	else
//	{
//		// 删除数据
//		_str[n] = '\0';
//		_size = n;
//	}
//}
