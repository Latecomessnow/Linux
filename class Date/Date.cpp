#define _CRT_SECURE_NO_WARNINGS 1

#include"Date.h"

void Date::Print() const
{
	cout << _year << "/" << _month << "/" << _day << endl;
}

bool Date::operator==(const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

bool Date::operator!=(const Date& d) const
{
	return !(*this == d);
}

// d1 > d2
bool Date::operator>(const Date& d) const
{
	if (_year > d._year)
	{
		return true;
	}
	else if ((_year == d._year)
		&& (_month > d._month))
	{
		return true;
	}
	else if ((_year == d._year)
		&& (_month == d._month)
		&& (_day > d._day))
	{
		return true;
	}
	return false;
}

bool Date::operator>=(const Date& d) const
{
	return (*this > d) || (*this == d);
}

bool Date::operator<(const Date& d) const
{
	return !(*this >= d);
}

bool Date::operator<=(const Date& d) const
{
	return !(*this > d);
}

// d1 + 100
// +复用无拷贝构造的+=去减少拷贝构造
Date Date::operator+(int day) const
{
	Date ret = *this;
	ret += day;
	return ret;
}

// d1 = d1 + 100
// += 之后this还在所以可以用传引用返回，减少拷贝构造
Date& Date::operator+=(int day)
{
	// 天数为负时处理一下
	if (day < 0)
	{
		return *this -= -day;
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}

Date Date::operator-(int day) const
{
	Date ret = *this;
	ret -= day;
	return ret;
}

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	while (_day < 1)
	{
		_month--;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

// d1 - d2
int Date::operator-(const Date& d) const
{
	int flag = 1;
	Date max = *this;
	Date min = d;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int day = 0;
	while (min != max)
	{
		min++;
		day++;
	}
	return day * flag;
}

Date& Date::operator++()
{
	//*this += 1;
	//return *this;
	return *this += 1;
}

Date Date::operator++(int)
{
	Date tmp = *this;
	*this += 1;
	return tmp;
}

Date& Date::operator--()
{
	return *this -= 1;
}

Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}