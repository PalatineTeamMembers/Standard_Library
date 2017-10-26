#include <bits/stdc++.h>
struct Palindrome_Automation {
	struct node {
		int son[27];
		int len, cnt, pnt;
		void clear() {
			memset(son, 0, sizeof son);
			len = pnt = 0;
		}
	}a[N << 1];
	int tail, root, tot;
	Palindrome_Automation() {
		for (int i = 0; i <= tot; ++i) {
			a[i].clear();
		}
		tail = root = tot = 1;
	}
	void insert(int x) {
		int p, q;
		for (p = tail; str[x - 2 * a[p].len] != str[x]; p = a[p].pnt);
		if (a[p].son[str[x] - '`']) tail = a[p].son[str[x] - '`'];
		else {
			a[p].son[str[x] - '`'] = tail = ++tot;
			a[tail].len = a[p].len + 1;
			for (p = a[p].pnt; p; p = a[p].pnt) {
				if (str[x - 2 * a[p].len] == str[x]) {
					a[tail].pnt = a[p].son[str[x] - '`'];
					break;
				}
			}
			if (!p) a[tail].pnt = root;
		}
		a[tail].cnt++;
	}
}pam;
