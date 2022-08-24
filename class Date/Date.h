#pragma once

#include<iostream>
#include<assert.h>

using namespace std;

class Date
{
public:
	// 友元函数 -- 这个函数内部可以使用Date对象访问私有保护成员
	friend inline ostream& operator<<(ostream& out, const Date& d);
	friend inline istream& operator>>(istream& in, Date& d);
	// 获取某年某月的天数，会被频繁调用设置成内敛
	int GetMonthDay(int year, int month)
	{
		//把月份天数设置成静态，这样每一次调用后就不会被销毁了
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
	// 全缺省的构造函数
	// 构造函数会被频繁调用，所以可设置成内敛
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		//构造时加入日期检查
		if (!CheckDate())
		{
			Print();
			cout << "DATE ERROR" << endl;
		}
	}
	// 不需要改变this指针指向内容的话可设置成const修饰this指针---const Date* const this
	// 这样无论对象是否是静态的都能够访问到成员函数了
	// 权限只能够平移或缩小
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
	// 默认前置++，后置++需要加上参数int
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
private:
	int _year;
	int _month;
	int _day;
};

// 流插入运算符重载
inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
	return out;
}

// 流提取运算符重载
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	assert(d.CheckDate());
	return in;
}
