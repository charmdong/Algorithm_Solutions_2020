
#include <iostream>
#include <vector>
using namespace std;

int T, N, M, answer = 1;

vector<vector<int> > graph;
vector<bool> visited;

void dfs(int cur, int len = 1);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int test = 1; test <= T; test++) {
        cin >> N >> M;
        graph.assign(N + 1, vector<int>());
        visited.assign(N + 1, false);

        int src, des;
        for(int index = 0; index < M; index++) {
            cin >> src >> des;

            graph[src].push_back(des);
            graph[des].push_back(src);
        }

        for(int index = 1; index <= N; index++) {
            visited[index] = true;
            dfs(index);
            visited[index] = false;
        }

        cout << "#" << test << " " << answer << endl;
        answer = 1;
    }

    return 0;
}

void dfs(int cur, int len) {
    if(answer < len) answer = len;

    for(int index = 0; index < graph[cur].size(); index++) {
        int next = graph[cur][index];

        if(!visited[next]) {
            visited[next] = true;
            dfs(next, len + 1);
            visited[next] = false;
        }
    }
}