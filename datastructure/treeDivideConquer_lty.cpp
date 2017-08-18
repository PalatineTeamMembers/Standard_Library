int root, sum, f[N], size[N];
bool vis[N];
void findRoot(int u, int fa) {
	f[u] = 0;   size[u] = 1;
	for (int i = head[u]; i; i = other[i]) {
		int v = edge[i];
		if (vis[v] || v == fa) continue;
		findRoot(v, u);
		size[u] += size[v];
		f[u] = max(f[u], size[v]);
	}
	f[u] = max(f[u], sum - size[u]);
	if (f[u] < f[root]) root = u;
}

void calc(int root) {}

void divideAndConquer(int u) {
	calc(u);		//deal with the link starting from the current root
	findRoot(u, 0);	//update the size
	vis[u] = 1;
	for (int i = head[u]; i; i = other[i]) {
		int v = edge[i];
		if (vis[v]) continue;
		root = 0;
		f[0] = sum = size[v];
		findRoot(v, 0);
		divideAndConquer(root);
	}
}

int main() {
	root = 0;
	f[0] = sum = n;
	findRoot(1, 0);
	divideAndConquer(root);
}
