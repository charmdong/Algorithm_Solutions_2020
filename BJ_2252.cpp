/**
 * @author : donggun.chung
 * @date : 2020. 05. 13
 * @site : BOJ
 * @probInfo : 2252 줄 세우기 
 * @time : 32ms
 * @memory : 4060KB
 */ 

#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int> > graph;
vector<int> line;
vector<bool> visited;

void dfs(int cur);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    
    graph.assign(N + 1, vector<int>());
    visited.assign(N + 1, false);

    int big, small;
    for(int iter = 0; iter < M; iter++) {
        cin >> big >> small;
        graph[big].push_back(small);
    }

    for(int index = 1; index <= N; index++) {
        if(!visited[index]) {
            dfs(index);
        }
    }

    for(auto iter = line.rbegin(); iter != line.rend(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;

    return 0;
}

void dfs(int cur) {
    visited[cur] = true;

    for(int next : graph[cur]) {
        if(!visited[next]) {
            dfs(next);
        }
    }

    line.push_back(cur);
}