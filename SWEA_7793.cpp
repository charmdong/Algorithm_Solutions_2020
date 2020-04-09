/**
 * @author : donggun.chung
 * @date : 2020. 03. 08
 * @site : SWEA
 * @probInfo : 7793 오 나의 여신님
 * @time : 10ms
 * @memory : 12,700KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int T, N, M;
char board[50][50];
bool visited[50][50];
pair<int, int> src, des;
vector<pair<int, int> > devil;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int bfs();
bool isInBoard(int y, int x);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> M;

        for(int row = 0; row < N; row++) {
            for(int col = 0; col < M; col++) {
                cin >> board[row][col];

                if(board[row][col] == 'S') {
                    src = make_pair(row, col);
                } else if(board[row][col] == '*') {
                    devil.push_back(make_pair(row, col));
                } else if(board[row][col] == 'D') {
                    des = make_pair(row, col);
                } else {
                    continue;
                }
            }
        }

        cout << "#" << test << " ";

        int res = bfs();
        if(res == -1) cout << "GAME OVER\n";
        else cout << res << endl;
        
        memset(visited, false, sizeof(visited));
        devil.clear();
    }

    return 0;
}

int bfs() {
    int answer = 0;
    queue<pair<int, int> > q, extend;

    visited[src.first][src.second] = true;
    q.push(src);

    for(pair<int, int> d : devil) {
        extend.push(d);
    }

    while(!q.empty()) {
        int devilCnt = extend.size();
        for(int index = 0; index < devilCnt; index++) {
            int y = extend.front().first;
            int x = extend.front().second;
            extend.pop();

            for(int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if(isInBoard(ny, nx)) {
                    if(board[ny][nx] == '.' || board[ny][nx] == 'S') {
                        board[ny][nx] = '*';
                        extend.push(make_pair(ny, nx));
                    }
                }
            }
        }

        int pCnt = q.size();
        for(int index = 0; index < pCnt; index++) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            if(y == des.first && x == des.second) {
                return answer;
            }

            for(int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if(isInBoard(ny, nx) && !visited[ny][nx]) {
                    if(board[ny][nx] != 'X' && board[ny][nx] != '*') {
                        visited[ny][nx] = true;
                        q.push(make_pair(ny, nx));
                    }
                }
            }
        }

        answer++;
    }

    return -1;
}

bool isInBoard(int y, int x) {
    return (y > -1 && y < N && x > -1 && x < M);
}