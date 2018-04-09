/*
0900
삼델로

검은색 하ㅑㄴ색알

1. 일자형 판 빈칸에 알을 놓음
2. 알을 놓을때 자신의 알과 알 사이 자신의 알색깔로 변화됨
3. 벽과 자신의 알사이도 변화
4. 돌은 빈 곳에서만 놓을 수 있으며, 
5. 사용자부터 시작 번갈아 가며 각 3알씩 놓을 수 있습니다.

예제를 보면서 어떻게 설계할지 봅니다.
1. 초기판이 주어짐
2. 사용자 검정돌을 14번쨰에 놓음
3. 컴퓨터는 가장자리에 흰돌을 놓음
4. 사용자는 검정돌을 4번쨰에 놓음
5. 컴퓨터는 가장 좌측의 자리에 흰돌을 놓음
6. 12번쨰 놓음
7. 10번째에 놓음

사용자가 가장 게임을 잘 했을 경우이며 이떄 검은색의 알의 개수는 9개입니다. 
각 3알씩 -> 뎁스가 3입니다. 

최대 검은색 알의 갯수를 구하기.

- 컴퓨터는 항상 왼쪽 끝 부터 빈칸을 찾아서 채웁니다.
- 빈칸은 반드시 6개 이상입니다. 

사용자는 빈칸중에 아무곳부터 놓을 수 있고, 중복불가
컴퓨터는 놓아지는 자리가 정해져 있습니다. 
그럼 사용자는 빈칸P3 의 순열입니다. 놓는 순서도 중요하니, 중복 x 순열

1. 사용자가 놓는 순열 함수

2. 돌의 색이 변하는 함수

3. 컴퓨터가 놓는 순열 

빈칸은 0 으로 두고, 사용자가 사용하는 검은색돌은 1, 컴퓨터의 흰돌은 2로 나타내도록 하겠습니다.


*/

#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define SIZE 31 // 31;
int map[SIZE];
int visit[SIZE];
int ans, N;



void problemIn() {
   cin >> N;
   for (int i = 0; i < N; i++) {
      cin >> map[i];
      if (map[i] != 0) {
         visit[i] = 1;
      }
   }
}

void init() {
   ans = 0;
   for (int i = 0; i < N; i++) {
      map[i] = 0;
      visit[i] = 0;
   }
}

void copy_arr(int a[SIZE], int b[SIZE]) {
   for (int i = 0; i < N; i++) {
      b[i] = a[i];
   }
}

void check(int arr[SIZE], int pos, int color) {
   
   int right_Pos, left_Pos;
   int prePos = pos;
   queue<int> que;
   int length;
   
   while (1) {
      right_Pos = pos + 1;
      if (arr[right_Pos] == ((color==1)?1:2)) { // 자기 자신을 만나는 경우
         break;
      }
      else if (right_Pos == N) { // 오른쪽 벽을 만나는 경우
         break;
      }
      else if (arr[right_Pos] == 0) { // 빈칸을 만나는 경우
         break;
      }
      else if (arr[right_Pos] == ((color==1)?2:1)) { // 하얀돌을 만나는 경우
         que.push(right_Pos);
         pos = right_Pos;
      }
   }

   /*
   이렇게 하면 빈칸을 만나는 경우가 될 수 도 있고, 그냥 벽에 만나는 경우 일 수도 있습니다.
   */
   if (!que.empty()) {
      length = que.size();
      if (arr[right_Pos] == 0 && right_Pos != N) { 
         for (int i = 0; i < length; i++) {
            que.pop();
         }
      }
      else {
         for (int i = 0; i < length; i++) {
            arr[que.front()] = (color == 1) ? 1 : 2;
            que.pop();
         }
      }
   }

   pos = prePos;
   while (1) {
      left_Pos =   pos - 1;
      if (arr[left_Pos] == ((color==1)?1:2)) { // 자기 자신을 만나는 경우
         break;
      }
      else if (left_Pos == -1) { // 왼쪽 벽을 만나는 경우
         break;
      }
      else if (arr[left_Pos] == 0) { // 빈칸을 만나는 경우
         break;
      }
      else if (arr[left_Pos] == ((color==1)?2:1)) { // 하얀돌을 만나는 경우
         que.push(left_Pos);
         pos = left_Pos;
      }
   }

   if (!que.empty()) {
      length = que.size();
      if (arr[left_Pos] == 0) {
         for (int i = 0; i < length; i++) {
            que.pop();
         }
      }
      else {
         for (int i = 0; i < length; i++) {
            arr[que.front()] = (color == 1) ? 1 : 2;
            que.pop();
         }
      }
   }
}
void dfs(int depth, int preMap[SIZE], int preVisit[SIZE]) {

   if (depth == 3) {
      int black_cnt = 0;
      for (int i = 0; i < N; i++) {
         if (preMap[i] == 1) {
            black_cnt++;
         }
      }
      ans = max(ans, black_cnt);
      return;
   }

   int curMap[SIZE], curVisit[SIZE]; // 변동 가능맵

   for (int i = 0; i < N; i++) { // 큰 for문은 하나만 돌리기
      copy_arr(preMap, curMap); // 다시 돌려놓기
      copy_arr(preVisit, curVisit);

      if (curVisit[i] == 0) {
         curVisit[i] = 1; // 놓음
         curMap[i] = 1; // 검은돌
         check(curMap, i, 1);

         for (int j = 0; j < N; j++) {
            if (curVisit[j] == 0) {
               curVisit[j] = 1; // 놓음
               curMap[j] = 2; // 흰돌
               check(curMap, j, 2);
               dfs(depth + 1, curMap, curVisit);
               break;
            }
         }
      }
   }
}


void solve() {
   dfs(0, map, visit);
}

int main() {
   int T;
   cin >> T;
   for (int tc = 1; tc <= T; tc++) {
      problemIn();
      solve();

      cout << "#" << tc << " " << ans << endl;
      init();
   }
   return 0;
}
