/**
 * @author : donggun.chung
 * @date : 2020. 03. 02
 * @site : BOJ
 * @probInfo : 1937 욕심쟁이 판다
 * @time : 40ms
 * @memory : 4140KB
 */ 

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;
vector<vector<int> > board, dp;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int dfs(int row, int col);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    board.assign(n, vector<int>(n, 0));
    dp.assign(n, vector<int>(n, 0));

    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            cin >> board[row][col];
        }
    }

    int answer = 0;
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            int res = dfs(row, col);

            if(answer < res) answer = res;
        }
    }

    cout << answer << endl;

    return 0;
}

int dfs(int y, int x) {
    if(dp[y][x] > 0) return dp[y][x];

    dp[y][x] = 1;

    for(int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if(ny > -1 && ny < n && nx > -1 && nx < n) {
            if(board[ny][nx] > board[y][x]) {
                dp[y][x] = max(dp[y][x], dfs(ny, nx) + 1);
            }
        }
    }

    return dp[y][x];
}