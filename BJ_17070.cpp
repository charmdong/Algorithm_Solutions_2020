/**
 * @author : donggun.chung
 * @date : 2020. 03. 24
 * @site : BOJ
 * @probInfo : 17070 파이프 옮기기1
 * @time : 132ms
 * @memory : 1984KB
 */ 

#include <iostream>

using namespace std;

int answer;
int N;
int board[17][17];

int dy[3] = {0, 1, 1};
int dx[3] = {1, 0, 1};

void dfs(int y, int x, int dir);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for(int row = 1; row <= N; row++) {
        for(int col = 1; col <= N; col++) {
            cin >> board[row][col];
        }
    }

    dfs(1, 2, 0);

    cout << answer << endl;

    return 0;
}

void dfs(int y, int x, int curDir) {
    if(y == N && x == N) {
        answer++;
        return;
    }

    for(int dir = 0; dir < 3; dir++) {
        // 가로 -> 세로, 세로 -> 가로 인 경우
        if((curDir == 0 && dir == 1) || (curDir == 1 && dir == 0)) continue;

        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if(ny > N || nx > N || board[ny][nx] == 1) continue;
        if(dir == 2 && (board[y][x + 1] == 1 || board[y + 1][x] == 1)) continue;

        dfs(ny, nx, dir);
    }
}