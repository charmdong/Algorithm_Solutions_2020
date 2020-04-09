/**
 * @author : donggun.chung
 * @date : 2020. 03. 10
 * @site : SWEA
 * @probInfo : 5656 벽돌깨기
 * @time : 314ms
 * @memory : 12,680KB
 */ 

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

int T, N, W, H, answer;
vector<vector<int> > board(15, vector<int>(12, 0));
vector<int> brick;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void solution(int cnt, int brickCnt, vector<vector<int> >& board);
int getFirstBrick(int col, vector<vector<int> >& board);
int brokeWall(int y, int x, vector<vector<int> >& board);

int removeWall(int col);
void moveWall(vector<vector<int> >& board);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int test = 1; test <= T; test++) {
        cin >> N >> W >> H;

        int brickCnt = 0;
        for(int row = 0; row < H; row++) {
            for(int col = 0; col < W; col++) {
                cin >> board[row][col];
                if(board[row][col] != 0) brickCnt++;
            }
        }
        answer = brickCnt;
        solution(0, brickCnt, board);
        cout << "#" << test << " " << answer << endl;
    }

    return 0;
}

void solution(int cnt, int brickCnt, vector<vector<int> >& board) {
    if(cnt == N) {
        if(answer > brickCnt) {
            answer = brickCnt;
        }
        return;
    }

    for(int col = 0; col < W; col++) {
        vector<vector<int> > copied = board;

        // 해당 열에 대해서 구슬 던지기
        int r = getFirstBrick(col, copied);
        if(r == -1) continue;

        int brokenCnt = brokeWall(r, col, copied);
        if(brokenCnt >= brickCnt) {
            answer = 0;
            return;
        }

        moveWall(copied);
        solution(cnt + 1, brickCnt - brokenCnt, copied);
    }
}

int getFirstBrick(int col, vector<vector<int> >& board) {
    for(int row = 0; row < H; row++) {
        if(board[row][col] != 0) return row;
    }

    return -1;
}

int brokeWall(int r, int c, vector<vector<int> >& board) {
    int brokeCnt = 1;
    int scope = board[r][c];

    board[r][c] = 0;
    for(int dir = 0; dir < 4; dir++) {
        for(int dist = 1; dist < scope; dist++) {
            int ny = r + dy[dir] * dist;
            int nx = c + dx[dir] * dist;

            if(ny > -1 && ny < H && nx > -1 && nx < W) {
                if(board[ny][nx] != 0) {
                    brokeCnt += brokeWall(ny, nx, board);
                }
            }
        }
    }

    return brokeCnt;
}

void moveWall(vector<vector<int> >& board) {
    for (int c = 0; c < W; c++)
    {
        for (int r = H - 1, nr = H - 1; r >= 0; r--)
        {
            if (board[r][c] != 0)
            {
                int temp = board[r][c];
                board[r][c] = 0;
                board[nr--][c] = temp;
            }
        }
    }
}