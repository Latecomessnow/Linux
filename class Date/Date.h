#pragma once

#include<iostream>
#include<assert.h>

using namespace std;

class Date
{
public:
	// ��Ԫ���� -- ��������ڲ�����ʹ��Date�������˽�б�����Ա
	friend inline ostream& operator<<(ostream& out, const Date& d);
	friend inline istream& operator>>(istream& in, Date& d);
	// ��ȡĳ��ĳ�µ��������ᱻƵ���������ó�����
	int GetMonthDay(int year, int month)
	{
		//���·��������óɾ�̬������ÿһ�ε��ú�Ͳ��ᱻ������
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			day++;
		}
		return day;
	}
	bool CheckDate()
	{
		if (_year >= 1
			&& (_month >= 1 && _month <= 12)
			&& (_day >= 1 && _day <= GetMonthDay(_year, _month)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// ȫȱʡ�Ĺ��캯��
	// ���캯���ᱻƵ�����ã����Կ����ó�����
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		//����ʱ�������ڼ��
		if (!CheckDate())
		{
			Print();
			cout << "DATE ERROR" << endl;
		}
	}
	// ����Ҫ�ı�thisָ��ָ�����ݵĻ������ó�const����thisָ��---const Date* const this
	// �������۶����Ƿ��Ǿ�̬�Ķ��ܹ����ʵ���Ա������
	// Ȩ��ֻ�ܹ�ƽ�ƻ���С
	void Print() const;
	bool operator==(const Date& d) const;
	bool operator!=(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	Date operator+(int day) const;
	Date& operator+=(int day);
	Date operator-(int day) const;
	Date& operator-=(int day);
	// d1 - d2
	int operator-(const Date& d) const;
	// Ĭ��ǰ��++������++��Ҫ���ϲ���int
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
private:
	int _year;
	int _month;
	int _day;
};

// ���������������
inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
	return out;
}

// ����ȡ���������
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	assert(d.CheckDate());
	return in;
}
