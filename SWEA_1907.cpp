/**
 * @author : donggun.chung
 * @date : 2020. 03. 03
 * @site : SWEA
 * @probInfo : 1907 모래성 쌓기
 * @time : 858ms
 * @memory : 17,568KB
 */ 

#include <iostream>
#include <queue>
#define MAX 1000
using namespace std;

int T, H, W;
char board[MAX][MAX];
int cnt[MAX][MAX];

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int bfs();
void getSandCnt();
void init();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int test = 1; test <= T; test++) {
        cin >> H >> W;

        for(int row = 0; row < H; row++) {
            for(int col = 0; col < W; col++) {
                cin >> board[row][col];
            }
        }
        getSandCnt();
        cout << "#" << test << " " << bfs() << endl;
        init();
    }

    return 0;
}

int bfs() {
    int answer = 0;
    queue<pair<pair<int, int>, int> > q;

    for(int row = 1; row < H - 1; row++) {
        for(int col = 1; col < W - 1; col++) {
            if(board[row][col] == '.') continue;
            if(board[row][col] - '0' <= cnt[row][col]) {
                board[row][col] = '.';
                q.push(make_pair(make_pair(row, col), 1));
            }
        }
    }

    while(!q.empty()) {
        pair<pair<int, int>, int> cur = q.front();
        int curY = cur.first.first;
        int curX = cur.first.second;
        int curCnt = cur.second;
        q.pop();

        for(int dir = 0; dir < 8; dir++) {
            int ny = curY + dy[dir];
            int nx = curX + dx[dir];

            // 모래가 없는 칸인 경우
            if(board[ny][nx] == '.') continue;
            
            // 인접 모래성의 cnt증가
            cnt[ny][nx]++;
            if(board[ny][nx] - '0' <= cnt[ny][nx]) {
                board[ny][nx] = '.';
                q.push(make_pair(make_pair(ny, nx), curCnt + 1));
            }
        }

        answer = curCnt;
    }

    return answer;
}

void getSandCnt() {
    for(int row = 1; row < H - 1; row++) {
        for(int col = 1; col < W - 1; col++) {
            if(board[row][col] == '.') continue;

            for(int dir = 0; dir < 8; dir++) {
                int ny = row + dy[dir];
                int nx = col + dx[dir];

                if(board[ny][nx] == '.') cnt[row][col]++;
            }
        }
    }
}

void init() {
    for(int row = 0; row < H; row++) {
        for(int col = 0; col < W; col++) {
            cnt[row][col] = 0;
        }
    }
}