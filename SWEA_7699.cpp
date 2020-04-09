/**
 * @author : donggun.chung
 * @date : 2020. 03. 02
 * @site : SWEA
 * @probInfo : 7699 수지의 수지 맞는 여행
 * @time : 22ms
 * @memory : 12,676KB
 */ 

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int T, R, C, answer;
char board[20][20];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void dfs(int check, int y = 0, int x = 0, int cnt = 1);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int test = 1; test <= T; test++) {
        cin >> R >> C;

        for(int row = 0; row < R; row++) {
            for(int col = 0; col < C; col++) {
                cin >> board[row][col];
            }
        }

        dfs((1 << (board[0][0] - 'A')));
        cout << "#" << test << " " << answer << "\n";
        answer = 0;
    }

    return 0;
}

void dfs(int check, int y, int x, int cnt) {
    if(answer < cnt) answer = cnt;

    for(int dir = 0; dir < 4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if(ny > -1 && ny < R && nx > -1 && nx < C) {
            int alpha = board[ny][nx] - 'A';
            if((check & (1 << alpha)) == 0) {
                dfs((check | (1 << alpha)), ny, nx, cnt + 1);
            }
        }
    }
}