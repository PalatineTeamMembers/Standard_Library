#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int n, m, rt, init_rt;
struct node {
	int l, r, val, size;
	LL sum[N];
}tr[N];

int resNode[N], usedNode[N], resTop, usedTop, top;

int newNode(int val = 0) {
	int u;
	if (resTop) u = resNode[resTop--];
	else u = ++top;
	usedNode[++usedTop] = u;
	tr[u].l = tr[u].r = 0;
	tr[u].val = val;
	return u;
}

void update(int x) {
	int ls = tr[x].l, rs = tr[x].r;
	tr[x].sum = tr[ls].sum + tr[rs].sum + tr[x].val;
	tr[x].size = tr[ls].size + tr[rs].size + 1;
}

int _index, vis[N];
void dfs(int x) {
	if (!x) return;
	vis[x] = _index;
	dfs(tr[x].l);
	dfs(tr[x].r);
}

void rebuild() {
	++_index;
	dfs(rt);
	dfs(init_rt);
	int cnt = 0;
	for (int i = 1; i <= usedTop; ++i) {
		if (vis[usedNode[i]] == _index) {
			usedNode[++cnt] = usedNode[i];
		} else {
			resNode[++resTop] = usedNode[i];
		}
	}
	usedTop = cnt;
}

int data[M];
int build(int l, int r) {
	if (l > r) return 0;
	int mid = l + r >> 1;
	int x = newNode(data[mid]);
	tr[x].l = build(l, mid - 1);
	tr[x].r = build(mid + 1, r);
	update(x);
	return x;
}

int r() {
	static int s = 3023192386;
	return (s += ((s << 3) + 1)) & (~0u >> 1);
}

bool random(int x, int y) {
	return r() % (x + y) < x;
}

int newMerge(int a, int b) {
	if (!a && !b) return 0;
	int x = newNode();
	if (!a || !b) tr[x] = tr[a ^ b];
	else if (random(tr[a].size, tr[b].size)) {
		tr[x] = tr[a];
		tr[x].r = newMerge(tr[x].r, b);
		update(x);
	} else {
		tr[x] = tr[b];
		tr[x].l = newMereg(a, tr[x].l);
		update(x);
	}
	return x;
}

int extract(int x, int l, int r) {
	if (l > r) return 0;
	if (l == 1 && r == tr[x].size) {
		int u = newNode();
		tr[u] = tr[x];
		return u;
	}
	int ls = tr[x].l, rs = tr[x].r;
	int size_l = tr[ls].size;
	if (r <= size_l) return extract(ls, l, r);
	else if (l > size_l + 1) return extract(rs, l - size_l - 1, r - size_l - 1);
	else {
		int u = newNode(tr[x].val);
		tr[u].l = extract(ls, l, size_l);
		tr[u].r = extract(rs, 1, r - size_l - 1);
		update(u);
		return u;
	}
}
