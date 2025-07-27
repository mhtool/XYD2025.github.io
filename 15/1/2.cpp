#include <bits/stdc++.h>
using namespace std;
int main()
{
	// freopen("string.in", "r", stdin);
	// freopen("string.out", "w", stdout);
	using ull = unsigned long long;
	mt19937 rnd(0721);
	int n, m, k;
	cin >> n >> m >> k;
	ull tot = 0;
	vector<string> a(n + 1);

	vector<ull> pw(n + 1);
	vector<array<ull, 27>> sum(n + 1, array<ull, 27>{});
	const int mod = 1e9 + 7;
	pw[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		// pw[i] = pw[i - 1] * (m + 1);
		pw[i] = rnd();
		tot = tot + (m - k) * pw[i];
	}



	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		for (int j = 0; j < m; ++j)
			sum[j][a[i][j] - 'a' + 1] += pw[i];
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		ull now = 0;
		for (int j = 0; j < m; ++j)
			now += sum[j][a[i][j] - 'a' + 1];
		now -= pw[i] * m;
		now += pw[i] * (m - k);
		if (now == tot)
			cout << i << endl;
	}
	return 0;
}