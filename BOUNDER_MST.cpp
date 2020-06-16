// BOUNDER_MST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 100
#define MAX_M 1000
#define INF 1000000
using namespace std;
int N, M, K;
int b[MAX_M];
int e[MAX_M];
int c[MAX_M];
int X[MAX_N];
int W;
int ans;
//data structure of disjoint_set
int r[MAX_N];
int p[MAX_N];
long long rs;
void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= M; i++) {
		int u, v, cuv;
		cin >> u >> v >> cuv;
		b[i] = u;
		e[i] = v;
		c[i] = cuv;
	}
}
void makeSet(int i) {
	r[i] = 0;
	p[i] = i;
}
int findSet(int i) {
	if (p[i] != i) p[i] = findSet(p[i]);
	return p[i];
}
void link(int x, int y) {
	if (r[x] > r[y]) p[y] = x;
	else
	{
		p[x] = y;
		if (r[x] == r[y]) r[y] += 1;
	}
}
int check(int val,int k) {
	for (int i = 1; i <= N; i++) { makeSet(i); }
	for (int j = 1; j < k; j++) {
		int u = b[X[j]]; 
		int v = e[X[j]];
		int ru = findSet(u); 
		int rv = findSet(v);
		if (ru == rv) return 0;
		link(ru, rv);
	}
	if (findSet(b[val]) == findSet(e[val])) return 0;
	return 1;
}
int selectMax(int d[], int N) {
	int max_d = -1;
	int u = -1;
	for (int v = 1; v <= N; v++) {
		if (max_d < d[v]) {
			max_d = d[v];
			u = v;
		}
	}
	return u;
}
int diameter() {
	vector<int> A[MAX_N];
	for (int i = 1; i <= N - 1; i++) {
		int u = b[X[i]];
		int v = e[X[i]];
		A[u].push_back(v);
		A[v].push_back(u);
	}
	queue<int> Q;
	int d[MAX_N] = { -1 };
	for (int i = 1; i <= N; i++) d[i] = -1;
	int s = 1;
	d[s] = 0;
	Q.push(s);
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		for (int i = 0; i < A[u].size(); i++) {
			int v = A[u][i];
			if (d[v] < 0) {
				d[v] = d[u] + 1;
				Q.push(v);
			}
		}
	}
	int x = selectMax(d, N);
	for (int i = 1; i <= N; i++) d[i] = -1;
	while (!Q.empty())
	{
		Q.pop();
	}
	d[x] = 0;
	Q.push(x);
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		for (int i = 0; i < A[u].size(); i++) {
			int v = A[u][i];
			if (d[v] < 0) {
				d[v] = d[u] + 1;
				Q.push(v);
			}
		}
	}
	int y = selectMax(d, N);
	return d[y];
}
void solution() {
	int dia = diameter();
	if (dia < K) {
		if (W < ans) ans = W;
	}
}
void Try(int k) {
	for (int v = X[k - 1] + 1; v <= M; v++) {
		int ok = check(v, k);
		if (ok) {
			X[k] = v;
			W += c[v];
			if (k == N - 1) { 
				solution(); 
			}
			else
			{
				Try(k + 1);
			}
			W -= c[v];
		}
	}
}
void solve() {
	ans = INF;
	X[0] = 0;
	Try(1);
	cout << ans;
}
int main()
{
	input();
	solve();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
