/**
 * @author : donggun.chung
 * @date : 2020. 05. 05
 * @site : BOJ
 * @probInfo : 1261 알고스팟 
 * @time : 0ms
 * @memory : 1988KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

int M, N;
vector<vector<int> > board, dist;
vector<vector<bool> > visited;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct cmp {
    bool operator()(const pair<pair<int, int>, int> &p1, const pair<pair<int, int>, int> &p2) {
        return p1.second > p2.second;
    }
};

void solution();

int main()
{
    cin >> M >> N;
    
    board.assign(N, vector<int>(M, 0));
    visited.assign(N, vector<bool>(M, false));
    dist.assign(N, vector<int>(M, INT_MAX));
    
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            scanf("%1d", &board[row][col]);
        }
    }

    solution();

    return 0;
}

void solution() {
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int> >, cmp> q;

    dist[0][0] = 0;
    q.push(make_pair(make_pair(0, 0), dist[0][0]));

    while(!q.empty()) {
        pair<int, int> cur = q.top().first;
        q.pop();

        if(visited[cur.first][cur.second]) continue;

        for(int dir = 0; dir < 4; dir++) {
            int ny = cur.first + dy[dir];
            int nx = cur.second + dx[dir];

            if(ny < 0 || ny >= N || nx < 0 || nx >= M || visited[ny][nx]) continue;

            if(dist[ny][nx] > dist[cur.first][cur.second] + board[ny][nx]) {
                dist[ny][nx] = dist[cur.first][cur.second] + board[ny][nx];
                q.push(make_pair(make_pair(ny, nx), dist[ny][nx]));
            }
        }

        visited[cur.first][cur.second] = true;
    }

    cout << dist[N - 1][M - 1] << endl;
}