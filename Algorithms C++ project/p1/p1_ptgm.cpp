/******************************************************************************
 * IST: ASA 2021/22 - P1 - Pedro T. Monteiro                                  *
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

//------------------------------------------------------------------------------
void readSeq(vector<int> &seq) { // arg by reference
	int val;
	string line;
	getline(cin, line);
	istringstream iss(line);
	while (iss >> val)
		seq.push_back(val);
}

//------------------------------------------------------------------------------
// Init sz[i]=1, count[i]=1 for 0<=i<=n. since any single number is a valid seq
//------------------------------------------------------------------------------
// Recursion for size of LIS ending at i
// sz[i] = | max{ sz[j] + 1 | 0<=j<i and seq[i]>seq[j] }
//------------------------------------------------------------------------------
// Recursion to count number of LIS ending at i
// count[i] = | count[j]              , if seq[i]>seq[j] and sz[i] < sz[j] + 1
//            | count[i] + count[j]   , if seq[i]>seq[j] and sz[i] = sz[j] + 1
//------------------------------------------------------------------------------
// LIS -- O(len(seq)^2)
void computeLIS(vector<int> &seq) { // arg by reference
	vector<int> sz(seq.size(), 1); // sz[i]>=1 # at least number seq[i] itself
	vector<long> count(seq.size(), 1);
	int max_sz = 0;

	for (size_t i = 0; i < seq.size(); i++) {
		int sz_i     = 1;    // speedup: tmp vars to avoid unnecessary
		long count_i = 1; // writes on vector during for_j
		for (size_t j = 0; j < i; j++) {
			if (seq[j] < seq[i]) { // sequence increasing ?
				if (sz_i < sz[j] + 1) { // sequence of bigger sz ?
					sz_i = sz[j] + 1;
					count_i = count[j]; // is dependent of at least one prev pos j
				} else if (sz_i == sz[j] + 1) {
					count_i += count[j]; // sum paths from j leading to i
				}
			}
		}
		max_sz = max(max_sz, sz_i); // max LIS sz until pos=i
		sz[i] = sz_i;
		count[i] = count_i;
	}

	long counts = 0;
	for (size_t i = 0; i < seq.size(); i++) { // sum all LIS ending all i's
		if (sz[i] == max_sz)
			counts += count[i];
	}
	cout << max_sz << " " << counts << endl;
}

//------------------------------------------------------------------------------
// LICS -- O(len(seqX)^2 . len(seqY)^2)
void computeLCIS_N4(vector<int> &seqX, vector<int> &seqY) { // args by reference
	vector<vector<int>> lics(seqX.size(), vector<int>(seqY.size()));
	int max_sz = 0;	
	for (size_t i = 0; i < seqX.size(); i++) {
		for (size_t j = 0; j < seqY.size(); j++) {
			if (seqX[i] == seqY[j]) {
				int maxVal = 0; // check best LICS value on subMatrix
				for (size_t a = 0; a < i; a++) {
					for (size_t b = 0; b < j; b++) {
						if (seqX[a] == seqY[b] && seqY[b] < seqY[j]) {
							maxVal = max(maxVal, lics[a][b]);
						}
					}
				}
				lics[i][j] = maxVal + 1; // bestSubMatrix(i-1, j-1) + 1
				max_sz = max(max_sz, lics[i][j]);
			}
		}
	}
	cout << max_sz << endl;
}

//------------------------------------------------------------------------------
// LICS -- O(len(seqX) . len(seqY)^2)
void computeLCIS_N3(vector<int> &seqX, vector<int> &seqY) { // args by reference
	vector<int> lics(seqY.size(), 0);

	for (size_t i = 0; i < seqX.size(); i++) {
		for (size_t j = 0; j < seqY.size(); j++) {
			if (seqX[i] == seqY[j]) {
				int maxVal = 0; // check best LICS value on subVector
				for (size_t b = 0; b < j; b++) {
					if (seqY[b] < seqY[j]) {
						maxVal = max(maxVal, lics[b]);
					}
				}
				lics[j] = maxVal + 1; // bestSubMatrix(i-1, j-1) + 1
			}
		}
	}
	int max_sz = 0;
	for (size_t j = 0; j < seqY.size(); j++) {
		max_sz = max(max_sz, lics[j]);
	}
	cout << max_sz << endl;
}

//------------------------------------------------------------------------------
// LICS -- O(len(seqX) . len(seqY))
void computeLCIS_N2(vector<int> &seqX, vector<int> &seqY) { // args by reference
	vector<int> lics(seqY.size(), 0); // by default 0 in common between seqX & seqY

	for (size_t i = 0; i < seqX.size(); i++) {
		int max_sz_j = 0;
		for (size_t j = 0; j < seqY.size(); j++) {
			if (seqX[i] > seqY[j]) {
				max_sz_j = max(max_sz_j, lics[j]);
			} else if (seqX[i] == seqY[j]) {
				lics[j] = max(lics[j], max_sz_j + 1);
			}
		}
	}
	int max_sz = 0;
	for (size_t j = 0; j < seqY.size(); j++) {
		max_sz = max(max_sz, lics[j]);
	}
	cout << max_sz << endl;
}

//------------------------------------------------------------------------------
// [1 2 3 4 5] [3 5 6 7 1] -> [1 3 5] [3 5 1]
void onlyCommonElements(vector<int> &seqX, vector<int> &seqY) { // args by reference
	unordered_set<int> sX, sY; // to store unique elems from seqX & seqY
	vector<int> newX, newY;
	
	for (size_t i = 0; i < seqX.size(); i++) {
		sX.insert(seqX[i]);
	}
	for (size_t j = 0; j < seqY.size(); j++) {
		if (sX.count(seqY[j])) {
			sY.insert(seqY[j]);
			newY.push_back(seqY[j]);
		}
	}
	for (size_t i = 0; i < seqX.size(); i++) {
		if (sY.count(seqX[i])) {
			newX.push_back(seqX[i]);
		}
	}
	seqX = newX;
	seqY = newY;
}

//------------------------------------------------------------------------------
int main() {
	vector<int> seqX, seqY;
	int prob;
	cin >> prob;
	cin.get(); // consumes \n before reading sequence

	if (prob==1) {
		readSeq(seqX);
		computeLIS(seqX);
	} else if (prob==2) {
		readSeq(seqX);
		readSeq(seqY);
		onlyCommonElements(seqX, seqY); // OPTIMIZATION
		computeLCIS_N2(seqX, seqY);
		//computeLCIS_N3(seqX, seqY);
		//computeLCIS_N4(seqX, seqY);
	}
}
