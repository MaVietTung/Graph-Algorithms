// IC_BUS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 5001
using namespace std;
int N, K;
int dist[MAX_N][MAX_N];
int color[MAX_N];
int d[MAX_N];
int c[MAX_N];
vector<int> A[MAX_N];
queue<pair<int, int>>Q;
int ans[MAX_N];
void input() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		int cc, ww;
		cin >> cc >> ww;
		c[i] = cc;
		d[i] = ww;		
	}
	for (int i = 1; i <= K; i++) {
		int u, v;
		cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}
}
void init() {
	for (int i = 1; i <= N; i++) {
		dist[i][i] = 0;
		color[i] = 0;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i != j) dist[i][j] = INT_MAX;
		}
	}
}
void initColor() {
	for (int i = 1; i <= N; i++) {
		color[i] = 0;
	}
}
void caculor_dist() {
	for (int i = 1; i <= N; i++) {
		color[i] = 1;
		Q.push(make_pair(i, 0));
		while (!Q.empty())
		{
			int u = Q.front().first;
			int ru = Q.front().second;
			Q.pop();
			if (ru + 1 <= d[i]) {
				for (int j = 0; j < A[u].size(); j++) {
					if (color[A[u][j]] == 0) {
						color[A[u][j]] = 1;
						dist[i][A[u][j]] = ru + 1;
						Q.push(make_pair(A[u][j], ru + 1));
					}
				}
			}
		}
		initColor();
	}
}
void find_shotest_path() {
	for (int i = 0; i <= N; i++) {
		ans[i] = INT_MAX;
		color[i] = 0;
	}
	ans[1] = 0;
	int step = N;
	while (step--)
	{
		int min_vertex = 0;
		for (int i = 1; i <= N; i++) {
			if (color[i] == 0 && ans[min_vertex] > ans[i]) {
				min_vertex = i;
			}
		}
		color[min_vertex] = 1;
		for (int i = 1; i <= N; i++) {
			if (dist[min_vertex][i] <= d[min_vertex]) {
				ans[i] = min(ans[i],ans[min_vertex] + c[min_vertex] );
			}
		}
		cout << ans[min_vertex] << endl;
	}
	cout << ans[N];
}
void solve() {
	init();
	caculor_dist();
	find_shotest_path();
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
