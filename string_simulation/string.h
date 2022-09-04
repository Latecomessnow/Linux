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
		// 初始化列表会有声明顺序的问题，这里可以采用函数体内赋值
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];// 多开一个空间给\0
			strcpy(_str, str);
			cout << "string(const char* str = "")" << endl;
		}

		~string()
		{
			// 需注意方括号的匹配
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

		// 重载方括号就可以按下标的形式访问了，string类更喜欢用方括号而不是迭代器
		char& operator[](size_t pos);

		// const成员
		const char& operator[](size_t pos) const;

		// 只开空间但不初始化数据
		void reserve(size_t n);

		// 开空间也可以初始化
		void resize(size_t n, char ch = '\0')
		{
			if (n > _size)
			{
				reserve(n);
				// 大于，插入数据
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				// 删除数据
				_str[n] = '\0';
				_size = n;
			}
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				// 满了扩容，复用reserve
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}

		// 插入一串字符串
		void append(const char* str)
		{
			size_t len = strlen(str);
			// 检查加入该字符串后的容量是否还够
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			// 不使用字符串追加，因为每次追加都需要找\0，效率低
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

		// 在字符串后边插入n个字符
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
			// 等于刚好在\0位置插入
			assert(pos <= _size);
			int len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size + len;
			// 挪动数据
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
		//		// 把删除len的字符后的字符拷贝到删除位置
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
				// 覆盖删除
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

		// 找字串
		size_t find(const char* sub, size_t pos = 0) const
		{
			assert(sub);
			assert(pos < _size);
			// 返回找到字串首元素地址
			const char* ptr = strstr(_str + pos, sub);
			if (ptr == nullptr)
			{
				return npos;
			}
			else
			{
				// 指针相减即可
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
		// const static 语法特殊处理
		// 直接可以当成定义初始化
		// 或者类内声明，类外定义
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
