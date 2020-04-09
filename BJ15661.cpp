/**
 * @author : donggun.chung
 * @date : 2020. 03. 11
 * @site : BOJ
 * @probInfo : 15661 Link and Start
 * @time : 84ms
 * @memory : 1988KB
 */ 

#include <iostream>
#include <vector>

using namespace std;

int N, answer = 987654321;
vector<vector<int> > senergy;
vector<bool> visited;
vector<int> teamA;

void dfs(int limit, int cnt);
int getTeamStat(vector<int> team);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    senergy.assign(N, vector<int>(N, 0));
    visited.assign(N, false);

    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            cin >> senergy[row][col];
        }
    }

    dfs(0, 0);

    cout << answer << endl;

    return 0;
}

void dfs(int limit, int cnt) {
    if(cnt == N / 2) {
        vector<int> teamB;
        for(int index = 0; index < N; index++) {
            if(!visited[index]) teamB.push_back(index);
        }

        int totalA = getTeamStat(teamA);
        int totalB = getTeamStat(teamB);
        int res = abs(totalA - totalB);

        if(answer > res) answer = res;
        return;
    }

    for(int index = limit; index < N; index++) {
        if(visited[index]) continue;

        visited[index] = true;
        teamA.push_back(index);
        dfs(index, cnt + 1);
        teamA.pop_back();
        visited[index] = false;
    }
}

int getTeamStat(vector<int> team) {
    int total = 0;

    for(int src : team) {
        for(int des : team) {
            total += (senergy[src][des]);
        }
    }

    return total; 
}