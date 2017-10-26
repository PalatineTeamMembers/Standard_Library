int idx;
int dp[2][MOD];
int state[2][MOD], total[2], bit[M];
int n, m;
int data[N][M];
namespace Hash_System {
	int head[MOD], other[N], edge[N], tot;
	inline void update(int s, int num) {
		int u = s % MOD;
		for (int i = head[u]; i; i = other[i]) {
			if (state[idx][edge[i]] == s) {
				dp[idx][edge[i]] = max(dp[idx][edge[i]], num);
				return;
			}
		}
		
		state[idx][++total[idx]] = s;
		dp[idx][total[idx]] = num;
		++tot;
		other[tot] = head[u];
		head[u] = tot;
		edge[tot] = total[idx];
	}
	void _init() {
		memset(head, 0, sizeof head);
		tot = 0;
	}
} using namespace Hash_System;

inline int get_digit(int x, int j) {
	return x >> bit[j - 1] & 3;
}

//modify the jth bit of x from a to b
inline int modify(int x, int j, int a, int b) {
	return x ^ (a << bit[j - 1]) ^ (b << bit[j - 1])
}

int main() {
	int now, num, right, up, nxt;
	
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= m; ++i) bit[i] = i << 1;
	
	total[idx] = 1;
	state[idx][1] = 0;
	dp[idx][0] = 0;
	
	for (int i = 1; i <= n; ++i) {
		for (int k = 1; k <= total[idx]; ++k) state[idx][k] <<= 2;
		for (int j = 1; j <= m; ++j) {
			idx ^= 1;
			total[idx] = 0;
			_init();
			for (int k = 1; k <= total[idx ^ 1]; ++k) {
				now = state[idx ^ 1][k];
				num = dp[idx ^ 1][k];
				right = get_digit(now, j);
				up = get_digit(now, j + 1);
				if (right == 0 && up == 0) {
					if (i < n && j < m) update(modify(modify(now, j, 0, 1), j + 1, 0, 2), num + data[i][j]);
					update(now, num);
				} else if (right && !up) {
					if (i < n) update(now, num + data[i][j]);
					if (j < m) update(modify(modify(now, j, right, up), j + 1, up, right), num + data[i][j]);
				} else if (!right && up) {
					if (j < m) update(now, num + data[i][j]);
					if (i < n) update(modify(modify(now, j, right, up), j + 1, up, right), num + data[i][j]);
				} else if (right + up == 2) {
					nxt = modify(modify(now, j, right, 0), j + 1, up, 0);
					int b = 1;
					for (int t = j + 2; t <= m + 1; ++t) {
						int d = get_digit(now, t);
						if (d == 1) ++b;
						if (d == 2) --b;
						if (b == 0) {
							update(modify(nxt, t, 2, 1), num + data[i][j]);
							break;
						}
					}
				} else if (right + up == 4) {
					nxt = modify(modify(now, j, right, 0), j + 1, up, 0);
					int b = 1;
					for (int t = j - 1; t; --t) {
						int d = get_digit(now, t);
						if (d == 2) ++b;
						if (d == 1) --b;
						if (b == 0) {
							update(modify(nxt, t, 1, 2), num + data[i][j]);
							break;
						}
					}
				} else if (right == 1 && up == 2) {
					nxt = modify(modify(now, j, 1, 0), j + 1, 2, 0);
					if (nxt == 0) ans = max(ans, num + data[i][j]);
				} else if (right == 2 && up == 1) {
					nxt = modify(modify(now, j, 2, 0), j + 1, 1, 0);
					update(nxt, num + data[i][j]);
				}
			}
		}
	}
}
