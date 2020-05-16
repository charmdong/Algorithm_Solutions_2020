/**
 * @author : donggun.chung
 * @date : 2020. 05. 14
 * @site : BOJ
 * @probInfo : 14502 연구소 
 * @time : 48ms
 * @memory : 1988KB
 */ 
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, answer;
vector<vector<int> > board, copied;
vector<pair<int, int> > virus;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void dfs(int y, int x, int cnt = 0);
void bfs();
int getArea();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    board.assign(N, vector<int>(M, 0));

    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            cin >> board[row][col];
            if(board[row][col] == 2) virus.push_back(make_pair(row, col));
        }
    }

    int y, x;
    for(int row = 0; row < N; row++) {
        bool find = false;
        for(int col = 0; col < M; col++) {
            if(board[row][col] == 0) {
                y = row;
                x = col;
                find = true;
                break;
            }
        }
        if(find) break;
    }

    dfs(y, x);
    cout << answer << endl;

    return 0;
}

void dfs(int y, int x, int cnt) {
    if(cnt == 3) {
        bfs();
        int res = getArea();
        if(answer < res) answer = res;
        return;
    }

    for(int row = y; row < N; row++) {
        if(row != y) x = 0;
        for(int col = x; col < M; col++) {
            if(board[row][col] == 0) {
                board[row][col] = 1;
                dfs(row, col, cnt + 1);
                board[row][col] = 0;
            }
        }
    }
}

void bfs() {
    queue<pair<int, int> > q;
    
    copied = board;
    for(pair<int, int> v : virus) {
        q.push(make_pair(v.first, v.second));
    }

    while(!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        for(int dir = 0; dir < 4; dir++) {
            int ny = now.first + dy[dir];
            int nx = now.second + dx[dir];

            if(ny > -1 && ny < N && nx > -1 && nx < M && copied[ny][nx] == 0) {
                copied[ny][nx] = 2;
                q.push(make_pair(ny, nx));
            }
        }
    }
}

int getArea() {
    int total = 0;

    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            if(copied[row][col] == 0) {
                total++;
            }
        }
    }

    return total;
}