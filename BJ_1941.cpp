/**
 * @author : donggun.chung
 * @date : 2020. 05. 16
 * @site : BOJ
 * @probInfo : 1941 소문난 칠공주 
 * @time : 268ms
 * @memory : 1984KB
 */ 
#include <iostream>
#include <vector>
#include <queue>
#define LEN 5
using namespace std;

int answer;
char board[LEN][LEN];
vector<pair<int, int> > pos;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void dfs(int y = 0, int x = 0);
bool isValid();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    for(int row = 0; row < LEN; row++) {
        for(int col = 0; col < LEN; col++) {
            cin >> board[row][col];
        }
    }

    dfs();

    cout << answer << endl;

    return 0;
}

void dfs(int y, int x) {
    if(pos.size() == 7) {
        if(isValid()) answer++;
        return;
    }

    for(int row = y; row < LEN; row++) {
        if(row != y) x = 0;
        for(int col = x; col < LEN; col++) {
            pos.push_back(make_pair(row, col));
            if(col + 1 < LEN) {
                dfs(row, col + 1);
            } else {
                dfs(row + 1, 0);
            }
            pos.pop_back();
        }
    }
}

bool isValid() {
    vector<vector<int> > tmp(LEN, vector<int>(LEN, 0));
    vector<vector<bool> > visited(LEN, vector<bool>(LEN, false));
    queue<pair<int, int> > q;

    for(pair<int, int> p : pos) {
        tmp[p.first][p.second] = 1;
    }

    visited[pos[0].first][pos[0].second] = true;
    q.push(pos[0]);

    while(!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        for(int dir = 0; dir < 4; dir++) {
            int ny = now.first + dy[dir];
            int nx = now.second + dx[dir];

            if(ny > -1 && ny < LEN && nx > -1 && nx < LEN && !visited[ny][nx]) {
                if(tmp[ny][nx] == 1) {
                    visited[ny][nx] = true;
                    q.push(make_pair(ny, nx));
                }
            }
        }
    }

    for(pair<int, int> p : pos) {
        if(!visited[p.first][p.second]) return false;
    }

    int s = 0;
    for(pair<int, int> p : pos) {
        if(board[p.first][p.second] == 'S') s++;
    }

    return s >= 4;
}

/**
 * 1. 25개 중 7개 골라라.
 * 2. 그 좌표들에 대해 인접해 있는지 확인하고, 다솜파가 더 많은지 확인
 * 3. 개수파악
 */ 