int det(int a[][N], int n) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] %= mod;
    int ret = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            while (a[j][i]) {
                int t = a[i][i] / a[j][i];
                for (int k = i; k <= n; k++)
                    a[i][k] = (a[i][k] - a[j][k] * t) % mod;
                for (int k = i; k <= n; k++)
                    swap(a[i][k], a[j][k]);
                ret = -ret;
            }
        }
        if (a[i][i] == 0) return 0;
        ret = ret * a[i][i] % mod;
    }
    if(ret < 0)
        ret = -ret;
    return (ret + mod) % mod;
}


void Gause(int *a, int cnt){
	int k = 0, i;
	for (long long j = (1LL << 62); j; j >>= 1) {
		for (i = k + 1; i <= cnt; i++){
			if (a[i] & j) break;
		}
		if (i > cnt) continue;
		swap(a[i], a[++k]);
		for (i = 1; i <= cnt; i++)
			if ((a[i] & j) && i != k) {
				a[i] ^= a[k];
			}
	}
}
