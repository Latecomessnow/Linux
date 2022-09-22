#define _CRT_SECURE_NO_WARNINGS 1

class Solution {
    // 类似于字符串数组vector<string>
    // 此处是常量字符串可能需要加const char*
    char* numtoStr[10] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
public:
    void Combine(string digits, int di, vector<string>& retV, string combineStr)
    {
        if (di == digits.size())
        {
            retV.push_back(combineStr);
            return;
        }
        int num = digits[di] - '0';
        string str = numtoStr[num];
        for (auto ch : str)
        {
            Combine(digits, di + 1, retV, combineStr + ch);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> v;
        if (digits.empty())
            return v;
        string str;
        Combine(digits, 0, v, str);
        return v;
    }
};