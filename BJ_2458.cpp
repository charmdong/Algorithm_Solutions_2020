/**
 * @author : donggun.chung
 * @date : 2020. 05. 14
 * @site : BOJ
 * @probInfo : 2458 키 순서 
 * @time : 380ms
 * @memory : 3044KB
 */ 
#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int> > graph;

int solutionByFloyd();
int solutionByDfs();
int dfs(int index);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    
    graph.assign(N + 1, vector<int>(N + 1, 0));

    int small, big;
    for(int iter = 0; iter < M; iter++) {
        cin >> small >> big;

        graph[small][big] = 1;
    }

    cout << solutionByDfs() << endl;

    return 0;
}

int solutionByFloyd() {
    int answer = 0;
    for(int k = 1; k <= N; k++) {
        for(int src = 1; src <= N; src++) {
            if(k == src) continue;
            for(int des = 1; des <= N; des++) {
                if(src == des || k == des || graph[src][des] == 1) continue;
                if(graph[src][k] == 1 && graph[k][des] == 1) graph[src][des] = 1;
            }
        }
    }

    for(int row = 1; row <= N; row++) {
        for(int col = 1; col <= N; col++) {
            graph[0][col] += graph[row][col];
            graph[row][0] += graph[row][col];
        }
    }
    
    for(int index = 1; index <= N; index++) {
        if(graph[index][0] + graph[0][index] == N - 1) answer++;
    }

    return answer;
}

/**
 * 
 * dfs를 사용하는 경우
 * 1~N번을 시작으로 방문되는 횟수가 바로 해당 번호보다 큰 번호임을 의미
 * 단점 : 중복호출이 발생한다.
 * return type - int로 하면 되지 않을까?
 */ 

int solutionByDfs() {
    int answer = 0;

    for(int row = 1; row <= N; row++) {
        graph[row][0] = -1;
    }

    for(int index = 1; index <= N; index++) {
        if(graph[index][0] == -1) {
            dfs(index);
        }
    }

    for(int row = 1; row <= N; row++) {
        for(int col = 1; col <= N; col++) {
            graph[0][col] += graph[row][col];
            // graph[row][0] += graph[row][col];
        }
    }
    
    for(int index = 1; index <= N; index++) {
        if(graph[index][0] + graph[0][index] == N - 1) answer++;
    }

    return answer;
}

int dfs(int cur) {
    for(int next = 1; next <= N; next++) {
        if(graph[cur][next] == 1) {
            if(graph[next][0] == -1) {
                dfs(next);
            }

            if(graph[next][0] > 0) {
                for(int index = 1; index <= N; index++) {
                    if(graph[next][index] == 1) {
                        graph[cur][index] = 1;
                    }
                }
            }
        }
    }

    int cnt = 0;
    for(int col = 1; col <= N; col++) {
        if(graph[cur][col] == 1) cnt++;
    }

    return graph[cur][0] = cnt;
}