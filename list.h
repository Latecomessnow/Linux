#pragma once

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
		// ������ڵ�һ�����캯���������������ʱ��Ҳ˳���ܹ���ʼ����
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
			// β�壬����β
			Node* tail = _head->_prev;
			Node* newnode = new Node(val);
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
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
	}
}

