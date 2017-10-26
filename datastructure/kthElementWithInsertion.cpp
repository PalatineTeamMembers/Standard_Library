#include <bits/stdc++.h>

//root: the root of segment tree
struct Splay{int l, r, v, root;} tr[N];
struct SegmentTree(int l, int r, int size;)seg[M];

int rec[M], recTop;
int newNode() {
	if (!recTop) return ++tot;
	int k = rec[recTop--];
	return k;
}

//clear the segment tree
void reclaim(int &x) {
	if (!x) return;
	rec[++recTop] = x;
	reclaim(seg[x].l);
	reclaim(seg[x].r);
	seg[x].size = 0;
	x = 0;
}

void updateSegment(int x) {
	seg[x].size = seg[seg[x].l].size + seg[seg[x].r].size;
}

void add(int &x, int l, int r, int pos, int ad) {
	if (!x) x = newNode();
	if (l == r) {
		seg[x].size += ad;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) add(seg[x].l, l, mid, pos, ad);
	else add(seg[x].r, mid + 1, r, pos, ad);
	updateSegment(x);
	if (!seg[x].size) reclaim(x);
}

int dfn[N], dfnTop;

#define LV
#define RV

void updateBalanced(int x, int l, int r) {
	for (int i = l; i <= r; ++i) {
		add(tr[x].root, LV, RV, tr[dfn[i]].v, 1);
	}
}

//build the balanced tree
//V is the upper_bound of the value
void build(int &x, int l, int r) {
	if (l > r) return;
	if (l == r) {
		x = dfn[l];
		add(tr[x].root, LV, RV, tr[x].v, 1);
		return;
	}
	int mid = l + r >> 1;
	x = dfn[mid];
	build(tr[x].l, l, mid - 1);
	build(tr[x].r, mid + 1, r);
	updateBalanced(x, l, r);
}

//change the value at pos to val
int modify(int x, int pos, int val) {
	add(tr[x].root, LV, RV, val, 1);
	int res, k = seg[tr[tr[x].l].root].size;
	if (pos == k + 1) {
		res = tr[x].v;
		tr[x].v = val;
	}
	else if (pos <= k) res = modify(tr[x].l, pos, val);
	else res = modify(tr[x].r, pos - k - 1, val);
	add(tr[x].root, LV, RV, res, -1);
	return res;
}

//clear the balanced tree
void erase(int &x) {
	if (!x) return;
	reclaim(tr[x].root);
	erase(tr[x].l);
	dfn[++dfnTop] = x;
	erase(tr[x].r);
	x = 0;
}

void rebuild(int &x) {
	erase(x);
	build(x, 1, dfnTop);
	dfnTop = 0;	
}

int n;
//insert a node on balanced tree
void insert(int &x, int pos, int val) {
	if (!x) {
		x = ++n;
		tr[x].v = val;
		add(tr[x].root, LV, RV, val, 1);
		return;
	}
	add(tr[x].root, LV, RV, val, 1);
	int mid = seg[tr[tr[x].l].root].size;
	if (pos <= mid) insert(tr[x].l, pos, val);
	else insert(tr[x].r, pos - mid - 1, val);
	int maxSonSize = max(seg[tr[tr[x].l].root].size, seg[tr[tr[x].r].root].size);
	if (seg[tr[x].root].size * alpha > maxSonSize) rebuild(x);
}

void query(int x, int l, int r) {
	int size_l = seg[tr[tr[x].l].root].size;
	int size_cur = seg[tr[x].root].size;
	if (l == 1 && rs == size_cur) {
		seg_q.push_back(tr[x].root);
		return;
	}
	if (l <= size_l + 1 && r >= size_l + 1) {
		nod_q.push_back(tr[x].v);
	}
	if (l <= size_l) query(tr[x].l, l, min(size_l, r));
	if (r > size_l + 1) query(tr[x].r, max(1, l - size_l - 1), r - size_l - 1);
}

int solveQuery(int x, int y, int k) {
	query(root, x, y);
	--k;
	int l = LV, r = RV, sum;
	int segSize = seg_q.size();
	int nodSize = nod_q.size();
	while (l < r) {
		int mid = l + r >> 1;
		sum = 0;
		for (int i = 0; i < segSize; ++i) {
			sum += seg[seg[seg_q[i]].l].size;
		}
		for (int i = 0; i < nodSize; ++i) {
			if (nod_q[i] >= l && nod_q[i] <= mid) ++sum;
		}
		if (k < sum) {
			for (int i = 0; i < segSize; ++i) {
				seg_q[i] = seg[seg_q[i]].l;
			}
			r = mid;
		} else {
			for (int i = 0; i < segSize; ++i) {
				seg_q[i] = seg[seg_q[i]].r;
				l = mid + 1;
				k -= sum;
			}
		}
	}
	nod_q.clear();
	seg_q.clear();
	return l;
}

void solve() {

	root = 0;
	for (int i = 1; i <= n; ++i) {
		tr[i].clear();
	}
	for (int i = 1; i <= tot; ++i) {
		seg[i].clear();
	}
	tot = 0;
	recTop = dfnTop = 0;

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &tr[i].v);
		dfn[i] = i;
	}
	
	build(root, 1, n);
	
	scanf("%d", &m);
	
	char opt[3];
	while (m--) {
		int x, y, k;
		scanf("%s", opt);
		scanf("%d%d", &x, &y);
		if (opt[0] == 'Q') {
			scanf("%d", &k);
			printf("%d\n", solveQuery(x, y, k));
		} else if (opt[0] == 'I') {
			insert(root, x - 1, y);
		} else {
			modify(root, x, y);
		}
	}
}
