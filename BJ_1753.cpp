/**
 * @author : donggun.chung
 * @date : 2020. 04. 14
 * @site : BOJ
 * @probInfo : 1753 최단경로 
 * @time : 860ms
 * @memory : 9076KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 987654321
using namespace std;

int V, E;
int start;
vector<vector<pair<int, int> > > edges;
vector<int> dist;
vector<bool> visited;

struct cmp {
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        return p1.second > p2.second;
    }
};

void solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;
    cin >> start;

    edges.assign(V + 1, vector<pair<int, int> >());

    int src, des, weight;
    for(int index = 0; index < E; index++) {
        cin >> src >> des >> weight;

        edges[src].push_back(make_pair(des, weight));
    }

    solution();

    return 0;
}

void solution() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> pq;
    
    dist.assign(V + 1, MAX);
    visited.assign(V + 1, false);
    dist[start] = 0;
    // 우선순위 큐에는 간선 정보를 넣는 것이 아니라, 정점과 해당 정점까지의 거리를 넣는다!
    pq.push(make_pair(start, dist[start]));

    while(!pq.empty()) {
        int current = pq.top().first;
        pq.pop();

        if(visited[current]) continue;

        visited[current] = true;

        // 현재 정점에서 갈 수 있는 정점에 대하여
        for(int index = 0; index < edges[current].size(); index++) {
            // 다음 정점으로 갈 수 있는 간선 정보 (정점, 가중치)
            pair<int, int> next = edges[current][index];

            // 다음 정점이 아직 방문되지 않았고, 거리가 갱신되어야 하는 경우
            if(!visited[next.first] && dist[next.first] > dist[current] + next.second) {
                // 거리 갱신
                dist[next.first] = dist[current] + next.second;
                // 큐에 삽입 (동일한 정점에 대해 여러 간선 정보가 삽입될 수 있음.)
                pq.push(make_pair(next.first, dist[next.first]));
            }
        }
    }

    for(int index = 1; index <= V; index++) {
        if(dist[index] == MAX) cout << "INF\n";
        else cout << dist[index] << endl;
    }
}