/**
 * @author : donggun.chung
 * @date : 2020. 05. 05
 * @site : BOJ
 * @probInfo : 11779 최소비용 구하기 2 
 * @time : 24ms
 * @memory : 3180KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 100000001

using namespace std;

int n, m, sp, ep;
vector<vector<pair<int, int> > > graph;
vector<bool> visited;
vector<int> dist;
vector<int> parent;

struct cmp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

void solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    
    graph.assign(n + 1, vector<pair<int, int> >());
    visited.assign(n + 1, false);
    dist.assign(n + 1, MAX);
    parent.assign(n + 1, -1);

    int src, des, w;
    for(int index = 0; index < m; index++) {
        cin >> src >> des >> w;
        graph[src].push_back(make_pair(des, w));
    }

    cin >> sp >> ep; 

    solution();

    return 0;
}

void solution() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> q;
    int totalCnt = 0;
    int totalDist = 0;
    vector<int> trace;

    dist[sp] = 0;
    q.push(make_pair(sp, dist[sp]));

    while(!q.empty()) {
        int cur = q.top().first;
        q.pop();

        if(visited[cur]) continue;

        for(int index = 0; index < graph[cur].size(); index++) {
            int next = graph[cur][index].first;
            int nextDist = graph[cur][index].second;

            if(!visited[next] && dist[next] > dist[cur] + nextDist) {
                dist[next] = dist[cur] + nextDist;
                parent[next] = cur;
                q.push(make_pair(next, dist[next]));
            }
        }

        visited[cur] = true;
        totalCnt++;
        totalDist = dist[cur];
    }

    int now = ep;
    while(true) {
        if(now == sp) {
            trace.push_back(sp);
            break;
        }

        trace.push_back(now);
        now = parent[now];
    }

    cout << dist[ep] << endl;
    cout << trace.size() << endl;
    for(auto iter = trace.rbegin(); iter != trace.rend(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}