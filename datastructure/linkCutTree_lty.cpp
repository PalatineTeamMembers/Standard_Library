int n;
struct LinkCutTree {
	struct node {
		int ch[2], pnt, size;
		bool isRoot, rev;
	}tr[N];
	void init(int x) {
		tr[x].isRoot = 1;
		tr[x].rev = 0;
		tr[x].ch[0] = tr[x].ch[1] = tr[x].pnt = 0;
		tr[x].size = 1;
	}
	void reverse(int x) {
		if (!x) return;
		tr[x].rev ^= 1;
		swap(tr[x].ch[0], tr[x].ch[1]);
	}
	void pushDown(int x) {
		if (tr[x].rev) {
			reverse(tr[x].ch[0]);
			reverse(tr[x].ch[1]);
			tr[x].rev = 0;
		}
	}
	void pushUp(int x) {
		tr[x].size = tr[tr[x].ch[0]].size + tr[tr[x].ch[1]].size + 1;
	}
	void rotate(int x, bool b) {
		int y = tr[x].pnt;
		int z = tr[y].pnt;
		int son = tr[x].ch[b];
		if (son) tr[son].pnt = y;
		tr[y].pnt = x;
		tr[x].pnt = z;
		if (tr[y].isRoot) tr[x].isRoot = 1, tr[y].isRoot = 0;
		else tr[z].ch[tr[z].ch[1] == y] = x;
		tr[x].ch[b] = y;
		tr[y].ch[!b] = son;
		pushUp(y);
	}
	void path(int x) {
		if (!tr[x].isRoot) path(tr[x].pnt);
		pushDown(x);
	}
	void splay(int x) {
		path(x);
		while (!tr[x].isRoot) {
			int y = tr[x].pnt;
			if (tr[y].isRoot) rotate(x, tr[y].ch[0] == x);
			else {
				int z = tr[y].pnt;
				bool c = (tr[y].ch[0] == x), d = (tr[z].ch[0] == y);
				if (c == d) rotate(y, c), rotate(x, c);
				else rotate(x, c), rotate(x, d);
			}
		}
		pushUp(x);
	}
	int access(int x) {
		int y = 0;
		for (; x; x = tr[x].pnt) {
			splay(x);
			tr[tr[x].ch[1]].isRoot = 1;
			tr[x].ch[1] = y;
			tr[y].isRoot = 0;
			pushUp(y = x);
		}
		return y;
	}
	int find_root(int x) {
		while (tr[x].pnt) x = tr[x].pnt;
		return x;
	}
	bool query(int x, int y) {
		return find_root(x) == find_root(y);
	}
	void change_root(int x) {
		access(x);
		splay(x);
		reverse(x);
	}
	void cut(int x, int y) {
		change_root(x);
		access(x);
		splay(y);
		tr[y].pnt = 0;
	}
	void add(int x, int y) {
		change_root(y);
		tr[y].pnt = x;
	}
	int answer(int x) {
		change_root(n + 1);
		return tr[access(x)].size - 1;
	}
}lct;
int main() {
	for (int i = 1; i <= n + 1; ++i) lct.init(i);
}

