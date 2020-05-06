/**
 * @author : donggun.chung
 * @date : 2020. 05. 06
 * @site : BOJ
 * @probInfo : 17472 다리 만들기2
 * @time : 0ms
 * @memory : 1988KB
 */ 

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cmp {
    bool operator() (const pair<pair<int, int>, int> &p1, const pair<pair<int, int>, int> &p2) {
        return p1.second > p2.second;
    }
};

int N, M, num = 1;
vector<vector<int> > board;
vector<int> parent;
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int> >, cmp> q;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void numbering();
void getDist();
int solution();
int findSet(int index);
bool unionSet(int src, int des);
bool isInBoard(int y, int x);

/** 
 * 1. 섬의 갯수를 구하면서 섬마다 넘버링
 * 각 섬에서 다른 섬으로 갈 수 있는 src, des, len을 구한다. (len >= 2)
 * 양방향 그래프
 * 최소 비용 신장 트리로 최소 값을 구한다.
 */

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
        }
    }

    cout << solution() << endl;

    return 0;
}

int solution() {
    int answer = 0;
    int edgeCnt = 0;
    bool flag = false;

    numbering();
    getDist();

    parent.assign(num, 0);
    for(int index = 1; index < num; index++) {
        parent[index] = index;
    }

    while(!q.empty()) {
        int a = q.top().first.first;
        int b = q.top().first.second;
        int len = q.top().second;
        q.pop();

        if(unionSet(a, b)) {
            answer += len;
            if(++edgeCnt == num - 2) {
                flag = true;
                break;
            }
        }
    }

    return (flag) ? answer : -1;
}

void numbering() {
    vector<vector<bool> > visited(N, vector<bool>(M, false));
    
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            if(visited[row][col] || board[row][col] == 0) continue;

            queue<pair<int, int> > q;
            q.push(make_pair(row, col));
            visited[row][col] = true;
            board[row][col] = num;

            while(!q.empty()) {
                pair<int, int> now = q.front();
                q.pop();

                for(int dir = 0; dir < 4; dir++) {
                    int ny = now.first + dy[dir];
                    int nx = now.second + dx[dir];

                    if(isInBoard(ny, nx) && !visited[ny][nx] && board[ny][nx] != 0) {
                        visited[ny][nx] = true;
                        board[ny][nx] = num;
                        q.push(make_pair(ny, nx));
                    }
                }
            }
            num++;
        }
    }
}

void getDist() {
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < M; col++) {
            if(board[row][col] == 0) continue;

            // 섬인 경우
            for(int dir = 0; dir < 4; dir++) {
                int len = 0;
                int ny = row;
                int nx = col;

                // 다리를 놓을 수 있는 경우
                while (true) {
                    ny += dy[dir];
                    nx += dx[dir]; 

                    if (!isInBoard(ny, nx) || board[ny][nx] == board[row][col]) {
                        break;
                    } else if(board[ny][nx] < 1) {
                        len++;
                    } else {
                        if(len >= 2) {
                            q.push(make_pair(make_pair(board[row][col], board[ny][nx]), len));
                        }
                        break;
                    }
                }
            }
        }
    }
}

int findSet(int index) {
    if(parent[index] == index) return index;
    return parent[index] = findSet(parent[index]);
}

bool unionSet(int src, int des) {
    int ps = findSet(src);
    int pd = findSet(des);

    if(ps != pd) {
        parent[ps] = pd;
        return true;
    }
    return false;
}

bool isInBoard(int y, int x) {
    return (y > -1 && y < N && x > -1 && x < M);
}