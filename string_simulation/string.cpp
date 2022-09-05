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
//	// ��������
//	strcpy(_str, s._str);
//}

// 3. s2(s1)
string::string(const string& s)
	: _str(nullptr)
	, _size(0)
	, _capacity(0)
{
	// ���ù���ͽ���ʵ�ֿ�������
	// ���������ַ������г�ʼ���Ĺ��캯��
	string tmp(s._str);
	swap(tmp);
	cout << "string(const string& s)" << endl;
}

// 1. s2 = s1
// s3 = s2 = s1, ������ֵ��һ�������÷���
//string& string::operator=(const string& s)
//{
//	// �ж�һ���Լ����Լ���ֵ�����
//	if (this != &s)
//	{
//      // �ȿ��㹻�Ŀռ����ڿ���
//		char* tmp = new char[s._capacity + 1];
//		strcpy(tmp, s._str);
//		// �ǵ�ɾ��ԭ�ռ�
//		delete[] _str;
//		_str = tmp;
//		_capacity = s._capacity;
//		_size = s._size;
//	}
//	return *this;
//}

// modern

// ͨ���������и�ֵ
void string::swap(string& s)
{
	// ָ���������ȫ�ֵ�swap
	::swap(_str, s._str);
	::swap(_size, s._size);
	::swap(_capacity, s._capacity);
}

// 2. s2 = s1
//string& string::operator=(const string& s)
//{
//	if (this != &s)
//	{
//		// ���ù��캯�����и�ֵ����
//		string tmp(s);
//		swap(tmp);
//	}
//	return *this;
//}

// 3. s2 = s1 
// ֱ��ͨ�����ν��п��������ٽ��н���
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

// �����ַ�����Ԫ�صĵ�ַ
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
	// string��ϲ�����±�ķ�ʽȥ����
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
//		// ���ڣ���������
//		for (size_t i = _size; i < n; i++)
//		{
//			_str[i] = ch;
//		}
//		_str[n] = '\0';
//		_size = n;
//	}
//	else
//	{
//		// ɾ������
//		_str[n] = '\0';
//		_size = n;
//	}
//}
