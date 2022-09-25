#pragma once

#include<iostream>
#include<algorithm>
#include<assert.h>

using namespace std;

namespace HuiGu
{
	// 模板参数
	template<class T>
	// 链表节点
	//class list_node
	// 所有成员都可以去访问，直接用struct设置成共有比较好
	struct list_node
	{
		T _data;
		list_node<T>* _prev;
		list_node<T>* _next;
		list_node(const T& val = T())
			: _data(val)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};

	// list迭代器
	// 像指针一样的对象

	template<class T, class Ref, class Ptr> // 给Ref、Ptr的模板参数，传入T&、T*做返回值
	                                        // 区分const成员，这样就不需要给const成员另写一个类了
	struct __list_iterator
	{
		typedef list_node<T> Node;
		// 给迭代器typedef一下，避免名字过长不方便，因为list的迭代器其实就是一个对象，
		// 所以在typedef、创建迭代器时都需要注意显式实例化，加上模板参数的类型，类似于vectro<int>
		//typedef __list_iterator<T> iterator;
		typedef __list_iterator<T, Ref, Ptr> iterator;

		// list的迭代器需要一个链表节点
		Node* _node;
		// 构造初始化迭代器中的节点
		__list_iterator(Node* node)
			: _node(node)
		{}

		// 迭代器不需要写析构函数
		// 也不需要写拷贝构造，赋值重载啥的，默认生成的浅拷贝就够用了，希望他们指向的是同一块空间
		bool operator!=(const iterator& it) const
		{
			// 注意此处it是一个迭代器对象，使用it->_node是错误的
			// 对象访问自己的成员变量应该使用"." 
			//return _node != it->_node;
			return _node != it._node;
		}

		bool operator==(const iterator& it)
		{
			return _node == it._node;
		}

		// 迭代器都支持解引用操作
		// *it --> it.operator*()
		// const T&operator()
		// 如果是const成员是调不到的，但是返回值不同又不构成重载，
		// 所以用Ref做返回值，实例化出T&、const T&
		//T& operator*()
		Ref operator*()
		{
			return _node->_data;
		}

		// ->重载
		//T* operator->()
		Ptr operator->()
		{
			return &(operator*());
			// 相当于&(_node->_data)
		}

		// 迭代器++返回的仍然是一个迭代器
		// ++it
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		// it++
		iterator operator++(int)
		{
			//iterator tmp(*this);
			iterator tmp = _node;
			_node = _node->_next;
			return tmp;
		}

		// --it
		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		// it--
		iterator operator--(int)
		{
			iterator tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
	};

	template<class T>
	class list
	{
		// typedef会受到访问限定符的限制，私有的话只是给这个类使用
		typedef list_node<T> Node;
	public:
		// 将迭代器typedef并设置成共有，这样在这个类里面就能够使用外面的定义的迭代器类
		// 这里的类其实就是一个显式实例化出来的类对象了，类型是T
		//typedef __list_iterator<T> iterator;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		// begin是哨兵位的下一个节点
		iterator begin()
		{
			// 调用__list_iterator的构造函数
			return iterator(_head->_next);
		}

		// end是哨兵位
		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		list()
			: _head(new Node)
		{
			_head->_next = _head;
			_head->_prev = _head;
		}

		~list()
		{
			delete _head;
			_head = nullptr;
		}

		void push_back(const T& val)
		{
			// 尾插，先找尾
			Node* tail = _head->_prev;
			Node* newnode = new Node(val);
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
			//insert(end(), val);
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_back()
		{
			// 前置--
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator insert(iterator pos, const T& val)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode = new Node(val);
			// cur newnode prev
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			// insert返回插入元素位置的迭代器
			return iterator(newnode);
		}

		// erase返回删除位置的下一个元素的迭代器
		iterator erase(iterator pos)
		{
			// 不能删除哨兵位的头节点
			assert(pos != end());
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			prev->_next = next;
			next->_prev = prev;
			delete cur;
			return iterator(next);
		}

	private:
		// list只需要一个指向链表的哨兵位指针即可
		Node* _head;
	};

	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it * 2 << " ";
			it++;
		}
		cout << endl;
		for (auto& e : lt)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	struct Pos
	{
		int _row;
		int _col;
		Pos(int row = 0, int col = 0)
			: _row(row)
			, _col(col)
		{}
	};

	void test_list2()
	{
		Pos a;
		Pos* p = &a;
		p->_row;
		p->_row;
		// list里存的是自定义类型的时候重载一个"->"会很方便
		list<Pos> lt;
		lt.push_back(Pos(10, 20));
		lt.push_back(Pos(30, 40));
		list<Pos>::iterator it = lt.begin();
		while (it != lt.end())
		{
			// 先解引用找到这个结构体
			//cout << (*it)._row << ":" << (*it)._col << endl;
			// 这里其实为了语法的的可读性省略了一个->
			// it->->_row, 第一个->调it.operator->(), 返回一个结构体指针T*, 然后T->再去访问成员	
			cout << it->_row << ":" << it->_col << endl;
			it++;
		}
	}


	void Func(const list<int>& lt)
	{
		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			//*it = 10;
			cout << *it << " ";
			it++;
		}
		cout << endl;
	}

	void test_list3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		Func(lt);
		//list<int>::iterator it = lt.begin();
		//list<int>::iterator ret = it++;
		//list<int>::iterator ret2 = ++it;
	}

	void test_list4()
	{
		list<int> lt;
		//lt.push_back(1);
		//lt.push_back(2);
		//lt.push_back(3);
		//lt.push_back(4);
		lt.push_front(1);
		lt.push_front(2);
		lt.push_front(3);
		lt.push_front(4);
		for (auto& e : lt)
		{
			cout << e << " ";
		}
		cout << endl;
		list<int>::iterator it = lt.begin();
		//lt.erase(it);
		lt.pop_back();
		for (auto& e : lt)
		{
			cout << e << " ";
		}
		cout << endl;
		lt.pop_front();
		for (auto& e : lt)
		{
			cout << e << " ";
		}
		cout << endl;
	}

}

