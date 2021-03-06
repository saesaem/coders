/*
20180306
20:30 - 21:40
*/

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
#define SIZE 11 // 11
int map[SIZE][SIZE];
int visit[SIZE][SIZE];


int m, n;
int ans, dir;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
int c_x, c_y;
int pre_cnt;

struct points {
	int x, y;
};
queue<points> que;

void problemIn() {
	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				c_x = i;
				c_y = j;
			}
			if (map[i][j] == 1) {
				pre_cnt++;
			}
		}
	}
}

void init() {
	ans = pre_cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] = 0;
			visit[i][j] = 0;
		}
	}
}

void dfs(int x, int y, int d, int p_cnt) {

	while (1) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx >= 0 && ny >= 0 && nx < n && ny < m && visit[nx][ny] == 0 ) {
			if (map[nx][ny] == 0) { // 0? ?? ??? ?? d? ??? ??
				x = nx;
				y = ny;
			}
			else if (map[nx][ny] == 1) {
				for (int i = 0; i < 4; i++) {  // 1? ??? ?? ???.
					visit[nx][ny] = 1;
					dfs(nx, ny, i, p_cnt - 1);
				}
				visit[nx][ny] = 0; // ??? ??? ???.
				x = nx;
				y = ny;
			}
			else if (map[nx][ny] == 2) { // ??? ?? ????,
				if (p_cnt == 0) { // ??? 0? ??,
					ans++; // ?? ?? ??.
					return;
				}
				else {
					x = nx;
					y = ny;
				}
			}
		}
		else {
			break;
		}
	}
}

void solve() {
	for (int i = 0; i < 4; i++) {
		dfs(c_x, c_y, i, pre_cnt);
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		problemIn();
		solve();
		cout << ans << endl;
		init();
	}
	return 0;
}
