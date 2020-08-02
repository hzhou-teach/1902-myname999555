/*
* Jeffrey Chen
* Time: 105 minutes
* Test Cases: 4/14
* Difficulty: 10/10
* I did a dfs, but I wasn't sure how to make it faster.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int n, q;
int enjoy[100009];
bool vis[100009];
vector<vector<int>> graph(100009);

int dfs(int x, int end, int amt) {
	if (x == end) {
		return (amt^enjoy[x]);
	}
	vis[x] = true;
	amt = amt ^ enjoy[x];
	for (int i = 0; i < graph[x].size(); ++i) {
		int node = graph[x][i];
		if (!vis[node]) {
			int tmp = dfs(node, end, amt);
			if (tmp != -1) {
				return tmp;
			}
		}
	}
	return -1;
}



int main(int argc, char* argv[]) {
	const char* FIN = "cowland.in";
	const char* FOUT = "cowland.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		cin >> enjoy[i];
	}
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}
	for (int i = 0; i < q; ++i) {
		int def, x, y;
		cin >> def >> x >> y;
		if (def == 1) {
			enjoy[x - 1] = y;
		}
		else {
			cout << dfs(x - 1, y - 1, 0) << endl;
			for (int i = 0; i < n; ++i) {
				vis[i] = false;
			}
		}
	}
	return 0;
}
