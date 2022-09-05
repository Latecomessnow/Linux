#define _CRT_SECURE_NO_WARNINGS 1

class Solution {
public:
    string addStrings(string num1, string num2) {
        int end1 = num1.size() - 1, end2 = num2.size() - 1;
        int next = 0, ret = 0;
        string strRet;
        // ע����||������&&����Ϊ�п��ܻ�����999+1���������Ҫ������ǰ��λ
        while (end1 >= 0 || end2 >= 0)
        {
            // ע���ϱߵ��߼��ǻ��±��п��ܻ�Խ�磬Խ������0
            int val1 = end1 >= 0 ? num1[end1] - '0' : 0;
            int val2 = end2 >= 0 ? num2[end2] - '0' : 0;
            ret = val1 + val2 + next;
            next = ret > 9 ? 1 : 0;
            // // ͷ��,�߼��򵥣�����Ч�ʺܵ�
            // strRet.insert(strRet.begin(), '0' + ret % 10);
            // Ӧʹ��β�壬Ȼ��������
            strRet += ret % 10 + '0';
            end1--;
            end2--;
        }
        // �ߵ���next����Ϊ1����9+1���������ַ�0�����������ַ�1
        if (next)
            //strRet.insert(strRet.begin(), '1');
            strRet += '1';
        reverse(strRet.begin(), strRet.end());
        return strRet;
    }
};