#pragma once

#include<assert.h>
#include<iostream>
#include <string.h>

//namespace HuiGu
//{
//    template<class T>
//    class vector
//    {
//    public:
//        // Vector的迭代器是一个原生指针
//        typedef T* iterator;
//        typedef const T* const_iterator;
//        iterator begin();
//        iterator end();
//        const_iterator cbegin();
//        const_iterator cend() const;
//        // construct and destroy
//        vector();
//        vector(int n, const T& value = T());
//        template<class InputIterator>;
//        vector(InputIterator first, InputIterator last);
//        vector(const vector<T>& v);
//        vector<T>& operator= (vector<T> v);
//        ~vector();
//        // capacity
//        size_t size() const;
//        size_t capacity() const;
//        void reserve(size_t n);
//        void resize(size_t n, const T& value = T());
//        ///////////////access///////////////////////////////
//        T& operator[](size_t pos);
//        const T& operator[](size_t pos)const;
//        ///////////////modify/////////////////////////////
//        void push_back(const T& x);
//        void pop_back();
//        void swap(vector<T>& v);
//        iterator insert(iterator pos, const T& x);
//        iterator erase(Iterator pos);
//    private:
//        iterator _start; // 指向数据块的开始
//        iterator _finish; // 指向有效数据的尾
//        iterator _endOfStorage; // 指向存储容量的尾
//    };
//}


namespace HuiGu
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		
		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return *(_start + pos);
		}

		const T& operator[](size_t pos) const
		{
			assert(pos < size());
			return *(_start + pos);
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				// 如果原对象中存在数据，则需要拷贝数据
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * sz);
					delete[] _start;
				}
				// 更新对象的信息
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		//void resize(size_t n, const T& val = T())
		//{
		//	if (n > size())
		//	{
		//		reserve(n);
		//	}
		//	size_t sz = size();
		//	for (size_t i = sz; i < capacity(); i++)
		//	{
		//		_start[i] = val;
		//	}
		//}

		void push_back(const T& val)
		{
			//if (_finish == _end_of_storage)
			//{
			//	reserve(capacity() == 0 ? 4 : capacity() * 2);
			//}
			//*_finish = val;
			//_finish++;
			insert(end(), val);
		}

		void pop_back()
		{
			assert(_finish > _start);
			_finish--;
		}

		// 使用迭代器表示pos位置
		void insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			// 插入空间可能不够，扩容，但要知道扩容后pos位置已经发生变化
			if (_finish == _end_of_storage)
			{
				// 记录pos位置与_start的偏移量
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				// 此时_start已表示新空间，更新新空间后的pos位置
				pos = _start + len;
			}
			// 挪动数据
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *(end);
				end--;
			}
			*pos = x;
			_finish++;
		}

		// stl 规定erase返回删除位置下一个位置迭代器
		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			// pos + 1用后边的元素覆盖删除前边的数
			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				begin++;
			}
			_finish--;
			return pos;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
	void test_vector1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			std::cout << *it << " ";
			it++;
		}
		std::cout << std::endl;
		v.pop_back();
		v.pop_back();
		v.pop_back();
	}

	void test_vector2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		v.push_back(7);
		for (auto e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				// 返回下一位置迭代器
				it = v.erase(it);
			}
			// 不删除++下一位置
			else
			{
				it++;
			}
		}
		for (auto e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
}