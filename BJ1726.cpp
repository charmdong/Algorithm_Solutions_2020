/**
 * @author : donggun.chung
 * @date : 2020. 03. 02
 * @site : BOJ
 * @probInfo : 1726 Robot
 * @time : 0ms
 * @memory : 2320KB
 */ 

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<vector<int> > board;
int visited[101][101][5];
pair<pair<int, int>, int> src, des;

int dy[5] = {0, 0, 0, 1, -1};
int dx[5] = {0, 1, -1, 0, 0};

int bfs();
bool isInBoard(int y, int x);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    board.assign(N + 1, vector<int>(M + 1, 0));

    for(int row = 1; row <= N; row++) {
        for(int col = 1; col <= M; col++) {
            cin >> board[row][col];
        }
    }
    
    cin >> src.first.first >> src.first.second >> src.second;
    cin >> des.first.first >> des.first.second >> des.second;

    cout << bfs() << endl;

    return 0;
}

int bfs() {
    if(src == des) {
        return 0;
    }

    queue<pair<pair<int, int>, int> > q;

    visited[src.first.first][src.first.second][src.second] = 1;
    q.push(src);

    while(!q.empty()) {
        pair<pair<int, int>, int> cur = q.front();
        int curRow = cur.first.first;
        int curCol = cur.first.second;
        int curDir = cur.second;
        q.pop();

        if(cur == des) {
            return visited[curRow][curCol][curDir] - 1;
        }
        
        // 칸 이동
        for(int dist = 1; dist < 4; dist++) {
            int ny = curRow + dy[curDir] * dist;
            int nx = curCol + dx[curDir] * dist;

            if(isInBoard(ny, nx)) {
                if(board[ny][nx] == 0) {
                    if(visited[ny][nx][curDir] == 0) {
                        visited[ny][nx][curDir] = visited[curRow][curCol][curDir] + 1;
                        q.push(make_pair(make_pair(ny, nx), curDir));
                    }
                } else {
                    break;
                }
            }
        }

        // 회전
        for(int dir = 1; dir < 5; dir++) {
            if(curDir != dir && visited[curRow][curCol][dir] == 0) {
                int cmdCnt = 1;
                if(curDir == 1 || curDir == 3) {
                    if(dir == curDir + 1) cmdCnt++;
                } else {
                    if(dir == curDir - 1) cmdCnt++;
                }

                visited[curRow][curCol][dir] = visited[curRow][curCol][curDir] + cmdCnt;
                q.push(make_pair(make_pair(curRow, curCol), dir));
            }
        }
    }
}

bool isInBoard(int y, int x) {
    return (y > 0 && y <= N && x > 0 && x <= M);
}