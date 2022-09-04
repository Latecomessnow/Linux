#define _CRT_SECURE_NO_WARNINGS 1

#include"string.h"
using namespace bit;

//int main()
//{
//	const char* str = "";
//	cout << strlen(str) << endl;
//	return 0;
//}

void StringTest1()
{
	string s1 = "hello";
	string s2(s1);
	const string s3 = "world";
	//cout << s1.begin() << endl;
	//cout << s1.end() << endl;
	//cout << s2.begin() << endl;
	//cout << s2.end() << endl;
	//cout << s3.begin() << endl;
	string s4 = s1;
}

void StringTest2()
{
	//string s1 = "hello";
	string s1("hello");
	string s2("world");
	s1 = s2;
}

void StringTest3()
{
	string s1("hello");
	for (size_t i = 0; i < s1.size(); i++)
	{
		s1[i]++;
	}
}

void StringTest4()
{
	string s;
	string s1("hello");
	s1.reserve(10);
	s1.resize(20);
	s1.resize(5);
}

void StringTest5()
{
	string s1("hello");
	s1.push_back(' ');
	s1.push_back('w');
	s1.push_back('o');
	s1.push_back('r');
	s1.push_back('l');
	s1.push_back('d');
	string s2;
	s2.push_back('h');
	s2.push_back('e');
	s2.push_back('l');
	s2.push_back('l');
	s2.push_back('o');
	std::cout << s1.c_str() << std::endl;
	std::cout << s2.c_str() << std::endl;
	s2.append(" world");
	std::cout << s2.c_str() << std::endl;
	s2.append(s1);
	std::cout << s2.c_str() << std::endl;
	s1.append(5, 'x');
	std::cout << s1.c_str() << std::endl;

}

void StringTest6()
{
	string s1("hello");
	//s1.insert(5, " world");
	//s1.insert(1, "world");
	std::cout << s1.c_str() << std::endl;
	s1.append("world");
	std::cout << s1.c_str() << std::endl;

}

void StringTest7()
{
	string s1("hello");
	//s1.erase(0);
	s1.erase(1, 2);
	s1.clear();
}

void StringTest8()
{
	string s1("hello world");
	string s3("hello world");
	string s2("right");
	size_t pos = s1.find("world");
	//cout << pos << endl;
	//cout << (s1 > s2) << endl;
	cout << (s1 == s3) << endl;
	cout << (s1 == s2) << endl;
}

void StringTest9()
{
	string s1("hello");
	s1 += "world";
	string s2 = "xxx";
	cout << s1.c_str() << endl;
	s1 += s2;
	cout << s1.c_str() << endl;

}

int main()
{
	//StringTest1();
	//StringTest2();
	//StringTest3();
	//StringTest4();
	//StringTest5();
	//StringTest6();
	//StringTest7();
	//StringTest8();
	StringTest9();
	return 0;
}