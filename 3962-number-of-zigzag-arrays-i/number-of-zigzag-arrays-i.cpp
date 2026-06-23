class Solution {
public:
    static constexpr int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<int> up(m + 1), down(m + 1);
        vector<int> prefUp(m + 1), prefDown(m + 1);
        vector<int> newUp(m + 1), newDown(m + 1);

        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        for (int len = 3; len <= n; len++) {
            prefUp[0] = prefDown[0] = 0;

            for (int v = 1; v <= m; v++) {
                prefUp[v] = (prefUp[v - 1] + up[v]) % MOD;
                prefDown[v] = (prefDown[v - 1] + down[v]) % MOD;
            }

            int totalUp = prefUp[m];

            for (int v = 1; v <= m; v++) {
                newUp[v] = prefDown[v - 1];
                newDown[v] = (totalUp - prefUp[v] + MOD) % MOD;
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;

        if (n == 2) {
            for (int v = 1; v <= m; v++) {
                ans += up[v];
                ans += down[v];
            }
        } else {
            for (int v = 1; v <= m; v++) {
                ans += up[v];
                ans += down[v];
            }
        }

        return ans % MOD;
    }
};