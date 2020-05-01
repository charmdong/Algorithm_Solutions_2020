// 등산로 조성
/**
 * @author : donggun.chung
 * @date : 2020. 05. 01
 * @site : SWEA
 * @probInfo : 1949 등산로 조성
 * @time : 22ms
 * @memory : 12,704KB
 */ 
#include <iostream>
#include <vector>

using namespace std;

int T, N, K, answer, highest;
vector<vector<int> > board;
vector<vector<bool> > visited;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void solution();
void dfs(int curY, int curX, int len = 1, bool isCut = false);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> K;
        board.assign(N, vector<int>(N, 0));
        visited.assign(N, vector<bool>(N, false));

        for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
                cin >> board[row][col];
                if(highest < board[row][col]) highest = board[row][col];
            }
        }

        solution();
        cout << "#" << test << " " << answer << endl;
        answer = 0;
        highest = 0;
    }

    return 0;
}

void solution() {
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            if(board[row][col] == highest) {
                dfs(row, col);
            }
        }
    }
}

void dfs(int curY, int curX, int len, bool isCut) {
    if(len > answer) {
        answer = len;
    }

    visited[curY][curX] = true;

    for(int dir = 0; dir < 4; dir++) {
        int ny = curY + dy[dir];
        int nx = curX + dx[dir];

        if(ny < 0 || ny >= N || nx < 0 || nx >= N || visited[ny][nx]) continue;

        if(board[ny][nx] < board[curY][curX]) {
            dfs(ny, nx, len + 1, isCut);
        } else if(board[ny][nx] >= board[curY][curX] && !isCut) {
            for(int h = 1; h <= K; h++) {
                isCut = true;
                board[ny][nx] -= h;

                if(board[ny][nx] < board[curY][curX]) {
                    dfs(ny, nx, len + 1, isCut);
                }

                board[ny][nx] += h;
                isCut = false;
            }
        }
    }

    visited[curY][curX] = false;
}