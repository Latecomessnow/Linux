#define _CRT_SECURE_NO_WARNINGS 1

class Solution {
public:
    int firstUniqChar(string s) {
        // ����һ��26��ĸ�����飬����ĸ���ִ�����¼����
        int letter[26] = { 0 };
        for (int i = 0; i < s.size(); i++)
        {
            letter[s[i] - 'a']++;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (letter[s[i] - 'a'] == 1)
                return i;
        }
        return -1;
    }
};