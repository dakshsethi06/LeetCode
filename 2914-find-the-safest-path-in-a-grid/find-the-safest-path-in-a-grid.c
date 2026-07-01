#define MAXN 405

typedef struct {
    int x, y;
} Pair;

typedef struct {
    int safe, x, y;
} Node;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void swap(Node *a, Node *b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

void push(Node heap[], int *size, Node val) {
    heap[++(*size)] = val;
    int i = *size;

    while (i > 1 && heap[i].safe > heap[i / 2].safe) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

Node pop(Node heap[], int *size) {
    Node ans = heap[1];
    heap[1] = heap[(*size)--];

    int i = 1;

    while (1) {
        int largest = i;
        int l = 2 * i;
        int r = 2 * i + 1;

        if (l <= *size && heap[l].safe > heap[largest].safe)
            largest = l;
        if (r <= *size && heap[r].safe > heap[largest].safe)
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return ans;
}

int minimum(int a, int b) {
    return a < b ? a : b;
}

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;

    int dist[MAXN][MAXN];
    int vis[MAXN][MAXN];

    Pair q[MAXN * MAXN];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = -1;
            vis[i][j] = 0;

            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q[rear++] = (Pair){i, j};
            }
        }
    }

    while (front < rear) {
        Pair cur = q[front++];

        for (int k = 0; k < 4; k++) {
            int nx = cur.x + dr[k];
            int ny = cur.y + dc[k];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                q[rear++] = (Pair){nx, ny};
            }
        }
    }

    Node heap[MAXN * MAXN];
    int size = 0;

    push(heap, &size, (Node){dist[0][0], 0, 0});

    while (size) {
        Node cur = pop(heap, &size);

        if (vis[cur.x][cur.y])
            continue;

        vis[cur.x][cur.y] = 1;

        if (cur.x == n - 1 && cur.y == n - 1)
            return cur.safe;

        for (int k = 0; k < 4; k++) {
            int nx = cur.x + dr[k];
            int ny = cur.y + dc[k];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny]) {
                push(heap, &size, (Node){
                    minimum(cur.safe, dist[nx][ny]),
                    nx,
                    ny
                });
            }
        }
    }

    return 0;
}