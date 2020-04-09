/**
 * @author : donggun.chung
 * @date : 2020. 03. 02
 * @site : BOJ
 * @probInfo : 8382 방향 전환  
 * @time : 442ms
 * @memory : 12,728KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#define MAX 200
using namespace std;

int T;
pair<int, int> src, des;
bool visited[MAX + 1][MAX + 1];

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int bfs(int direction);
void initialize();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int test = 1; test <= T; test++) {
        cin >> src.first >> src.second >> des.first >> des.second;
       
        src.first += 100;
        src.second += 100;
        des.first += 100;
        des.second += 100;

        int answer = INT_MAX;

        for(int dir = 0; dir < 2; dir++) {
            int res = bfs(dir);

            if(answer > res) answer = res;

            initialize();
        }

        cout << "#" << test << " " << answer << endl;
    }

    return 0;
}

void initialize() {
    for(int row = 0; row <= MAX; row++) {
        for(int col = 0; col <= MAX; col++) {
            visited[row][col] = false;
        }
    }
}

int bfs(int direction) {
    queue<pair<pair<int, int>, pair<int, int> > > q;

    visited[src.first][src.second] = true;
    q.push(make_pair(make_pair(src.first, src.second), make_pair(direction, 0)));

    while(!q.empty()) {
        auto cur = q.front();
        int curY = cur.first.first;
        int curX = cur.first.second;
        int curDir = cur.second.first;
        int curCnt = cur.second.second;
        q.pop();

        if(curY == des.first && curX == des.second) {
            return curCnt;
        }

        int dIndex = (curDir == 1) ? 0 : 2;
        for(int dir = dIndex; dir < dIndex + 2; dir++) {
            int ny = curY + dy[dir];
            int nx = curX + dx[dir];
            int nd = (curDir == 1) ? 0 : 1;

            if(ny < 0 || nx < 0 || ny > MAX || nx > MAX) continue;

            if(!visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push(make_pair(make_pair(ny, nx), make_pair(nd, curCnt + 1)));
            }
        }
    }
}