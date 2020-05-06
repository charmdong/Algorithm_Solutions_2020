/**
 * @author : donggun.chung
 * @date : 2020. 05. 05
 * @site : BOJ
 * @probInfo : 14938 서강그라운드 
 * @time : 0ms
 * @memory : 1988KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 1501

using namespace std;

int n, m, r;
vector<vector<pair<int, int> > > graph;
vector<bool> visited;
vector<int> dist;
vector<int> items;

struct cmp {
    bool operator() (const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

int solution(int start);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> r;

    graph.assign(n + 1, vector<pair<int, int> >());
    items.assign(n + 1, 0);

    for(int index = 1; index <= n; index++) {
        cin >> items[index];
    }

    int src, des, len;
    for(int index = 0; index < r; index++) {
        cin >> src >> des >> len;

        graph[src].push_back(make_pair(des, len));
        graph[des].push_back(make_pair(src, len));
    }

    int answer = 0;
    for(int index = 1; index <= n; index++) {
        int res = solution(index);
        if(answer < res) answer = res;
    }

    cout << answer << endl;

    return 0;
}

int solution(int start) {
    int total = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> q;

    visited.assign(n + 1, false);
    dist.assign(n + 1, MAX);

    dist[start] = 0;
    q.push(make_pair(start, dist[start]));

    while(!q.empty()) {
        int cur = q.top().first;
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
    }

    for(int index = 1; index <= n; index++) {
        if(dist[index] <= m) {
            total += items[index];
        }
    }

    return total;
}