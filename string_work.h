#pragma once

#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<iostream>

namespace HuiGu
{
    class string
    {
    public:
        typedef char* iterator;
        typedef const char* const_iterator;
    public:
        string(const char* str = "")
        {
            _size = strlen(str);
            _capacity = _size;
            _str = new char[_capacity + 1];
            strcpy(_str, str);
        }

        string(const string& s) 
            : _str(nullptr)
            , _size(0)
            , _capacity(0)
        {
            string tmp(s._str);
            this->swap(tmp);
        }

        string& operator=(const string& s)
        {
            if (this != &s)
            {
                string temp(s);
                this->swap(temp);
            }
            return *this;
        }

        string& operator=(const char* str)
        {
            string tmp(str);
            this->swap(tmp);
            return *this;
        }

        ~string()
        {
            if (_str)
            {
                delete[] _str;
                _str = nullptr;
                _size = _capacity = 0;
            }
        }
        //////////////////////////////////////////////////////////////
        // iterator
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
        /////////////////////////////////////////////////////////////

        // modify
        void push_back(char c)
        {
            if (_size == _capacity)
                reserve(_capacity == 0 ? 4 : _capacity * 2);
            _str[_size++] = c;
            _str[_size] = '\0';
        }

        string& operator+=(char c)
        {
            push_back(c);
            return *this;
        }

        void append(const char* str);

        string& operator+=(const char* str);

        void clear()
        {
            _size = 0;
            _str[_size] = '\0';
        }

        void swap(string& s)
        {
            std::swap(_str, s._str);
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
        }

        const char* C_Str()const
        {
            return _str;
        }

        /////////////////////////////////////////////////////////////
        // capacity
        size_t size()const
        {
            return _size;
        }

        size_t capacity()const
        {
            return _capacity;
        }

        bool empty()const
        {
            return _size == 0;
        }

        void resize(size_t newSize, char c = '\0')
        {
            if (newSize > _size)
            {
                // 如果newSize大于底层空间大小，则需要重新开辟空间
                if (newSize > _capacity)
                {
                    reserve(newSize);
                }
                memset(_str + _size, c, newSize - _size);
            }
            _size = newSize;
            _str[newSize] = '\0';
        }

        void reserve(size_t newCapacity)
        {
            // 如果新容量大于旧容量，则开辟空间
            if (newCapacity > _capacity)
            {
                char* str = new char[newCapacity + 1];
                strcpy(str, _str);
                // 释放原来旧空间,然后使用新空间
                delete[] _str;
                _str = str;
                _capacity = newCapacity;
            }
        }
        /////////////////////////////////////////////////////////////

        // access
        char& operator[](size_t index)
        {
            assert(index < _size);
            return _str[index];
        }

        const char& operator[](size_t index)const
        {
            assert(index < _size);
            return _str[index];
        }

        /////////////////////////////////////////////////////////////
        //relational operators
        bool operator<(const string& s)const
        {
            int res = strcmp(_str, s._str);
            if (res < 0)
                return true;
            return false;
        }

        bool operator<=(const string& s)const
        {
            return !(*this > s);
        }

        bool operator>(const string& s)const
        {
            int res = strcmp(_str, s._str);
            if (res > 0)
                return true;
            return false;
        }

        bool operator>=(const string& s)const
        {
            return !(*this < s);
        }

        bool operator==(const string& s)const
        {
            int res = strcmp(_str, s._str);
            if (res == 0)
                return true;
            return false;
        }

        bool operator!=(const string& s)const
        {
            return !(*this == s);
        }

        // 返回c在string中第一次出现的位置
        size_t find(char c, size_t pos = 0) const
        {
            for (size_t i = pos; i < _size; ++i)
            {
                if (_str[i] == c)
                    return i;//找到，返回下标
            }
            return -1;//未找到
        }

        // 返回子串s在string中第一次出现的位置
        size_t find(const char* s, size_t pos = 0) const
        {
            assert(s);
            assert(pos < _size);
            const char* src = _str + pos;
            while (*src)
            {
                const char* match = s;//如果不匹配，返回子串起始处重新查找
                const char* cur = src;
                while (*match && *match == *cur)//结束条件
                {
                    ++match;
                    ++cur;
                }
                if (*match == '\0')//找到子串
                {
                    return src - _str;//返回下标
                }
                else
                {
                    ++src;
                }
            }
            return -1;//未找到
        }

        // 在pos位置上插入字符c/字符串str，并返回该字符的位置
        string& insert(size_t pos, char c)
        {
            assert(pos <= _size);
            if (_size > _capacity)
            {
                //扩容
                char* newstr = new char[_capacity * 2 + 1];//开空间
                strcpy(newstr, _str);
                delete[] _str;
                _str = newstr;
                _capacity *= 2;
                //Expand(_capacity * 2);
            }
            //移数据
            for (int i = _size; i >= (int)pos; --i)
            {
                _str[i + 1] = _str[i];
            }
            _str[pos] = c;
            _size++;
            return *this;
        }

        string& insert(size_t pos, const char* str)
        {
            size_t len = strlen(str);
            if (_size + len > _capacity)//扩容
            {
                //扩容
                char* newstr = new char[_capacity * 2 + 1];//开空间
                strcpy(newstr, _str);
                delete[] _str;
                _str = newstr;
                _capacity *= 2;
                //Expand(_size + len);
            }
            //后移数据
            for (int i = _size; i >= (int)pos; --i)
            {
                _str[len + i] = _str[i];
            }
            //拷贝字符串
            while (*str != '\0')
            {
                _str[pos++] = *str++;
            }
            _size += len;
            return *this;
        }
        // 删除pos位置上的元素，并返回该元素的下一个位置
        string& erase(size_t pos, size_t len)
        {
            assert(pos < _size);
            if (pos + len >= _size)//pos位置之后全为0
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                strcpy(_str + pos, _str + pos + len);
                _size -= len;
            }
            return *this;
        }
    private:
        friend std::ostream& operator<<(std::ostream& _cout, const HuiGu::string& s);
        friend std::istream& operator>>(std::istream& _cin, HuiGu::string& s);
    private:
        char* _str;
        size_t _capacity;
        size_t _size;
    };
};



//输入流重载
std::istream& HuiGu::operator>>(std::istream& _cin, HuiGu::string& s)
{
    //预分配100个空间
    char* str = (char*)malloc(sizeof(char) * 100);
    char* buf = str;
    int i = 1;
    //预处理：跳过流里面的所有空格和回车
    while ((*buf = getchar()) == ' ' || (*buf == '\n'));
    for (; ; ++i)
    {
        if (*buf == '\n') //回车跳出
        {
            *buf = '\0';
            break;
        }
        else if (*buf == ' ') //空格跳出
        {
            *buf = '\0';
            break;
        }
        else if (i % 100 == 0) //空间不足
        {
            i += 100; //追加100个空间
            str = (char*)realloc(str, i);
        }
        else  //每次getchar()一个值
        {
            buf = (str + i);//为了避免realloc返回首地址改变，不使用++buf，而是用str加上偏移.
            //每次读取一个字符
            *buf = getchar();
        }
    }
    //输入完成,更新s
    s._str = str;
    s._capacity = s._size = i;
    return _cin;
}

//输出流重载
std::ostream& HuiGu::operator<<(std::ostream& _cout, const HuiGu::string& s)
{
    for (size_t i = 0; i < s.size(); ++i)
    {
        _cout << s[i];
    }
    return _cout;
}

using namespace HuiGu;

int main()
{
    string s("hello world");
    std::cout << s << std::endl;
    return 0;
}    