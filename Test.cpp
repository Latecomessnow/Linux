#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

//int main(int argc, char* argv[])
//
//{
//
//	string a = "hello world";
//
//	string b = a;
//
//	if (a.c_str() == b.c_str())
//
//	{
//
//		cout << "true" << endl;
//
//	}
//
//	else cout << "false" << endl;
//
//	string c = b;
//
//	c = "";
//
//	if (a.c_str() == b.c_str())
//
//	{
//
//		cout << "true" << endl;
//
//	}
//
//	else cout << "false" << endl;
//
//	a = "";
//
//	if (a.c_str() == b.c_str())
//
//	{
//
//		cout << "true" << endl;
//
//	}
//
//	else cout << "false" << endl;
//
//	return 0;
//
//}
//

//int main()
//
//{
//
//	string str("Hello Bit.");
//
//	str.reserve(111);
//
//	//str.resize(5);
//
//	//str.reserve(50);
//
//	cout << str.size() << ":" << str.capacity() << endl;
//	cout << str << endl;
//
//	return 0;
//
//}

int main(int argc, char* argv[])
{
	string strText = "How are you?";
	string strSeparator = " ";
	string strResult;
	int size_pos = 0;
	int size_prev_pos = 0;
	while ((size_pos = strText.find_first_of(strSeparator, size_pos)) != string::npos)
	{
		strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
		cout << strResult << " ";
		size_prev_pos = ++size_pos;
	}
	if (size_prev_pos != strText.size())
	{
		strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
		cout << strResult << " ";
	}
	cout << endl;
	return 0;
}

class Solution {
public:
    int StrToInt(string str) {
        int index = 0, len = str.size(), flag = 1, result = 0;
        // 跳空格
        while (str[index] == ' ' && index < len)
            index++;
        // 如果第一个字符为+-，处理一下
        if (str[index] == '+')
            index++;
        else if (str[index] == '-')
        {
            flag = -1;
            index++;
        }
        // 循环处理数字字符
        while (index < len && isdigit(str[index]))
        {
            // 把字符转换成数字并加在一起
            // 还要考虑越的问题，INT_MAX & INT_MIN
            result = result * 10 + (str[index] - '0');
            if (result > INT_MAX && flag == 1)
                return INT_MAX;
            if (result > INT_MAX && flag == -1)
                return INT_MIN;
            index++;
        }
        // 走到这有可能是走完字符串了也有可能是遇到字母跳出循环
        if (index == len)
            return flag * result;
        return 0;
    }
};