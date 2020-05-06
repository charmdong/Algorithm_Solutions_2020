/**
 * @author : donggun.chung
 * @date : 2020. 05. 05
 * @site : BOJ
 * @probInfo : 10282 해킹 
 * @time : 128ms
 * @memory : 5744KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 10000001

using namespace std;

struct cmp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

int T, n, d, start;
vector<vector<pair<int, int> > > graph;
vector<bool> visited;
vector<int> dist;

void solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> n >> d >> start;

        graph.assign(n + 1, vector<pair<int, int> >());
        visited.assign(n + 1, false);
        dist.assign(n + 1, MAX);

        int a, b, s;
        for(int index = 0; index < d; index++) {
            cin >> a >> b >> s;

            graph[b].push_back(make_pair(a, s));
        }

        solution();
    }

    return 0;
}

void solution() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> q;
    int totalCnt = 0;
    int totalDist = 0;

    dist[start] = 0;
    q.push(make_pair(start, dist[start]));

    while(!q.empty()) {
        int cur = q.top().first;
        int curDist = q.top().second;
        q.pop();

        if(visited[cur]) continue;

        for(int index = 0; index < graph[cur].size(); index++) {
            int next = graph[cur][index].first;
            int nextDist = graph[cur][index].second;

            if(!visited[next] && dist[next] > dist[cur] + nextDist) {
                dist[next] = dist[cur] + nextDist;
                q.push(make_pair(next, dist[next]));
            }
        }

        visited[cur] = true;
        totalCnt++;
        totalDist = curDist;
    }

    cout << totalCnt << " " << totalDist << endl;
}