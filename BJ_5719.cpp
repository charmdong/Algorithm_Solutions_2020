/**
 * @author : donggun.chung
 * @date : 2020. 04. 20
 * @site : BOJ
 * @probInfo : 5719 거의 최단 경로
 * @time : 40ms
 * @memory : 3100KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 500001
using namespace std;

int N, M;

int edgeList[500][500];
vector<int> dist;
vector<vector<int> > parent;
vector<bool> visited;

struct cmp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

int solution(int src, int des);
void remove(int des);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    int S, D;
    while(true) {
        cin >> N >> M;
        
        if(N == 0 && M == 0) break;

        cin >> S >> D;

        int src, des, w;
        for(int index = 0; index < M; index++) {
            cin >> src >> des >> w;
            edgeList[src][des] = w;
        }

        solution(S, D);
        remove(D);
        cout << solution(S, D) << endl;
        for(int index = 0; index < N; index++) {
            fill(edgeList[index], edgeList[index] + N, 0);
        }
    }

    return 0;
}

int solution(int src, int des) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> q;
    int answer = -1;

    dist.assign(N, MAX);
    parent.assign(N, vector<int>());
    visited.assign(N, false);

    dist[src] = 0;
    q.push(make_pair(src, dist[src]));

    while(!q.empty()) {
        int current = q.top().first;
        q.pop();

        if(current == des) {
            answer = dist[current];
            break;
        }

        if(visited[current]) continue;
        visited[current] = true;

        for(int next = 0; next < N; next++) {
            if(edgeList[current][next] == 0 || visited[next]) continue;
            
            if(dist[next] > dist[current] + edgeList[current][next]) {
                dist[next] = dist[current] + edgeList[current][next];
                parent[next].clear();
                parent[next].push_back(current);
                q.push(make_pair(next, dist[next]));
            } else if(dist[next] == dist[current] + edgeList[current][next]) {
                parent[next].push_back(current);
            }
        }
    }

    return answer;
}

void remove(int des) {
    queue<int> q;

    q.push(des);

    while(!q.empty()) {
        int current = q.front();
        q.pop();

        for(int index = 0; index < parent[current].size(); index++) {
            int p = parent[current][index];

            edgeList[p][current] = 0;
            q.push(p);
        }
    }
}