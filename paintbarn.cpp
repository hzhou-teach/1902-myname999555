/*
* Jeffrey Chen
* Time: 45 minutes
* Test Cases: 10/10
* Difficulty: 7/10
* The main part of this problem was writing the covered rectangles by using prefix sums.
* It wasn't too hard to implement after that.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int pref[1003][1003];

int main(int argc, char* argv[]) {
	const char* FIN = "paintbarn.in";
	const char* FOUT = "paintbarn.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	int n, k;
	cin >> n >> k;
	int maxX = 0;
	int maxY = 0;
	for (int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		maxX = max(maxX, x2);
		maxY = max(maxY, y2);
		++pref[x1 + 1][y1 + 1];
		--pref[x1 + 1][y2 + 1];
		--pref[x2 + 1][y1 + 1];
		++pref[x2 + 1][y2 + 1];
	}
	for (int i = 1; i < maxX+3; ++i) {
		for (int j = 1; j < maxY + 3; ++j) {
			pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + pref[i][j];
		}
	}
	int cnt = 0;
	for (int i = 1; i < maxX+3; ++i) {
		for (int j = 1; j < maxY+ 3; ++j) {
			if (pref[i][j] == k) ++cnt;
		}
	}
	cout << cnt << endl;

	return 0;
}
