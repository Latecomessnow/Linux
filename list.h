#pragma once

#include<iostream>
#include<algorithm>
#include<assert.h>

using namespace std;

namespace HuiGu
{
	// ģ�����
	template<class T>
	// ����ڵ�
	//class list_node
	// ���г�Ա������ȥ���ʣ�ֱ����struct���óɹ��бȽϺ�
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

	// list������
	// ��ָ��һ���Ķ���

	template<class T, class Ref, class Ptr> // ��Ref��Ptr��ģ�����������T&��T*������ֵ
	                                        // ����const��Ա�������Ͳ���Ҫ��const��Ա��дһ������
	struct __list_iterator
	{
		typedef list_node<T> Node;
		// ��������typedefһ�£��������ֹ��������㣬��Ϊlist�ĵ�������ʵ����һ������
		// ������typedef������������ʱ����Ҫע����ʽʵ����������ģ����������ͣ�������vectro<int>
		//typedef __list_iterator<T> iterator;
		typedef __list_iterator<T, Ref, Ptr> iterator;

		// list�ĵ�������Ҫһ������ڵ�
		Node* _node;
		// �����ʼ���������еĽڵ�
		__list_iterator(Node* node)
			: _node(node)
		{}

		// ����������Ҫд��������
		// Ҳ����Ҫд�������죬��ֵ����ɶ�ģ�Ĭ�����ɵ�ǳ�����͹����ˣ�ϣ������ָ�����ͬһ��ռ�
		bool operator!=(const iterator& it) const
		{
			// ע��˴�it��һ������������ʹ��it->_node�Ǵ����
			// ��������Լ��ĳ�Ա����Ӧ��ʹ��"." 
			//return _node != it->_node;
			return _node != it._node;
		}

		bool operator==(const iterator& it)
		{
			return _node == it._node;
		}

		// ��������֧�ֽ����ò���
		// *it --> it.operator*()
		// const T&operator()
		// �����const��Ա�ǵ������ģ����Ƿ���ֵ��ͬ�ֲ��������أ�
		// ������Ref������ֵ��ʵ������T&��const T&
		//T& operator*()
		Ref operator*()
		{
			return _node->_data;
		}

		// ->����
		//T* operator->()
		Ptr operator->()
		{
			return &(operator*());
			// �൱��&(_node->_data)
		}

		// ������++���ص���Ȼ��һ��������
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
		// typedef���ܵ������޶��������ƣ�˽�еĻ�ֻ�Ǹ������ʹ��
		typedef list_node<T> Node;
	public:
		// ��������typedef�����óɹ��У������������������ܹ�ʹ������Ķ���ĵ�������
		// ���������ʵ����һ����ʽʵ����������������ˣ�������T
		//typedef __list_iterator<T> iterator;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		// begin���ڱ�λ����һ���ڵ�
		iterator begin()
		{
			// ����__list_iterator�Ĺ��캯��
			return iterator(_head->_next);
		}

		// end���ڱ�λ
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
			// β�壬����β
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
			// ǰ��--
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
			// insert���ز���Ԫ��λ�õĵ�����
			return iterator(newnode);
		}

		// erase����ɾ��λ�õ���һ��Ԫ�صĵ�����
		iterator erase(iterator pos)
		{
			// ����ɾ���ڱ�λ��ͷ�ڵ�
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
		// listֻ��Ҫһ��ָ��������ڱ�λָ�뼴��
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
		// list�������Զ������͵�ʱ������һ��"->"��ܷ���
		list<Pos> lt;
		lt.push_back(Pos(10, 20));
		lt.push_back(Pos(30, 40));
		list<Pos>::iterator it = lt.begin();
		while (it != lt.end())
		{
			// �Ƚ������ҵ�����ṹ��
			//cout << (*it)._row << ":" << (*it)._col << endl;
			// ������ʵΪ���﷨�ĵĿɶ���ʡ����һ��->
			// it->->_row, ��һ��->��it.operator->(), ����һ���ṹ��ָ��T*, Ȼ��T->��ȥ���ʳ�Ա	
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

