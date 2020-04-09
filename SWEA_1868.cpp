/**
 * @author : donggun.chung
 * @date : 2020. 03. 15
 * @site : SWEA
 * @probInfo : 1868 파핑파핑 지뢰찾기
 * @time : 230ms
 * @memory : 13,708KB
 */ 

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int T, N;
int noneCnt;
vector<vector<char> > board;
vector<vector<int> > mine;
vector<vector<bool> > visited;
vector<pair<int, int> > zero;

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int solution();
int bfs(int y, int x);
bool isInBoard(int y, int x);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N;

        board.assign(N, vector<char>(N, '\0'));
        visited.assign(N, vector<bool>(N, false));
        mine.assign(N, vector<int>(N, 0));
        zero.clear();
        noneCnt = 0;

        for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
                cin >> board[row][col];
                if(board[row][col] == '*') mine[row][col] = -1;
                else noneCnt++;
            }
        }

        // check mine count
        for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
                if(board[row][col] == '*') continue;

                for(int dir = 0; dir < 8; dir++) {
                    int ny = row + dy[dir];
                    int nx = col + dx[dir];

                    if(isInBoard(ny, nx) && board[ny][nx] == '*') {
                        mine[row][col]++;
                    }
                }
                if(mine[row][col] == 0) {
                    zero.push_back(make_pair(row, col));
                }
            }
        }

        cout << "#" << test << " " << solution() << endl;
    }

    return 0;
}

int solution() {
    int answer = 0;
    int visitedCnt = 0;
    
    for(pair<int, int> pos : zero) {
        if(!visited[pos.first][pos.second]) {
            visitedCnt += bfs(pos.first, pos.second);
            answer++;
        }
    }

    return answer + (noneCnt - visitedCnt);
}

int bfs(int y, int x){
    int visitCnt = 1;
    queue<pair<int, int> > q;

    visited[y][x] = true;
    q.push(make_pair(y, x));

    while(!q.empty()) {
        int curRow = q.front().first;
        int curCol = q.front().second;
        q.pop();
        
        for(int dir = 0; dir < 8; dir++) {
            int ny = curRow + dy[dir];
            int nx = curCol + dx[dir];

            if(isInBoard(ny, nx) && !visited[ny][nx]) {
                visitCnt++;
                visited[ny][nx] = true;
                // 주변 지뢰 갯수가 0인 얘들
                if(mine[ny][nx] == 0) {
                    q.push(make_pair(ny, nx));
                }
            }
        }
    }

    return visitCnt;
}

bool isInBoard(int y, int x) {
    return (y > -1 && y < N && x > -1 && x < N);
}