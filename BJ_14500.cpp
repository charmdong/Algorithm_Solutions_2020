/**
 * @author : donggun.chung
 * @date : 2020. 04. 01
 * @site : BOJ
 * @probInfo : 14500 테트리미노
 * @time : 92ms
 * @memory : 2924KB
 */ 

#include <iostream>
#include <vector>

using namespace std;

int N, M, answer;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0 ,-1};
vector<vector<int> > board;
vector<vector<bool> > visited;

void dfs(int y, int x, int total, int cnt = 1);
void middle(int y, int x);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    board.assign(N, vector<int>(M, 0));
    visited.assign(N, vector<bool>(M, false));

    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            cin >> board[row][col];
        }
    }

    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            visited[row][col] = true;
            dfs(row, col, board[row][col]);
            middle(row, col);
            visited[row][col] = false;
        }
    }

    cout << answer << endl;

    return 0;
}

void dfs(int y, int x, int total, int cnt) {
    if(cnt == 4) {
        if(answer < total) answer = total;
        return;
    }

    for(int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if(ny > -1 && ny < N && nx > -1 && nx < M) {
            if(!visited[ny][nx]) {
                visited[ny][nx] = true;
                dfs(ny, nx, total + board[ny][nx], cnt + 1);
                visited[ny][nx] = false;
            }
        }
    }
}

void middle(int y, int x) {
    int total = 0;

    if(y >= 1 && x >= 1 && x < M - 1) {
        total = max(total, board[y][x - 1] + board[y][x] + board[y - 1][x] + board[y][x + 1]);
    }

    if(y >= 1 && y < N - 1 && x < M - 1) {
        total = max(total, board[y - 1][x] + board[y][x] + board[y][x + 1] + board[y + 1][x]);
    }

    if(y >= 0 && y < N - 1 && x >= 1 && x < M - 1) {
        total = max(total, board[y][x - 1] + board[y][x] + board[y + 1][x] + board[y][x + 1]);
    }

    if(y >= 1 && y < N - 1 && x >= 1) {
        total = max(total, board[y - 1][x] + board[y][x] + board[y][x - 1] + board[y + 1][x]);
    }

    answer = max(answer, total);
}