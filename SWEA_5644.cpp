/**
 * @author : donggun.chung
 * @date : 2020. 05. 17
 * @site : SWEA
 * @probInfo : 5644 배터리 충전
 * @time : 16ms
 * @memory : 12,708KB
 */ 
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int T, M, A;
pair<int, int> user1, user2;
vector<int> board[11][11];
vector<int> battery;
vector<int> route[2];

int dy[5] = {0, -1, 0, 1, 0};
int dx[5] = {0, 0, 1, 0, -1};

void bfs(int y, int x, int cover, int index);
int solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        user1 = make_pair(1, 1);
        user2 = make_pair(10, 10);

        cin >> M >> A;

        battery.assign(A + 1, 0);
        route[0].assign(M + 1, 0);
        route[1].assign(M + 1, 0);

        for(int user = 0; user < 2; user++) {
            for(int r = 1; r <= M; r++) {
                cin >> route[user][r];
            }
        }

        int x, y, cover;
        for(int index = 1; index <= A; index++) {
            cin >> x >> y;
            cin >> cover >> battery[index];
            bfs(y, x, cover, index);
        }

        cout << "#" << test << " " << solution() << endl;

        for(int row = 1; row <= 10; row++) {
            for(int col = 1; col <= 10; col++) {
                board[row][col].clear();
            }
        }
    }

    return 0;
}

int solution() {
    int answer = 0;
    
    for(int index = 0; index <= M; index++) {
        user1.first += dy[route[0][index]];
        user1.second += dx[route[0][index]];

        user2.first += dy[route[1][index]];
        user2.second += dx[route[1][index]];

        vector<int> &bc1 = board[user1.first][user1.second];
        vector<int> &bc2 = board[user2.first][user2.second];

        int maxVal = 0;

        if(bc1.size() == 0 || bc2.size() == 0) {
            for(int t : bc1) {
                if(maxVal < battery[t]) maxVal = battery[t];
            }
            answer += maxVal;
            maxVal = 0;
            for(int t: bc2) {
                if(maxVal < battery[t]) maxVal = battery[t];
            }
            answer += maxVal;
            continue;
        }

        for(int i : bc1) {
            int t1 = battery[i];
            for(int j : bc2) {
                int t2 = (i == j) ? 0 : battery[j];

                if(maxVal < t1 + t2) maxVal = t1 + t2;
            }
        }

        answer += maxVal;
    }

    return answer;
}

void bfs(int y, int x, int cover, int index) {
    queue<pair<pair<int, int>, int> > q;
    vector<vector<bool> > visited(11, vector<bool>(11, false));

    visited[y][x] = true;
    q.push(make_pair(make_pair(y, x), 0));

    while(!q.empty()) {
        pair<int, int> cur = q.front().first;
        int curDist = q.front().second;
        q.pop();

        board[cur.first][cur.second].push_back(index);

        for(int dir = 1; dir <= 4; dir++) {
            int ny = cur.first + dy[dir];
            int nx = cur.second + dx[dir];

            if(ny > 0 && ny < 11 && nx > 0 && nx < 11 && !visited[ny][nx]) {
                if(curDist + 1 <= cover) {
                    visited[ny][nx] = true;
                    q.push(make_pair(make_pair(ny, nx), curDist + 1));
                }
            }
        }
    }
}

/*
5
20 3
2 2 3 2 2 2 2 3 3 4 4 3 2 2 3 3 3 2 2 3
4 4 1 4 4 1 4 4 1 1 1 4 1 4 3 3 3 3 3 3
4 4 1 100
7 10 3 40
6 3 2 70
40 2
0 3 0 3 3 2 2 1 0 4 1 3 3 3 0 3 4 1 1 3 2 2 2 2 2 0 2 3 2 2 3 4 4 3 3 3 2 0 4 4 
0 1 0 3 4 0 4 0 0 1 1 1 0 1 4 4 4 4 4 3 3 3 0 1 0 4 3 2 1 4 4 3 2 3 2 2 0 4 2 1 
5 2 4 140
8 3 3 490
60 4
0 3 3 3 0 1 2 2 2 1 2 2 3 3 4 4 0 3 0 1 1 2 2 3 2 2 3 2 2 0 3 0 1 1 1 4 1 2 3 3 3 3 3 1 1 4 3 2 0 4 4 4 3 4 0 3 3 0 3 4 
1 1 4 1 1 1 1 1 1 4 4 1 2 2 3 2 4 0 0 0 4 3 3 4 3 3 0 1 0 4 3 0 4 3 2 3 2 1 2 2 3 4 0 2 2 1 0 0 1 3 3 1 4 4 3 0 1 1 1 1 
6 9 1 180
9 3 4 260
1 4 1 500
1 3 1 230
80 7
2 2 2 2 2 2 0 2 2 0 4 0 2 3 3 2 3 3 0 3 3 3 4 3 3 2 1 1 1 0 4 4 4 1 0 2 2 2 1 1 4 1 2 3 4 4 3 0 1 1 0 3 4 0 1 2 2 2 1 1 3 4 4 4 4 4 4 3 2 1 4 4 4 4 3 3 3 0 3 3 
4 4 1 1 2 1 2 3 3 3 4 4 4 4 4 1 1 1 1 1 1 1 1 0 3 3 2 0 4 0 1 3 3 3 2 2 1 0 3 2 3 4 1 0 1 2 2 3 2 0 4 0 3 4 1 1 0 0 3 2 0 0 4 3 3 4 0 4 4 4 4 0 3 0 1 1 4 4 3 0 
4 3 1 170
10 1 3 240
10 5 3 360
10 9 3 350
9 6 2 10
5 1 4 350
1 8 2 450
100 8
2 2 3 2 0 2 0 3 3 1 2 2 2 2 3 3 0 4 4 3 2 3 4 3 3 2 3 4 4 4 2 2 2 0 2 2 4 4 4 4 1 1 1 2 2 2 4 3 0 2 3 3 4 0 0 1 1 4 1 1 1 1 2 2 1 1 3 3 3 0 3 2 3 3 0 1 3 3 0 1 1 3 3 4 0 4 1 1 2 2 4 0 4 1 1 2 2 1 1 1 
4 4 4 0 4 1 1 4 1 1 1 1 3 2 1 2 1 1 4 4 1 0 2 3 4 4 4 4 4 0 1 0 2 2 2 0 2 2 2 2 2 2 3 0 0 1 4 3 3 2 0 0 4 4 4 0 2 0 4 1 1 2 2 0 4 4 0 0 2 0 2 3 3 0 2 3 0 3 4 0 4 3 4 4 3 4 1 1 2 2 2 0 0 1 0 4 1 1 1 4 
3 4 2 340
10 1 1 430
3 10 4 10
6 3 4 400
7 4 1 80
4 5 1 420
4 1 2 350
8 4 4 300
*/