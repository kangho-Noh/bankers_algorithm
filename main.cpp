#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define SHARED_RESOURCES 4
#define NUM_OF_PROCESS 5

vector<vector<int>> Max(NUM_OF_PROCESS);
vector<vector<int>> Alloc(NUM_OF_PROCESS);
vector<vector<int>> Need(NUM_OF_PROCESS);
vector<int> available;
vector<int> temp_available;
vector<int> safe_sequence;
bool found;
int chk[NUM_OF_PROCESS];

/*
* 1번문제 input

6 0 1 2 4 0 0 1
1 7 5 0 1 1 0 0
2 3 5 6 1 2 5 4
1 6 5 3 0 6 3 3
1 6 5 6 0 2 1 2
3 2 1 1

* 2번문제 input

6 0 1 2 4 0 0 1
1 7 5 0 1 1 0 0
2 3 5 6 1 2 5 4
1 6 5 3 0 6 3 3
1 6 5 6 1 4 1 2
3 2 1 1

*/
bool can_alloc(int pid) {
	bool ret = true;
	for (int i = 0; i < SHARED_RESOURCES; i++) {
		if (Need[pid][i] > available[i]) ret = false;
	}
	return ret;
}
void avail_plus_alloc(int pid) {
	for (int i = 0; i < SHARED_RESOURCES; i++) {
		available[i] += Alloc[pid][i];
	}
}

void dfs(int now) {
	chk[now]++;
	avail_plus_alloc(now);
	safe_sequence.push_back(now);
	if (safe_sequence.size() == NUM_OF_PROCESS) {
		for (int i = 0; i < 4; i++) {
			cout << available[i] << ' ';
		}
		cout << "available\n";
		found = true;
		return;
	}
	for (int i = 0; i < NUM_OF_PROCESS;i++) {
		if (!chk[i] && can_alloc(i)) {
			dfs(i);
		}
		if (found) return;
	}
	safe_sequence.pop_back();
}

void dfs_all() {
	for (int i = 0; i < NUM_OF_PROCESS; i++) {
		safe_sequence.clear();
		available = temp_available;
		memset(chk, 0, sizeof(chk));
		if (can_alloc(i)) {
			dfs(i);
		}
		if (found) return;
	}
	return;
}

int main() {
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	found = false;
	int a;
	for (int i = 0; i < NUM_OF_PROCESS; i++) {
		for (int j = 0; j < SHARED_RESOURCES; j++) {
			cin >> a;
			Max[i].push_back(a);
		}
		for (int j = 0; j < SHARED_RESOURCES; j++) {
			cin >> a;
			Alloc[i].push_back(a);
		}
		for (int j = 0; j < SHARED_RESOURCES; j++) {
			Need[i].push_back(Max[i][j] - Alloc[i][j]);
		}
	}
	for (int i = 0; i < SHARED_RESOURCES; i++) {
		cin >> a;
		temp_available.push_back(a);
	}
	//for (int i = 0; i < NUM_OF_PROCESS; i++) {
	//	for (int j = 0; j < SHARED_RESOURCES; j++) {
	//		cout << Max[i][j] << ' ';
	//	}
	//	cout << '\n';
	//}
	dfs_all();

	if (found) {
		cout << "Safe Sequence가 존재합니다.\n";
		for (int i = 0; i < NUM_OF_PROCESS; i++) {
			cout << "PID"<<safe_sequence[i] << ' ';
			if (i != NUM_OF_PROCESS - 1)cout << "-> ";
		}
		cout << '\n';
	}
	else {
		cout << "Safe Sequence가 존재하지 않습니다.\n";
	}
}