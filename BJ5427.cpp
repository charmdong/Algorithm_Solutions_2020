/**
 * @author : donggun.chung
 * @date : 2020. 03. 06
 * @site : BOJ 
 * @probInfo : 5427 불
 * @time : 56ms
 * @memory : 8124KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int T, w, h;
char board[1000][1000];
bool visited[1000][1000];
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

    cin >> T;

    for(int test = 1; test <= T; test++) {
        cin >> w >> h;

        for(int row = 0; row < h; row++) {
            for(int col = 0; col < w; col++) {
                cin >> board[row][col];
                
                if(board[row][col] == '@') {
                    start = make_pair(row, col);
                } else if(board[row][col] == '*') {
                    fire.push_back(make_pair(row,col));
                }
            }
        }

        int answer = bfs();
        if(answer == -1) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << answer << endl;
        }

        fire.clear();
        memset(visited, false, sizeof(visited));
    }

    return 0;
}

int bfs() {
    int res = 0;
    queue<pair<int, int> > q, extended;

    q.push(start);

    for(pair<int, int> f : fire) {
        extended.push(f);
    }

    while(!q.empty()) {
        int fireCnt = extended.size();
        
        for(int index = 0; index < fireCnt; index++) {
            int y = extended.front().first;
            int x = extended.front().second;
            extended.pop();

            for(int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if(ny > -1 && ny < h && nx > -1 && nx < w) {
                    if(board[ny][nx] == '.') {
                        board[ny][nx] = '*';
                        extended.push(make_pair(ny, nx));
                    }
                }
            }
        }

        int pathCnt = q.size();

        for(int index = 0; index < pathCnt; index++) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            if(y == 0 || y == h - 1 || x == 0 || x == w - 1) {
                return res + 1;
            }

            for(int dir = 0; dir < 4; dir++) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if(ny > -1 && ny < h && nx > -1 && nx < w) {
                    if(!visited[ny][nx] && board[ny][nx] == '.') {
                        visited[ny][nx] = true;
                        q.push(make_pair(ny, nx));
                    }
                }
            }
        }
        res++;
    }

    return -1;
}