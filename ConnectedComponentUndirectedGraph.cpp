// ConnectedComponentUndirectedGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int N, M;
int ans;
vector<vector<int>> A;
vector<int> color;
queue<int> Queue;
void input() {
	ans = 0;
	cin >> N >> M;
	for (int i = 0; i <= N; i++) {
		vector<int> M;
		A.push_back(M);
	}
	for (int i = 1; i <= M; i++) {
		int u, v;
		cin >> u >> v;
		A[u].push_back(v);
		A[v].push_back(u);
	}
}
void BFS(int u) {
	color[u] += 1;
	for (int i = 0; i < A[u].size(); i++) {
		if (color[A[u][i]] == 0) {
			color[A[u][i]] += 1;
			Queue.push(A[u][i]);
		}
	}
	if (!Queue.empty()) { int v = Queue.front(); Queue.pop(); BFS(v); }
}
void BFS() {
	for (int i = 0; i <= N; i++) {
		color.push_back(0);
	}
	for (int i = 1; i <= N; i++) {
		if (color[i] == 0) {
			BFS(i);
			ans++;
		}
	}
}
int main() {
	input();
	BFS();
	cout << ans;
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
