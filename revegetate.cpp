/*
* Jeffrey Chen
* Time: 90 minutes
* Test Cases: 12/12
* Difficulty: 8/10
* The main part of this problem was the Union-Find algorithm, and checking
* for odd cycles. The implementation was annoying but not too difficult.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef pair<int, int> pii;
int n, m;
int subs;
vector<vector<int>> graph(100003);
vector<vector<int>> difGraph(100003);
bool visit[100003] = { false };
int subGraph[100003];
bool visCol[100003] = { false };
int difCol[100003];

bool colour(int x, int c) {
	difCol[x] = c;
	visCol[x] = true;
	for (int i = 0; i < difGraph[x].size(); ++i) {
		int node = difGraph[x][i];
		if (!visCol[node]) {
			if (!colour(node, 1 - c)) {
				return false;
			}
			continue;
		}
		if (visCol[node] && difCol[node] == c) {
			return false;
		}
	}
	return true;
}

void dfs(int x, int ori) {
	visit[x] = true;
	subGraph[x] = ori;
	for (int i = 0; i < graph[x].size(); ++i) {
		int node = graph[x][i];
		if (!visit[node]) {
			dfs(node, ori);
		}
	}
}

int fillSub() {
	int subNum = 0;
	for (int i = 0; i < n; ++i) {
		if (!visit[i]) {
			dfs(i, subNum);
			++subNum;
		}
	}
	return subNum;
}

int main(int argc, char* argv[]) {
	const char* FIN = "revegetate.in";
	const char* FOUT = "revegetate.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	cin >> n >> m;
	vector<pii> dif;
	for (int i = 0; i < m; ++i) {
		char c;
		int a, b;
		cin >> c;
		cin >> a >> b;
		if (c == 'D') {
			dif.push_back(make_pair(a-1, b-1));
		}
		if (c == 'S') {
			graph[a - 1].push_back(b - 1);
			graph[b - 1].push_back(a - 1);
		}
	}
	subs = fillSub();
	set<pii> difSub;


	for (int i = 0; i < dif.size(); ++i) {
		int begin, end;
		begin = subGraph[dif[i].first];
		end = subGraph[dif[i].second];
		if (begin == end) {
			cout << 0 << endl;
			return 0;
		}
		if (begin > end) swap(begin, end);
		difSub.insert(make_pair(begin, end));
	}
	set<pii>::iterator itr;
	for (itr = difSub.begin(); itr != difSub.end(); ++itr) {
		pii p = *itr;
		difGraph[p.first].push_back(p.second);
		difGraph[p.second].push_back(p.first);
	}
	int ans = 0;
	for (int i = 0; i < subs; ++i) {
		if (!visCol[i]) {
			++ans;
			if (!colour(i, 0)) {
				cout << 0 << endl;
				return 0;
			}
		}
	}
	string str = "1";
	for (int i = 0; i < ans; ++i) {
		str += '0';
	}
	cout << str << endl;
	
	return 0;
}
