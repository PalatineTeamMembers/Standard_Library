struct Suffix_Automation {
	struct node {
		int son[26], pre, len;
	}a[N << 1];
	int tail, tot;
	void insert(int k) {
		int np = ++tot, nq, p, q;
		a[np].len = a[tail].len + 1;
		for (p = tail; p && !a[p].son[k]; p = a[p].pre) a[p].son[k] = np;
		if (!a[p].son[k]) {
			a[p].son[k] = np;
			a[np].pre = p;
		} else {
			if (a[q = a[p].son[k]].len == a[p].len + 1) a[np].pre = q;
			else {
				a[nq = ++tot] = a[q];
				a[nq].len = a[p].len + 1;
				a[np].pre = a[q].pre = nq;
				for (;a[p].son[k] == q; p = a[p].pre) a[p].son[k] = nq;
			}
		}
		tail = np;
	}
}sam;

struct Generalized_Suffix_Automation {
	struct node {
		int son[26], pre, len;
	}a[N << 1];
	int tail, tot;
	Suffix_Automation() { tail = 0; tot = 0; }
	void insert(int k) {
		int q, nq, p, np;
		if (a[tail].son[k]) {
			q = a[tail].son[k];
			if (a[q].len == a[tail].len + 1) tail = a[tail].son[k];
			else {
				a[nq = ++tot] = a[q];
				a[nq].len = a[tail].len + 1;
				a[q].pre = nq;
				for (p = tail; a[p].son[k] == q; p = a[p].pre) a[p].son[k] = nq;
				tail = nq;
			}
		} else {
			a[np = ++tot].len = a[tail].len + 1;
			for (p = tail; p && !a[p].son[k]; p = a[p].pre) a[p].son[k] = np;
			if (!a[p].son[k]) a[p].son[k] = np;
			else {
				if (a[nq = a[p].son[k]].len == a[p].len + 1) a[np].pre = q;
				else {
					a[nq = ++tot] = a[q];
					a[q].pre = a[np].pre = nq;
					a[nq].len = a[p].len + 1;
					for (; a[p].son[k] == q; p = a[p].pre) a[p].son[k] = nq;
				}
			}
			tail = np;
		}
	}
}gsam;
