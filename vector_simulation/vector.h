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
		
		// n ��val�Ĺ���
		// T()��T���͵������������������ȥ����Ĭ�Ϲ���,�൱������������ȥ��ʼ������ȱʡֵ
		// ����string��ȥ��������Ĭ�Ϲ��죬vector<vecotr<int>>Ҳ��ȥ��������Ĭ�Ϲ���
		// int����Ҳ�����int����Ĭ�Ϲ����ȱʡֵ��0
		vector(size_t  n, const T& val = T())
			// �����˹��캯����ʼ��һ��
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

		// ��Ҫ��һ��int���͵ĺ������أ�����(10, 1)��ƥ�䵽���������乹��
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
		// ��ͳд��
		//vector(const vector<T>& v)
		//{
		//	// ���ÿռ�Ȼ���ٿ���
		//	_start = new T[v.size()];// Ҳ���Ը�v.capcity()
		//	// �˴���T��һ���Զ�������memcpyʵ�ֵ���ǳ����
		//	// ����vector<vector<int>>�еĵ�һ�ο���vector<vector<int>>ʵ�������
		//	// ���ǵڶ��ο���vector<int>��memcpy��vector<int>�е�_start��_finish��_end_of_storage
		//	// ǳ��������һ�����У���ʱ�����������е�vector<int>ָ�����ͬһ��ռ�
		//	// ������ʱ����������Σ�ͬһ��ռ䲻�����������Σ�����
		//	// ���Դ˴���Ҫ���ø�������ʵ�����
		//	//memcpy(_start, v._start, sizeof(T) * v.size());
		//	// reverse�еĿ���Ҳ����ڴ����⣬������memcpyǳ����
		//	for (size_t i = 0; i < v.size(); i++)
		//	{
		//		_start[i] = v._start[i];
		//	}
		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.size();
		//}

		// v2(v1)
		// �ִ�д��
		//vector(const vector<int>& v)
		//	// �ȳ�ʼ���б���reserve���ÿռ䣬push_back����Ԫ�ؾͿ�����
		//	: _start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	reserve(v.size());
		//	// ע��˴������ã���ֹ�����������죬����Ч�ʣ��ر������
		//	for (const auto& e : v)
		//	{
		//		push_back(e);
		//	}
		//}

		// v2(v1)
		// ���캯���ִ�д��
		// ���������乹�� + swap
		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}

		// ��һ��ֻ��vector�ĵ������������һ��ģ�������������ĵ�������Ҳ���Թ����ˣ���string��list
		// ģ�����滹���Զ���������ģ��
		template <class InputIterator>
		// ���������乹��
		vector(InputIterator first, InputIterator last)
		// ע��˴���Ҫ���˳�ʼ���б�, ����push_back�е�reverse�ڽ�������ʱ
		// ��Ϊ���û�г�ʼ��_start��_finish��end_of_storage�������ֵ
		// ������Ϊreverse�����������ʱ_start��Ϊ����´�����ݵ��¿ռ�
		// ��ʱ��Ա�����������ֵ�������ֵ�Ŀ�����Խ����Ϊ���������
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				// push_back�д���reverse
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
				// ���ԭ�����д������ݣ�����Ҫ��������
				if (_start)
				{
					// �˴�Ϊǳ���������ڿ����Զ������͵Ķ��������������ε�����
					//memcpy(tmp, _start, sizeof(T) * sz);
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				// ���¶������Ϣ
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			// n ���� capacity,���ݼӳ�ʼ��
			if (n > capacity())
			{
				reserve(n);
			}
			// ���n > size��ֵ, ��finish��ʼ��
			if (n > size())
			{
				while (_finish < _start + n)
				{
					*_finish = val;
					_finish++;
				}
			}
			// n < size��ɾ������
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

		//// ʹ�õ�������ʾposλ��
		//void insert(iterator pos, const T& x)
		//{
		//	assert(pos >= _start);
		//	assert(pos <= _finish);
		//	// ����ռ���ܲ��������ݣ���Ҫ֪�����ݺ�posλ���Ѿ������仯
		//	if (_finish == _end_of_storage)
		//	{
		//		// ��¼posλ����_start��ƫ����
		//		size_t len = pos - _start;
		//		reserve(capacity() == 0 ? 4 : capacity() * 2);
		//		// ��ʱ_start�ѱ�ʾ�¿ռ䣬�����¿ռ���posλ��
		//		pos = _start + len;
		//	}
		//	// Ų������
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
			// ������ܻ�����
			if (_finish == _end_of_storage)
			{
				// ��¼ƫ����
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				// ����posλ��
				pos = _start + len;
			}
			// ��pos��pos���Ԫ�������ƶ�
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = val;
			_finish++;
			// ����posλ�õĵ�����
			return pos;
		}

		//stl �涨erase����ɾ��λ����һ��λ�õ�����
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
		// �Ȱ�v2ԭ�ȵĿռ��ͷţ�Ȼ���ٰ�v1�������쵽v2��
		// ����ֱ�����ô���Ҳ��һ�ο�������
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
				// ����insert���صĵ�������������ż��ǰ�����ż����2��
				it = v.insert(it, *it * 2);
				it++;// ��һ��++��ԭ��������λ��
				it++;// �ڶ���++����һ��λ��
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
			// ɾ�����е�ż����ע�����һ����ż����������ż���ȵ�
			// erase����ɾ���Ǹ�λ�õ���һ��������
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
		// �˴���ɵ����������v1���޸Ĳ�����Ӱ��v
		// ���캯��: 1.�������Ͳ�����   2.�Զ������ͻ�ȥ�������Ĺ��캯��
		// �������캯��: 1.�������ͻ����ǳ����   2.�Զ������ͻ�ȥ�����Ŀ�������
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
		// ��ֵ��������Ѿ����ڵĶ���Ż�ȥ���ø�ֵ����
		// ��������ʵ�ǵȼ���vector<int> copy(v1)�����ÿ�������
		vector<int> copy(v1);
		for (const auto& e : copy)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	void test_vector8()
	{
		// ��������Ҳ�Ǵ���Ĭ�Ϲ����
		int i = 0;
		int j = int(); // 0
		int k = int(10);// 10
		//int* p = int* ();
	}

	void test_vector9()
	{
		vector<char> v(5, 'a');
		vector<int*> v1(10);
		// ��ʱ�������n��val��int���͵ĺ������أ�����ᱨ��
		// һ����unsign int��һ����int����ƥ�䵽IntputIterator
		// ��Ϊ��ʱ��ƥ�䵽�����ʵĵ��������乹�죬������Ĳ��������ǵ�����
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

	// ��ֵ����Ҳ��һ�ο�������
	// ���������һ��vector<vector<int>>�����
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
		// ��ֵ����Ҳ��һ�ο�������
		vector<vector<int>> ret = Solution().generate(5);
	}
}