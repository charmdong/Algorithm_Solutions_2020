/**
 * @author : donggun.chung
 * @date : 2020. 05. 03
 * @site : BOJ
 * @probInfo : 4485 녹색 옷 입은 애가 젤다지?
 * @time : 4ms
 * @memory : 2180KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 987654321

using namespace std;

int N;
int board[125][125];
vector<vector<bool> > isMerged;
vector<vector<int> > dist;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int solution();
struct cmp {
    bool operator()(const pair<int, pair<int, int> > &p1, const pair<int, pair<int, int> > &p2) {
        return p1.first > p2.first;
    }
};

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    int test = 1;
    while(true) {
        cin >> N;
        if(N == 0) break;

        isMerged.assign(N, vector<bool>(N, false));
        dist.assign(N, vector<int>(N, MAX));
        for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
                cin >> board[row][col];
            }
        }

        cout << "Problem " << test++ << ": " << solution() << endl;
    }

    return 0;
}

int solution() {
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, cmp> q;
    
    dist[0][0] = board[0][0];
    q.push(make_pair(dist[0][0], make_pair(0, 0)));

    while(!q.empty()) {
        int curDist = q.top().first;
        pair<int, int> cur = q.top().second;
        q.pop();

        if(isMerged[cur.first][cur.second]) continue;

        for(int dir = 0; dir < 4; dir++) {
            int ny = cur.first + dy[dir];
            int nx = cur.second + dx[dir];

            if(ny > -1 && ny < N && nx > -1 && nx < N) {
                if(!isMerged[ny][nx] && dist[ny][nx] > dist[cur.first][cur.second] + board[ny][nx]) {
                    dist[ny][nx] = dist[cur.first][cur.second] + board[ny][nx];
                    q.push(make_pair(dist[ny][nx], make_pair(ny, nx)));
                }
            }
        }

        isMerged[cur.first][cur.second] = true;
    }

    return dist[N - 1][N - 1];
}