class Solution:
    def assignEdgeWeights(self, edges, queries):
        MOD = 10**9 + 7

        n = len(edges) + 1
        LOG = n.bit_length()

        g = [[] for _ in range(n + 1)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        depth = [0] * (n + 1)
        up = [[0] * LOG for _ in range(n + 1)]

        stack = [(1, 0)]
        while stack:
            u, p = stack.pop()
            up[u][0] = p

            for j in range(1, LOG):
                up[u][j] = up[up[u][j - 1]][j - 1]

            for v in g[u]:
                if v != p:
                    depth[v] = depth[u] + 1
                    stack.append((v, u))

        def lca(a, b):
            if depth[a] < depth[b]:
                a, b = b, a

            diff = depth[a] - depth[b]

            for j in range(LOG):
                if diff & (1 << j):
                    a = up[a][j]

            if a == b:
                return a

            for j in range(LOG - 1, -1, -1):
                if up[a][j] != up[b][j]:
                    a = up[a][j]
                    b = up[b][j]

            return up[a][0]

        pow2 = [1] * n
        for i in range(1, n):
            pow2[i] = (pow2[i - 1] * 2) % MOD

        ans = []

        for u, v in queries:
            w = lca(u, v)
            dist = depth[u] + depth[v] - 2 * depth[w]

            if dist == 0:
                ans.append(0)
            else:
                ans.append(pow2[dist - 1])

        return ans