#pragma once

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
		// 给链表节点一个构造函数，这样申请结点的时候也顺便能够初始化了
		list_node(const T& val = T())
			: _data(val)
			, _prev(nullptr)
			, _next(nullptr)
		{}
	};

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		list()
			: _head(new Node)
		{
			_head->_next = _head;
			_head->_prev = _head;
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
	}
}

