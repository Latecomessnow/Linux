#define _CRT_SECURE_NO_WARNINGS 1

#include"Date.h"

void TestDate1()
{
	Date d1(2022, 8, 11);
	Date d2(d1);
	Date d3;
	Date d4(2022, 10);
	Date d5(d4);
	d1.Print();
	d2.Print();
	d3.Print();
	d4.Print();
	d5.Print();
}

void TestDate2()
{
	Date d1(2022, 8, 11);
	Date d2(1900, 1, 12);
	Date d3(2020, 2, 1);
	Date d4(2020, 2, 4);
	Date d5(1988, 5, 18);
	Date d6(2042, 2, 11);
	cout << (d1 < d2) << endl;
	cout << (d2 > d3) << endl;
	cout << (d1 <= d2) << endl;
	cout << (d1 >= d2) << endl;
	cout << (d2 > d4) << endl;
	cout << (d3 != d6) << endl;
	cout << (d5 == d6) << endl;
}

void TestDate3()
{
	Date d1(2022, 8, 11);
	Date d2(1978, 1, 12);
	Date d3(2020, 2, 1);
	d1 += 100;
	d2 += 400;
	d3 += 4000;
	Date d4 = (d1 + 200);
	d1.Print();
	d2.Print();
	d3.Print();
	d4.Print();
}

void TestDate4()
{
	Date d1(2022, 8, 11);
	Date d2(1978, 1, 12);
	Date d3(2020, 2, 1);
	d1 -= -100;
	d2 += -400;
	d3 -= 4000;
	Date d4(2022, 8, 11);
	Date d5 = d4 - 200;
	d1.Print();
	d2.Print();
	d3.Print();
	d4.Print();
	d5.Print();
}

void TestDate5()
{
	Date d1(2022, 8, 11);
	Date d2(1978, 1, 12);
	Date d3(2020, 2, 1);
	Date d4(2021, 6, 1);
	//Date ret1 = d1++;
	//Date ret2 = ++d1;
	//Date ret3 = ++d2;
	//Date ret4 = ++d3;
	//Date ret5 = d4++;
	Date ret1 = d1--;
	Date ret2 = --d1;
	Date ret3 = --d2;
	Date ret4 = --d3;
	Date ret5 = d4--;
}

void TestDate6()
{
	Date d1(2022, 8, 12);
	Date d2(2023, 2, 15);
	Date d3(2090, 1, 15);
	cout << d1 - d2 << endl;
	cout << d2 - d1 << endl;
	cout << d3 - d1 << endl;
}

void TestDate7()
{
	Date d1(2022, 8, 78);
	Date d2(2023, 2, 29);
	Date d3(2090, 13, 15);
}

void TestDate8()
{
	Date d1(2022, 8, 2);
	Date d2(2023, 2, 2);
	Date d3;
	cout << d1;
	cout << d3;
	cin >> d3;
	cout << d3;
}

int main()
{
	//TestDate1();
	//TestDate2();
	//TestDate3();
	//TestDate4();
	//TestDate5();
	//TestDate6();
	//TestDate7();
	//TestDate8();
	Date d1(2022, 8, 15);
	Date d2 = d1;
	d1.Print();
	d2.Print();
	return  0;
}