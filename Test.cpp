#define _CRT_SECURE_NO_WARNINGS 1

class Solution {
public:
    int firstUniqChar(string s) {
        // 创建一个26字母的数组，把字母出现次数记录下来
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