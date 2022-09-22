#define _CRT_SECURE_NO_WARNINGS 1

class Solution {
public:
    string addStrings(string num1, string num2) {
        int end1 = num1.size() - 1, end2 = num2.size() - 1;
        int next = 0, ret = 0;
        string strRet;
        // 注意是||不能是&&，因为有可能会遇到999+1这种情况需要不断向前进位
        while (end1 >= 0 || end2 >= 0)
        {
            // 注意上边的逻辑是或，下边有可能会越界，越界了置0
            int val1 = end1 >= 0 ? num1[end1] - '0' : 0;
            int val2 = end2 >= 0 ? num2[end2] - '0' : 0;
            ret = val1 + val2 + next;
            next = ret > 9 ? 1 : 0;
            // // 头插,逻辑简单，但是效率很低
            // strRet.insert(strRet.begin(), '0' + ret % 10);
            // 应使用尾插，然后再逆置
            strRet += ret % 10 + '0';
            end1--;
            end2--;
        }
        // 走到这next可能为1，如9+1，插入了字符0，但还少了字符1
        if (next)
            //strRet.insert(strRet.begin(), '1');
            strRet += '1';
        reverse(strRet.begin(), strRet.end());
        return strRet;
    }
};
