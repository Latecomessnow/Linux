#pragma once

namespace HuiGu
{
	// �������������ȥ���췴�������
	template<class Iterator, class Ref, class Ptr>
	struct __reverse_iterator
	{
		typedef __reverse_iterator<Iterator, Ref, Ptr> Riterator;
		Iterator _cur;
		// �������������ʵ�ַ���������Ĺ��캯��
		__reverse_iterator(Iterator it)
			: _cur(it)
		{}

		// ��������������Ĳ���ʵ�ַ��������
		// �����������begin
		Riterator operator++()
		{
			_cur--;
			return *this;
		}

		Riterator operator++(int)
		{
			Riterator tmp(*this);
			_cur--;
			return tmp;
		}

		Riterator operator--()
		{
			_cur++;
			return *this;
		}

		Riterator operator--(int)
		{
			Riterator tmp(*this);
			_cur++;
			return tmp;
		}

		Ref operator*()
		{
			// ��Ϊ�����������begin�Ƿ����end�������end�Ƿ����begin��stl�е�����Ǳ��ֶԳƵ�
			// �������end��_finish����ָ�����һ��Ԫ�ص���һ��λ��
			// ���Է��������ȡԪ��ʱҪ�ȼ����ٽ�����
			Iterator tmp = _cur;
			tmp--;
			return *tmp;
		}

		Ptr operator->()
		{
			return &(operator*());
		}

		bool operator!=(const Riterator& it)
		{
			return _cur != it._cur;
		}

		bool operator==(const Riterator& it)
		{
			return _cur == it._cur;
		}
	};
}
