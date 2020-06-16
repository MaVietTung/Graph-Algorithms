// CountSpanningTree_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define MAX_N 101
#define MAX_M 1000
using namespace std;
int N, M;
int b[MAX_M];
int e[MAX_M];
int X[MAX_N];
long long ans;
int r[MAX_N];
int p[MAX_N];
long long rs;
void input() {
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> b[i] >> e[i];
	}
}
void solution() { 
	ans++; 
}
void makeSet(int i) {
	p[i] = i;
	r[i] = 0;
}
int findSet(int x) {
	if (x != p[x]) {
		p[x] = findSet(p[x]);
	}
	return p[x];
}
void link(int x,int y) {
	if (r[x] > r[y]) p[y] = x;
	else
	{
		p[x] = y;
		if (r[x] == r[y]) r[y] += 1;
	}
}
int checkNoCycle(int val,int k) {
	for (int i = 1; i <= N; i++) makeSet(i);
	for (int j = 1; j < k; j++) {
		int u = b[X[j]]; int v = e[X[j]];
		int ru = findSet(u); int rv = findSet(v);
		if (ru == rv) return 0;
		link(ru, rv);
	}
	if (findSet(b[val]) == findSet(e[val])) { return 0; }
	return 1;
}
void Try(int k) {
	for (int v = X[k - 1] + 1; v <= M; v++) {
		if (checkNoCycle(v, k)) {
			X[k] = v;
			if (k == N - 1) {
				solution();
			}
			else
			{
				Try(k + 1);
			}
		}
	}
}
void solve() {
	ans = 0;
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
