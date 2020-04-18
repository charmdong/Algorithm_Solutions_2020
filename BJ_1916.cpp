/**
 * @author : donggun.chung
 * @date : 2020. 04. 18
 * @site : BOJ
 * @probInfo : 1916 최소비용 구하기
 * @time : 24ms
 * @memory : 3180KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MAX 100000001
using namespace std;

int V, E;
int startIndex, endIndex;

vector<vector<pair<int, int> > > edgeList;
vector<int> dist;
vector<bool> visited;

struct cmp {
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        return p1.second > p2.second;
    }
};

int solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;
    edgeList.assign(V + 1, vector<pair<int, int> >());

    int src, des, w;
    for(int index = 0; index < E; index++) {
        cin >> src >> des >> w;
        edgeList[src].push_back(make_pair(des, w));
    }

    cin >> startIndex >> endIndex;

    cout << solution() << endl;

    return 0;
}

int solution() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp > q;

    dist.assign(V + 1, MAX);
    visited.assign(V + 1, false);

    dist[startIndex] = 0;

    q.push(make_pair(startIndex, dist[startIndex]));

    while(!q.empty()) {
        int current = q.top().first;
        q.pop();

        if(current == endIndex) return dist[current];

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