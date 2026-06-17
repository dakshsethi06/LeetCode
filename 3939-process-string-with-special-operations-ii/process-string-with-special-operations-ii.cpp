class Solution {
public:
    char processStr(string s, long long k) {
        const long long INF = 1000000000000000LL;

        int n = s.size();
        vector<long long> lenAfter(n);

        long long len = 0;

        for (int i = 0; i < n; i++) {
            char ch = s[i];

            if (ch >= 'a' && ch <= 'z') {
                len = min(INF, len + 1);
            } 
            else if (ch == '*') {
                if (len > 0) len--;
            } 
            else if (ch == '#') {
                len = min(INF, len * 2);
            } 
            else if (ch == '%') {
                // length unchanged
            }

            lenAfter[i] = len;
        }

        if (k >= len) return '.';

        long long idx = k;

        for (int i = n - 1; i >= 0; i--) {
            char ch = s[i];

            long long curLen = lenAfter[i];
            long long prevLen = (i == 0 ? 0 : lenAfter[i - 1]);

            if (ch >= 'a' && ch <= 'z') {
                if (idx == prevLen) return ch;
            }
            else if (ch == '*') {
                // indices remain unchanged
            }
            else if (ch == '#') {
                if (prevLen > 0) {
                    idx %= prevLen;
                }
            }
            else if (ch == '%') {
                idx = prevLen - 1 - idx;
            }
        }

        return '.';
    }
};