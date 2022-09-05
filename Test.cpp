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
        // ���ո�
        while (str[index] == ' ' && index < len)
            index++;
        // �����һ���ַ�Ϊ+-������һ��
        if (str[index] == '+')
            index++;
        else if (str[index] == '-')
        {
            flag = -1;
            index++;
        }
        // ѭ�����������ַ�
        while (index < len && isdigit(str[index]))
        {
            // ���ַ�ת�������ֲ�����һ��
            // ��Ҫ����Խ�����⣬INT_MAX & INT_MIN
            result = result * 10 + (str[index] - '0');
            if (result > INT_MAX && flag == 1)
                return INT_MAX;
            if (result > INT_MAX && flag == -1)
                return INT_MIN;
            index++;
        }
        // �ߵ����п����������ַ�����Ҳ�п�����������ĸ����ѭ��
        if (index == len)
            return flag * result;
        return 0;
    }
};