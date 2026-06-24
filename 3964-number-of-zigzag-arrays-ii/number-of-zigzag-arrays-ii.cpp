class Solution {
public:
    static const long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (!A[i][k]) continue;
                for (int j = 0; j < n; j++) {
                    if (!B[k][j]) continue;
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();
        Matrix res(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }

        return res;
    }

    vector<long long> multiplyMatVec(const Matrix& A,
                                     const vector<long long>& v) {
        int n = A.size();
        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;
            for (int j = 0; j < n; j++) {
                cur = (cur + A[i][j] * v[j]) % MOD;
            }
            res[i] = cur;
        }
        return res;
    }

    int zigZagArrays(long long n, int l, int r) {
        long long m = r - l + 1;

        if (n == 1) return m % MOD;
        if (n == 2) return (m * (m - 1)) % MOD;

        int sz = 2 * m;
        Matrix T(sz, vector<long long>(sz, 0));

        for (int x = 1; x <= m; x++) {
            for (int y = 1; y < x; y++) {
                T[x - 1][m + y - 1] = 1;
            }
        }

        for (int x = 1; x <= m; x++) {
            for (int y = x + 1; y <= m; y++) {
                T[m + x - 1][y - 1] = 1;
            }
        }

        vector<long long> init(sz, 0);

        for (int x = 1; x <= m; x++) {
            init[x - 1] = x - 1;
            init[m + x - 1] = m - x;
        }

        Matrix P = power(T, n - 2);
        vector<long long> finalState = multiplyMatVec(P, init);

        long long ans = 0;
        for (long long v : finalState) {
            ans = (ans + v) % MOD;
        }

        return (int)ans;
    }
};