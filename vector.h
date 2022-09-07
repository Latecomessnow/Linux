#pragma once

#include<assert.h>

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

		vector(cosnt vector<T>& v)
		{
			int sz = size();
			T* tmp = new T[sz + 1];
			memcpy(tmp, v._start, sizeof(T) * sz);
			delete[] _start;
			_start = tmp;
			_finish = _end_of_storage = v._finish;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() cosnt
		{
			return _end_of_storage;
		}

		vloid push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity * 2);
			}
			_finish = x;
			_finish++;
		}

		void test_vector1()
		{
			vector v1;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
}