/**
 * @author : donggun.chung
 * @date : 2020. 03. 06
 * @site : BOJ
 * @probInfo : 4179 불
 * @time : 36ms
 * @memory : 4068KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000
using namespace std;

int R, C;
char board[MAX][MAX];
bool visited[MAX][MAX];
pair<int, int> start;
vector<pair<int, int> > fire;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int bfs();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> R >> C;

    for(int row = 0; row < R; row++) {
        for(int col = 0; col < C; col++) {
            cin >> board[row][col];

            if(board[row][col] == 'J') {
                start = make_pair(row, col);
            } else if(board[row][col] == 'F') {
                fire.push_back(make_pair(row, col));
            }
        }
    }

    int res = bfs();
    if(res == -1) cout << "IMPOSSIBLE\n";
    else cout << res << endl;

    return 0;
}

int bfs() {
    int answer = 0;
    queue<pair<int, int> > q, nextFire;

    visited[start.first][start.second] = true;
    q.push(start);

    for(pair<int, int> f : fire) {
        nextFire.push(f);
    }

    while(!q.empty()) {
        int fireCnt = nextFire.size();
        for(int index = 0; index < fireCnt; index++) {
            int y = nextFire.front().first;
            int x = nextFire.front().second;
            nextFire.pop();
            
            for(int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if(ny > -1 && ny < R && nx > -1 && nx < C) {
                    if(board[ny][nx] == '.' || board[ny][nx] == 'J') {
                        board[ny][nx] = 'F';
                        nextFire.push(make_pair(ny, nx));
                    }
                }
            }
        }

        int pathCnt = q.size();
        for(int index = 0; index < pathCnt; index++) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            if(y == 0 || y == R - 1 || x == 0 || x == C - 1) {
                return answer + 1;
            }

            for(int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if(ny > -1 && ny < R && nx > -1 && nx < C) {
                    if(board[ny][nx] == '.' && !visited[ny][nx]) {
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