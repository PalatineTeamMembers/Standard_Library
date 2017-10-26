#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#define ll long long
#define INF 0x3f3f3f3f
#define alpha 0.8
#define N 70010
using namespace std;
struct Splay{ int l, r, v, root; }tr[N];//root:线段树的根 
struct Segment_tree{ int l, r, size; }seg[10000005];//这玩意是不是要尽量开大啊= = 
int tmp, n, root, dfn[N], tot;//sz:线段树点个数；dfn:平衡树点； 
vector<int> seg_q, nod_q;//rec:线段树点；t:平衡树区间；p:平衡树中间点； 
int rec[10000005], recTop;
int newnode(){
	if (!recTop) return ++tot;
	return rec[recTop--];
}
void reclaim(int &x){	//清空线段树 
	if (!x) return;
	rec[++recTop] = x;
	reclaim(seg[x].l);
	reclaim(seg[x].r);
	seg[x].size = 0; x = 0;
}
void add(int &x, int l, int r, int pos, int ad){
	if (!x) x = newnode();
	if (l == r){
		seg[x].size += ad; return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) add(seg[x].l, l, mid, pos, ad);
	else add(seg[x].r, mid + 1, r, pos, ad);
	seg[x].size = seg[seg[x].l].size + seg[seg[x].r].size;
	if (!seg[x].size) reclaim(x);
}

#define LV 0
#define RV 70000
void build(int &x, int l, int r){ //建平衡树 
	if (l > r) return;
	if (l == r){
		x = dfn[l];
		add(tr[x].root, LV, RV, tr[x].v, 1);
		return;
	}
	int mid = l + r >> 1;
	x = dfn[mid];
	build(tr[x].l, l, mid - 1);
	build(tr[x].r, mid + 1, r);
	for (int i = l; i <= r; i++) add(tr[x].root, LV, RV, tr[dfn[i]].v, 1);
}
int modify(int x, int pos, int val){	//修改平衡树点 
	add(tr[x].root, LV, RV, val, 1);
	int res, k = seg[tr[tr[x].l].root].size;
	if (pos == k + 1){
		res = tr[x].v;
		tr[x].v = val;
	}
	else if (pos <= k) res = modify(tr[x].l,pos,val);
	else res = modify(tr[x].r,pos - k - 1, val);
	add(tr[x].root, LV, RV, res, -1);
	return res;
}

int dfnTop;
void del(int &x){	//删除平衡树点 
	if (!x) return;
	reclaim(tr[x].root);
	del(tr[x].l); 
	dfn[++dfnTop] = x;
	del(tr[x].r);
	x = 0;
}

void rebuild(int &x){	//重建平衡树 
	del(x);
	build(x, 1, dfnTop);
	dfnTop = 0;
}
void insert(int &x, int pos, int val){	//加入平衡树点 
	if (!x){
		x = ++n;
		tr[x].v = val;
		add(tr[x].root, LV, RV, val, 1);
		return;
	}
	add(tr[x].root, LV, RV, val, 1);
	int mid = seg[tr[tr[x].l].root].size;
	if (pos <= mid) insert(tr[x].l,pos, val);
	else insert(tr[x].r, pos - mid - 1, val);
	if (seg[tr[x].root].size * alpha > max(seg[tr[tr[x].l].root].size, seg[tr[tr[x].r].root].size)) {
		if (tmp){
			if (tmp == tr[x].l) rebuild(tr[x].l);
			else rebuild(tr[x].r);	
			tmp = 0;
		}
	}
	else tmp = x;
}
void query(int x, int l, int r){	//在平衡树上找区间 
	int L = seg[tr[tr[x].l].root].size, R = seg[tr[x].root].size;
	if (l == 1 && r == R){
		seg_q.push_back(tr[x].root);
		return;
	}
	if (l <= L + 1 && r >= L + 1) nod_q.push_back(tr[x].v);
	if (l <= L) query(tr[x].l, l, min(L, r));
	if (r > L + 1) query(tr[x].r, max(l - L - 1, 1),r - L - 1);
}
int solve_query(int x, int y, int k){
	query(root, x, y);
	k--;
	int l = LV, r = RV, sum, mid, s1 = seg_q.size(), s2 = nod_q.size();
	while (l < r) {
		mid = l + r >> 1;
		sum = 0;
		for (int i = 0;i < s1; i++) sum += seg[seg[seg_q[i]].l].size;
		for (int i = 0;i < s2; i++){
			if (nod_q[i] >= l && nod_q[i] <= mid) sum++;
		}
		if (k < sum) {
			for (int i = 0; i < s1; i++) seg_q[i] = seg[seg_q[i]].l;
			r = mid;
		}
		else {
			for (int i = 0; i < s1; i++) seg_q[i] = seg[seg_q[i]].r;
			l = mid + 1;
			k -= sum;
		}
	}
	seg_q.clear();
	nod_q.clear();
	return l;
}

void init() {
	for (int i = 1; i <= tot; ++i) seg[i].clear();
	for (int i = 1; i <= n; ++i) tr[i].clear();
	recTop = dfnTop = 0;
}

void solve() {
	int m, x, y, c;
	char str[2];
	n = read();
	for (int i = 1; i <= n; i++) {
		tr[i].v = read();
		dfn[i] = i;	
	}
	build(root, 1, n);
	m = read();
	while (m--) {
		scanf("%s", str);
		x = read();
		y = read();
		if (str[0]=='Q') {
			c = read();
			printf("%d\n", solve_query(x, y, c));
		}
		else if (str[0] == 'I') {
			tmp = 0;
			insert(root, x-1, y);
		}
		else if (str[0] == 'M') modify(root, x, y);
	}
}
