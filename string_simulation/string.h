#pragma once

#include<iostream>
#include<assert.h>
using std::cout;
using std::cin;
using std::endl;
using std::swap;

namespace bit
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		// string("hello")
		// ��ʼ���б��������˳������⣬������Բ��ú������ڸ�ֵ
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];// �࿪һ���ռ��\0
			strcpy(_str, str);
			cout << "string(const char* str = "")" << endl;
		}

		~string()
		{
			// ��ע�ⷽ���ŵ�ƥ��
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
			cout << "~string()" << endl;

		}

		string(const string& s);

		string& operator=(string s);
		//string& operator=(const char* s);

		void swap(string& s);

		size_t size() const;

		size_t capacity() const;

		const char* c_str() const;

		// ���ط����žͿ��԰��±����ʽ�����ˣ�string���ϲ���÷����Ŷ����ǵ�����
		char& operator[](size_t pos);

		// const��Ա
		const char& operator[](size_t pos) const;

		// ֻ���ռ䵫����ʼ������
		void reserve(size_t n);

		// ���ռ�Ҳ���Գ�ʼ��
		void resize(size_t n, char ch = '\0')
		{
			if (n > _size)
			{
				reserve(n);
				// ���ڣ���������
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				// ɾ������
				_str[n] = '\0';
				_size = n;
			}
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				// �������ݣ�����reserve
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}

		// ����һ���ַ���
		void append(const char* str)
		{
			size_t len = strlen(str);
			// ��������ַ�����������Ƿ񻹹�
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			// ��ʹ���ַ���׷�ӣ���Ϊÿ��׷�Ӷ���Ҫ��\0��Ч�ʵ�
			// strcat(_str, str)
			_size += len;
			//insert(_size, str);
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		string& operator+=(const string& s)
		{
			append(s._str);
			return *this;
		}

		void append(const string& s)
		{
			append(s._str);
		}

		// ���ַ�����߲���n���ַ�
		void append(size_t n, char ch = '\0')
		{
			reserve(_size + n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(ch);
			}
			_size += n;
		}

		string& insert(size_t pos, const char* str)
		{
			// ���ڸպ���\0λ�ò���
			assert(pos <= _size);
			int len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size + len;
			// Ų������
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				end--;
			}
			strncpy(_str + pos, str, len);
			_size += len;
			return *this;
		}

		//void erase(size_t pos, size_t len = npos)
		//{
		//	assert(pos < _size);
		//	if (len == npos || pos + len > _size)
		//	{
		//		_str[pos] = '\0';
		//		_size = pos;
		//	}
		//	else
		//	{
		//		// ��ɾ��len���ַ�����ַ�������ɾ��λ��
		//		strcpy(_str + pos, _str + pos + len);
		//		_size -= len;
		//	}
		//}

		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos + len > _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				// ����ɾ��
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		size_t find(char ch, size_t pos = 0) const
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == ch)
					return i;
			}
			return npos;
		}

		// ���ִ�
		size_t find(const char* sub, size_t pos = 0) const
		{
			assert(sub);
			assert(pos < _size);
			// �����ҵ��ִ���Ԫ�ص�ַ
			const char* ptr = strstr(_str + pos, sub);
			if (ptr == nullptr)
			{
				return npos;
			}
			else
			{
				// ָ���������
				return ptr - _str;
			}
		}

		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str) > 0;
		}

		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}

		bool operator>=(const string& s) const
		{
			return *this > s || *this == s;
		}

		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}

		bool operator<(const string& s) const
		{
			return !(*this >= s);
		}

		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	public:
		// const static �﷨���⴦��
		// ֱ�ӿ��Ե��ɶ����ʼ��
		// �����������������ⶨ��
		const static size_t npos = -1;
	};
	//std::ostream& operator<<(std::ostream& out, const string& s)
	//{
	//	for (size_t i = 0; i < s.size(); ++i)
	//	{
	//		out << s[i];
	//	}
	//	return out;
	//}
	/*std::istream& operator>>(std::istream in, string& s)
	{
		s.clear();
		char ch;
		ch = in.get();
		const size_t N = 32;
		char buff[N];
		size_t i = 0;
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == N - 1)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}
		buff[i] = '\0';
		s += buff;
		return in;
	}*/
}
