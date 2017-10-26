struct Heap{
	struct node{int l, r, d, v, pnt;}a[N];
	int top, sz;
	int s[N];
	void init() {
		top = 0;
		sz = 0;
		newnode(0, -INF);
		a[0].d = 0;
	}
	int merge(int x, int y){
		if (!x || !y) return x ^ y;
		if (a[x].v < a[y].v) swap(x, y);
		a[x].r = merge(a[x].r, y);
		a[a[x].r].pnt = x;
		if (a[a[x].r].d > a[a[x].l].d) swap(a[x].r, a[x].l);
		a[x].d = a[a[x].r].d + 1;
		return x;
	}
	inline int front(){return top;}
	void newnode(int x, int val){
		a[x].l = a[x].r = a[x].pnt = 0;
		a[x].v = val;
		a[x].d = 1;
	}
	inline void push(int x, int val){ 
		sz++;
		newnode(x, val);
		top = merge(top, x);
		a[top].pnt = 0;
	}
	inline void pop(){
		sz--;
		top = merge(a[top].l, a[top].r);
		a[top].pnt = 0;
	}
	inline int size(){ return sz; }
	inline void del(int x){
		sz--;
		int fa = a[x].pnt;
		int tmp = merge(a[x].l,a[x].r);
		a[tmp].pnt = fa;
		if(top == x){
			top = tmp;
			return;
		}
		if(a[fa].l == x) a[fa].l = tmp;
		else a[fa].r = tmp;
	}
	inline void change(int x, int val){
		del(x);
		push(x, val);
	}
}heap;
