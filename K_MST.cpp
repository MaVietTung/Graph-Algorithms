// K_MST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#define MAX_N 100
#define MAX_M 1000
#define INF 1000000
using namespace std;
int N, M, K;
vector<int> A[MAX_N];
int b[MAX_M];
int e[MAX_M];
int w[MAX_M];
int X[MAX_N];
set<int> Ax[MAX_N];
int ans;
int W;
int visited[MAX_N];
int r[MAX_N];
int p[MAX_N];
long long rs;
void input() {
	cin >> N >> M >> K;
	for (int i = 1; i <= M; i++) {
		int u, v, wuv;
		cin >> u >> v >> wuv;
		A[u].push_back(v);
		A[v].push_back(u);
		b[i] = u;
		e[i] = v;
		w[i] = wuv;
	}
}
void swapEdge(int i,int j) {
	swap(w[i], w[j]);
	swap(b[i], b[j]);
	swap(e[i], e[j]);
}
int partition(int L, int R, int index) {
	int pivot = w[index];
	swapEdge(index, R);
	int storeIndex = L;
	for (int i = L; i <= R - 1; i++) {
		if (w[i] < pivot) {
			swapEdge(storeIndex, i);
			storeIndex++;
		}
	}
	swapEdge(storeIndex, R);
	return storeIndex;
}
void quickSort(int L,int R) {
	if (L < R) {
		int index = (L + R) / 2;
		index = partition(L, R, index);
		if (L < index) quickSort(L, index - 1);
		else if(index<R) quickSort(index + 1, R);
	}
}
void quickSort() {
	quickSort(1, M);
}
void DFS(int u) {
	visited[u] = 1;
	for (set<int>::iterator it = Ax[u].begin(); it != Ax[u].end(); it++) {
		int v = *it;
		if (!visited[v]) DFS(v);
	}
}
int checkConnected() {
	set<int> Vx;
	for (int i = 1; i <= K; i++) {
		Vx.insert(b[X[i]]);
		Vx.insert(e[X[i]]);
	}
	for (set<int>::iterator it = Vx.begin(); it != Vx.end(); it++) {
		int u = *it;
		visited[u] = 0;
	}
	int cnt = 0;
	for (set<int>::iterator it = Vx.begin(); it != Vx.end(); it++) {
		int u = *it;
		if (visited[u] == 0) {
			cnt++;
			DFS(u);
		}
	}
	return cnt == 1;
}
void solution() {
	if (checkConnected())
		if (W < ans) ans = W;
}
void makeSet(int i) {
	p[i] = i;
	r[i] = 0;
}
int findSet(int u) {
	if (u != p[u]) {
		p[u] = findSet(p[u]);
	}
	return p[u];
}
void link(int u, int v) {
	if (r[u] > r[v]) p[v] = u;
	else
	{
		p[u] = v;
		if (r[u] == r[v]) r[v] += 1;
	}
}
int check(int val,int k) {
	for (int i = 1; i <= N; i++) makeSet(i);
	for (int j = 1; j < k; j++) {
		int u = b[X[j]]; int v = e[X[j]];
		int ru = findSet(u); int rv = findSet(v);
		if (ru == rv) return 0;
		link(ru, rv);
	}
	if (findSet(b[val]) == findSet(e[val])) return 0;
	return 1;
}
void Try(int k) {
	for (int v = X[k - 1] + 1; v <= M; v++) {
		if (check(v, k)) {
			X[k] = v;
			W += w[v];
			Ax[b[v]].insert(e[v]); Ax[e[v]].insert(b[v]);
			if (k == K) {
				solution();
			}
			else
			{
				int g = W;
				for (int j = 1; j < K - k; j++) g += w[X[k] + j];
				if (g < ans) { 
					Try(k + 1);
				}
			}
			Ax[b[v]].erase(e[v]); Ax[e[v]].erase(b[v]);
			W -= w[v];
		}
	}
}
void solve() {
	quickSort();
	ans = INF;
	X[0] = 0;
	W = 0;
	Try(1);
	if (ans == INF) ans = -1;
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
