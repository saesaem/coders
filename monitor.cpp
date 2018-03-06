/*
20180305 23:01
재형이의 모니터

20180306 14:01
수정한 부분
1. solve() 함수에서 처음에 이동하지 않고 입력받은 불량 픽셀이 허용 가능 불량픽셀 이하인 경우가 있을 수 있으므로 검사를 시행한다.
2. 이동한 최소 거리를 계산할 때, 상하비교, 좌우비교해서 연산해야 함.

*/

#include <iostream>
#include <algorithm>
using namespace std;

#define SIZE 31 // 30
int map[SIZE][SIZE];
int ans;
int moveArr[4]; // 상 하 좌 우
int X;
int W, H;
int pix_cnt;
int minVal;

void problemIn() {
	cin >> H >> W >> X;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> map[i][j];
		}
	}
}

void init() {
	ans = 1000000000;
	for (int i = 0; i < 4; i++)
		moveArr[i] = 0;
	minVal = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			map[i][j] = 0;
		}
	}
}

void pix_check() {
	for (int i = moveArr[0]; i < H - moveArr[1]; i++) {
		for (int j = moveArr[2]; j < W - moveArr[3]; j++) {
			if (map[i][j] == 1) {
				pix_cnt++;
			}
		}
	}
	if (pix_cnt <= X) {
		minVal = min(moveArr[0], moveArr[1]) * 2 + max(moveArr[0], moveArr[1]) + min(moveArr[2], moveArr[3]) + max(moveArr[2], moveArr[3]);
		//minVal = moveArr[0] + moveArr[1] + moveArr[2] + moveArr[3];
		ans = min(ans, minVal);
	}
}

void copy_arr(int a[4], int b[4]) {
	for (int i = 0; i < 4; i++)
		b[i] = a[i];
}

void dfs(int depth, int preArr[4]) {

	int arr[4];
	copy_arr(preArr, arr);

	if (depth == 4) {
		if (arr[0] + arr[1] < H && arr[2] + arr[3] < W) { // 상하, 좌우의 합이 SIZE 보다 작으면,
			copy_arr(arr, moveArr);
			pix_cnt = 0;
			pix_check();
			pix_cnt = 0;
		}
		return;
	}

	if (depth <= 1) {
		for (int i = 0; i < H; i++) {
			arr[depth] = i;
			dfs(depth + 1, arr);
		}
	}
	else {
		for (int i = 0; i < W; i++) {
			arr[depth] = i;
			dfs(depth + 1, arr);
		}
	}
}

void solve() {

	//이동하지 않고, 처음에 검사해보기.
	pix_check();
	if (ans < 1000000000) return;
	dfs(0, moveArr);

}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ans = 1000000000;
		problemIn();
		solve();
		cout << "#testcase" << tc << endl << ans << endl;
		init();
	}
	return 0;
}