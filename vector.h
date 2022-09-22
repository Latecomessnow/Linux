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
//        // Vector�ĵ�������һ��ԭ��ָ��
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
//        iterator _start; // ָ�����ݿ�Ŀ�ʼ
//        iterator _finish; // ָ����Ч���ݵ�β
//        iterator _endOfStorage; // ָ��洢������β
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
				// ���ԭ�����д������ݣ�����Ҫ��������
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * sz);
					delete[] _start;
				}
				// ���¶������Ϣ
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

		// ʹ�õ�������ʾposλ��
		void insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			// ����ռ���ܲ��������ݣ���Ҫ֪�����ݺ�posλ���Ѿ������仯
			if (_finish == _end_of_storage)
			{
				// ��¼posλ����_start��ƫ����
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				// ��ʱ_start�ѱ�ʾ�¿ռ䣬�����¿ռ���posλ��
				pos = _start + len;
			}
			// Ų������
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *(end);
				end--;
			}
			*pos = x;
			_finish++;
		}

		// stl �涨erase����ɾ��λ����һ��λ�õ�����
		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);
			// pos + 1�ú�ߵ�Ԫ�ظ���ɾ��ǰ�ߵ���
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
				// ������һλ�õ�����
				it = v.erase(it);
			}
			// ��ɾ��++��һλ��
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