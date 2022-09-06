#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>

using namespace std;

//int main()
//{
//	vector<int>array;
//	array.push_back(100);
//	array.push_back(300);
//	array.push_back(300);
//	array.push_back(300);
//	array.push_back(300);
//	array.push_back(500);
//	vector<int>::iterator itor;
//	for (itor = array.begin(); itor != array.end(); itor++)
//	{
//		if (*itor == 300)
//		{
//			// erase返回的是pos位置的下一个迭代器
//			// 再进行++操作会跳过一个300
//			itor = array.erase(itor);
//		}
//	}
//	for (itor = array.begin(); itor != array.end(); itor++)
//	{
//
//		cout << *itor << " ";
//
//	}
//	return 0;
//}

int main()
{
	int ar[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = sizeof(ar) / sizeof(int);
	vector<int> v(ar, ar + n);
	cout << v.size() << ":" << v.capacity() << endl;
	// 注：reserve或resize中的capacity比之前小的话capacity是不变的
	v.reserve(100);
	v.resize(20);
	cout << v.size() << ":" << v.capacity() << endl;
	v.reserve(50);
	v.resize(5);
	cout << v.size() << ":" << v.capacity() << endl;
}