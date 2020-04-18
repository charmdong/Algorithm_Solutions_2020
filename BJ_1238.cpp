/**
 * @author : donggun.chung
 * @date : 2020. 04. 19
 * @site : BOJ
 * @probInfo : 1238 Party 
 * @time : 80ms
 * @memory : 2132KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 100001

using namespace std;

int V, E, X;
vector<vector<pair<int, int> > > edgeList;
vector<int> dist;
vector<bool> visited;

struct cmp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

int solution(int start, int des);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E >> X;
    edgeList.assign(V + 1, vector<pair<int, int> >());

    int src, des, weight;
    for(int index = 0; index < E; index++) {
        cin >> src >> des >> weight;
        edgeList[src].push_back(make_pair(des, weight));
    }

    int answer = 0;
    for(int index = 1; index <= V; index++) {
        int res = solution(index, X);
        res += solution(X, index);
        if(answer < res) answer = res;
    }

    cout << answer << endl;

    return 0;
}

int solution(int start, int des) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> q;

    dist.assign(V + 1, MAX);
    visited.assign(V + 1, false);

    dist[start] = 0;

    q.push(make_pair(start, dist[start]));

    while(!q.empty()) {
        int current = q.top().first;
        q.pop();

        if(current == des) return dist[current];

        if(visited[current]) continue;
        visited[current] = true;

        for(int index = 0; index < edgeList[current].size(); index++) {
            pair<int, int> next = edgeList[current][index];

            if(!visited[next.first] && dist[next.first] > dist[current] + next.second) {
                dist[next.first] = dist[current] + next.second;
                q.push(make_pair(next.first, dist[next.first]));
            }
        }
    }

    return 0;
}