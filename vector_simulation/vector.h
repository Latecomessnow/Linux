#pragma once

#include<iostream>
#include<assert.h>
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
		
		// n 个val的构造
		// T()是T类型的匿名对象，匿名对象会去调用默认构造,相当于用匿名对象去初始化，做缺省值
		// 例如string回去调用它的默认构造，vector<vecotr<int>>也会去调用他的默认构造
		// int类型也会调，int类型默认构造的缺省值是0
		vector(size_t  n, const T& val = T())
			// 别忘了构造函数初始化一下
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// 需要给一个int类型的函数重载，否则(10, 1)会匹配到迭代器区间构造
		vector(int n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// v2(v1)
		// 传统写法
		//vector(const vector<T>& v)
		//{
		//	// 开好空间然后再拷贝
		//	_start = new T[v.size()];// 也可以给v.capcity()
		//	// 此处当T是一个自定义类型memcpy实现的是浅拷贝
		//	// 例如vector<vector<int>>中的第一次拷贝vector<vector<int>>实现了深拷贝
		//	// 但是第二次拷贝vector<int>是memcpy把vector<int>中的_start、_finish、_end_of_storage
		//	// 浅拷贝到另一对象中，此时这两个对象中的vector<int>指向的是同一块空间
		//	// 析构的时候会析构两次，同一块空间不允许析构两次，报错
		//	// 所以此处需要调用复制重载实现深拷贝
		//	//memcpy(_start, v._start, sizeof(T) * v.size());
		//	// reverse中的拷贝也会存在此问题，不能用memcpy浅拷贝
		//	for (size_t i = 0; i < v.size(); i++)
		//	{
		//		_start[i] = v._start[i];
		//	}
		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.size();
		//}

		// v2(v1)
		// 现代写法
		//vector(const vector<int>& v)
		//	// 先初始化列表，在reserve开好空间，push_back插入元素就可以了
		//	: _start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	reserve(v.size());
		//	// 注意此处给引用，防止发生拷贝构造，降低效率，特别是深拷贝
		//	for (const auto& e : v)
		//	{
		//		push_back(e);
		//	}
		//}

		// v2(v1)
		// 构造函数现代写法
		// 迭代器区间构造 + swap
		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}

		// 不一定只是vector的迭代器，这里给一个模板参数，其他类的迭代器就也可以构造了，如string、list
		// 模板里面还可以定义其他的模板
		template <class InputIterator>
		// 迭代器区间构造
		vector(InputIterator first, InputIterator last)
		// 注意此处不要忘了初始化列表, 否则push_back中的reverse在进行扩容时
		// 因为如果没有初始化_start、_finish、end_of_storage都是随机值
		// 而又因为reverse中如果在扩容时_start不为空则会拷贝数据到新空间
		// 此时成员变量都是随机值，对随机值的拷贝是越界行为，程序崩溃
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				// push_back中存在reverse
				push_back(*first);
				first++;
			}
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
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
					// 此处为浅拷贝，对于拷贝自定义类型的对象会存在析构两次的问题
					//memcpy(tmp, _start, sizeof(T) * sz);
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				// 更新对象的信息
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			// n 大于 capacity,扩容加初始化
			if (n > capacity())
			{
				reserve(n);
			}
			// 如果n > size填值, 从finish开始填
			if (n > size())
			{
				while (_finish < _start + n)
				{
					*_finish = val;
					_finish++;
				}
			}
			// n < size，删除数据
			else
			{
				_finish = _start + n; 
			}
		}

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

		//// 使用迭代器表示pos位置
		//void insert(iterator pos, const T& x)
		//{
		//	assert(pos >= _start);
		//	assert(pos <= _finish);
		//	// 插入空间可能不够，扩容，但要知道扩容后pos位置已经发生变化
		//	if (_finish == _end_of_storage)
		//	{
		//		// 记录pos位置与_start的偏移量
		//		size_t len = pos - _start;
		//		reserve(capacity() == 0 ? 4 : capacity() * 2);
		//		// 此时_start已表示新空间，更新新空间后的pos位置
		//		pos = _start + len;
		//	}
		//	// 挪动数据
		//	iterator end = _finish - 1;
		//	while (end >= pos)
		//	{
		//		*(end + 1) = *(end);
		//		end--;
		//	}
		//	*pos = x;
		//	_finish++;
		//}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			// 插入可能会扩容
			if (_finish == _end_of_storage)
			{
				// 纪录偏移量
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				// 更新pos位置
				pos = _start + len;
			}
			// 将pos及pos后的元素往后移动
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = val;
			_finish++;
			// 返回pos位置的迭代器
			return pos;
		}

		//stl 规定erase返回删除位置下一个位置迭代器
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

		//iterator erase(iterator pos)
		//{
		//	assert(pos >= _start);
		//	assert(pos < _finish);
		//	iterator begin = pos + 1;
		//	while (begin < _finish)
		//	{
		//		*(begin - 1) = *begin;
		//		begin++;
		//	}
		//	_finish--;
		//	return pos;
		//}

		// v2 = v1
		// 先把v2原先的空间释放，然后再把v1拷贝构造到v2中
		// 这里直接利用传参也是一次拷贝构造
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		T& front()
		{
			assert(size() > 0);
			return *_start;
		}

		T& back()
		{
			assert(size() > 0);
			return *(_finish - 1);
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

	void test_vector3()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		auto it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				// 接受insert返回的迭代器，在所有偶数前插入该偶数的2倍
				it = v.insert(it, *it * 2);
				it++;// 第一次++到原来的数的位置
				it++;// 第二次++到下一个位置
			}
			else
			{
				it++;
			}
		}
		for (const auto& e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

	void test_vector4()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(3);
		v.push_back(4);
		v.push_back(4);
		v.push_back(5);
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			// 删除所有的偶数，注意最后一个是偶数，连续的偶数等等
			// erase返回删除那个位置的下一个迭代器
			if (*it % 2 == 0)
			{
				v.erase(it);
			}
			else
			{
				it++;
			}
		}
		for (const auto& e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

	void test_vector5()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		for (const auto& e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		vector<int> v1(v);
		for (const auto& e : v1)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		// 此处完成的是深拷贝，对v1的修改并不会影响v
		// 构造函数: 1.内置类型不处理   2.自定义类型回去调用它的构造函数
		// 拷贝构造函数: 1.内置类型会进行浅拷贝   2.自定义类型会去调他的拷贝构造
		v1[0] *= 2;
		for (const auto& e : v1)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		for (const auto& e : v)
		{
			std::cout << e << " ";
		}
	}

	void test_vector6()
	{
		std::string s("abcdef");
		vector<int> v(s.begin(), s.end());
		for (const auto& e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	void test_vector7()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int> v2(v1.begin(), v1.end());
		for (const auto& e : v1)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		//for (const auto& e : v2)
		//{
		//	std::cout << e << " ";
		//}
		//std::cout << std::endl;
		for (auto& e : v2)
		{
			e *= 2;
			std::cout << e << " ";
		}
		std::cout << std::endl;
		v2 = v1;
		for (const auto& e : v2)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		// 赋值是针对于已经存在的对象才会去调用赋值重载
		// 像如下其实是等价于vector<int> copy(v1)，调用拷贝构造
		vector<int> copy(v1);
		for (const auto& e : copy)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	void test_vector8()
	{
		// 内置类型也是存在默认构造的
		int i = 0;
		int j = int(); // 0
		int k = int(10);// 10
		//int* p = int* ();
	}

	void test_vector9()
	{
		vector<char> v(5, 'a');
		vector<int*> v1(10);
		// 此时如果不给n个val的int类型的函数重载，编译会报错
		// 一个是unsign int，一个是int，会匹配到IntputIterator
		// 因为此时会匹配到更合适的迭代器区间构造，而传入的参数都不是迭代器
		vector<int> v2(10, 1);
		for (const auto& e : v)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		for (const auto& e : v1)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
		for (const auto& e : v2)
		{
			std::cout << e << " ";
		}
	}
	void test_vector10()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.reserve(10);
		//v.resize(20);
		//v.resize(8, 10);
		v.resize(2);
		vector<int> v1;
		v1.resize(10, 0);
	}

	void test_vector11()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		std::cout << v.front() << std::endl;
		std::cout << v.back() << std::endl;
		vector<int> v1(v);
		for (const auto& e : v1)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	// 传值返回也是一次拷贝构造
	// 杨辉三角试一试vector<vector<int>>的深拷贝
	class Solution {
	public:
		vector<vector<int>> generate(int numRows) {
			vector<vector<int>> vv;
			vv.resize(numRows);
			for (size_t i = 0; i < vv.size(); ++i)
			{
				vv[i].resize(i + 1, 0);
				vv[i].front() = vv[i].back() = 1;
			}
			for (size_t i = 0; i < vv.size(); ++i)
			{
				for (size_t j = 0; j < vv[i].size(); ++j)
				{
					if (vv[i][j] == 0)
					{
						vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
					}
				}
			}
			for (size_t i = 0; i < vv.size(); ++i)
			{
				for (size_t j = 0; j < vv[i].size(); ++j)
				{
					std::cout << vv[i][j] << " ";
				}
				std::cout << std::endl;
			}
			//vector<vector<int>> ret = vv;
			return vv;
		}
	};

	void test_vector12()
	{
		// 传值返回也是一次拷贝构造
		vector<vector<int>> ret = Solution().generate(5);
	}
}