#pragma once

#if 0
typedef pair<long long, long long> pll;
class Solution {
public:
    long long pow(int a, int m, int mod) {
        long long ans = 1;
        long long contribute = a;
        while (m > 0) {
            if (m % 2 == 1) {
                ans = ans * contribute % mod;
                if (ans < 0) {
                    ans += mod;
                }
            }
            contribute = contribute * contribute % mod;
            if (contribute < 0) {
                contribute += mod;
            }
            m /= 2;
        }
        return ans;
    }

    int check(const vector<int>& arr, int m, int a1, int a2, int mod1, int mod2) {
        int n = arr.size();
        long long aL1 = pow(a1, m, mod1);
        long long aL2 = pow(a2, m, mod2);
        long long h1 = 0, h2 = 0;
        for (int i = 0; i < m; ++i) {
            h1 = (h1 * a1 % mod1 + arr[i]) % mod1;
            h2 = (h2 * a2 % mod2 + arr[i]) % mod2;
            if (h1 < 0) {
                h1 += mod1;
            }
            if (h2 < 0) {
                h2 += mod2;
            }
        }
        // �洢һ����������Ƿ���ֹ�
        set<pll> seen;
        seen.emplace(h1, h2);
        for (int start = 1; start <= n - m; ++start) {
            h1 = (h1 * a1 % mod1 - arr[start - 1] * aL1 % mod1 + arr[start + m - 1]) % mod1;
            h2 = (h2 * a2 % mod2 - arr[start - 1] * aL2 % mod2 + arr[start + m - 1]) % mod2;
            if (h1 < 0) {
                h1 += mod1;
            }
            if (h2 < 0) {
                h2 += mod2;
            }

            // ����ظ����򷵻��ظ��������
            if (seen.count(make_pair(h1, h2))) {
                return start;
            }
            seen.emplace(h1, h2);
        }
        // û���ظ����򷵻�-1
        return -1;
    }

    string longestDupSubstring(string s) {
        srand((unsigned)time(NULL));
        // ������������
        int a1 = random() % 75 + 26;
        int a2 = random() % 75 + 26;

        // ��������ģ
        int mod1 = random() % (INT_MAX - 1000000006) + 1000000006;
        int mod2 = random() % (INT_MAX - 1000000006) + 1000000006;
        int n = s.size();
        // �ȶ������ַ����б���
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = s[i] - 'a';
        }
        // ���ֲ��ҵķ�Χ��[1, n-1]
        int l = 1, r = n - 1;
        int length = 0, start = -1;
        while (l <= r) {
            int m = l + (r - l + 1) / 2;
            int idx = check(arr, m, a1, a2, mod1, mod2);
            if (idx != -1) {
                // ���ظ��Ӵ����ƶ���߽�
                l = m + 1;
                length = m;
                start = idx;
            }
            else {
                // ���ظ��Ӵ����ƶ��ұ߽�
                r = m - 1;
            }
        }
        return start != -1 ? s.substr(start, length) : "";
    }
};
#endif