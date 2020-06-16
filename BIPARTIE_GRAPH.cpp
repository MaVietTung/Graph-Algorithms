// BIPARTIE_GRAPH.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<vector>
#include<queue>
#define MAX_SIZE 100001
using namespace std;
vector<int> A[MAX_SIZE];
int d[MAX_SIZE];
int N,M,ans;
void input() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		d[i] = -1;
	}
	for (int i = 1; i <= M; i++) {
		int u, v;
		cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}
}
int BFS(int u) {
	queue<int> Q;
	Q.push(u);
	d[u] = 0;
	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		for (int i = 0; i < A[v].size(); i++) {
			int x = A[v][i];
			if (d[x] > -1) {
				if (d[v] % 2 == d[x] % 2) return 0;
			}
			else {
				d[x] = d[v] + 1;
				Q.push(x);
			}
		}
	}
	return 1;
}
void solve() {
	ans = 1;
	for (int i = 1; i <= N; i++) {
		if (d[i] == -1) {
			if (!BFS(i)) ans = 0; break;
		}
	}
	cout << ans;
}
int main() {
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
