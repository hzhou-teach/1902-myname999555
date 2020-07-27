/*
* Jeffrey Chen
* Time: 50 minutes
* Test Cases: 12/12
* Difficulty: 7/10
* Finding the maximum was easy. Conceptually, finding the minimum also 
* wasn't too hard, but there was some edge cases that I had to check.
* At first I only had 11/12 test cases with the last one timing out, so 
* I pruned it a bit.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int n;

int main(int argc, char* argv[]) {
	const char* FIN = "herding.in";
	const char* FOUT = "herding.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	cin >> n;
	vector<int> cows(n);
	for (int i = 0; i < n; ++i) {
		cin >> cows[i];
	}
	sort(cows.begin(), cows.end());
	int maxMoves = cows[n - 1] - cows[0];
	maxMoves -= n;
	maxMoves -= (min(cows[1] - cows[0], cows[n - 1] - cows[n - 2]));
	maxMoves += 2;

	int maxIn = 0;
	int curIn = 1;
	int curRight = 0;
	for (int i = 0; i < n; ++i) {
		int l = cows[i];
		curIn -= 1;
		while (curRight < n && cows[curRight] <= l + n - 1) {
			++curRight;
			++curIn;
		}
		maxIn = max(maxIn, curIn);
	}
	if (maxIn == n - 1) {
		if (((cows[n-2] - cows[0] == n-2) || (cows[n-1] - cows[1] == n-2)) && (cows[n-1] - cows[0] != n-1 && cows[n-1] - cows[0] != n))
			maxIn = n - 2;
	}
	cout << n - maxIn << endl << maxMoves << endl;
	return 0;
}
