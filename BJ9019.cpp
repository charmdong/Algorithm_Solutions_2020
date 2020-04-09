/**
 * @author : donggun.chung
 * @date : 2020. 03. 02
 * @site : BOJ
 * @probInfo : 9019 DSLR
 * @time : 4628ms
 * @memory : 2252KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#define MOD 10000
using namespace std;

int T, n1, n2;
vector<bool> visited;

string bfs();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    for(int test = 1; test <= T; test++) {
        visited.assign(MOD, false);
        cin >> n1 >> n2;
        cout << bfs() << endl;
    }

    return 0;
}

string bfs() {
    queue<pair<int, string> > q;

    visited[n1] = true;
    q.push(make_pair(n1, ""));

    while(!q.empty()) {
        pair<int, string> current = q.front();
        int curNum = current.first;
        string curRes = current.second;
        q.pop();

        if(curNum == n2) {
            return curRes;
        }

        // case D
        int nextNum = (curNum * 2) % MOD;
        if(!visited[nextNum]) {
            visited[nextNum] = true;
            q.push(make_pair(nextNum, curRes + "D"));
        }

        // case S
        nextNum = (curNum == 0) ? 9999 : curNum - 1;
        if(!visited[nextNum]) {
            visited[nextNum] = true;
            q.push(make_pair(nextNum, curRes + "S"));
        }

        nextNum = (curNum % 1000) * 10 + curNum / 1000;
        if(!visited[nextNum]) {
            visited[nextNum] = true;
            q.push(make_pair(nextNum, curRes + "L"));
        }

        nextNum = curNum / 10 + (curNum % 10) * 1000;
        if(!visited[nextNum]) {
            visited[nextNum] = true;
            q.push(make_pair(nextNum, curRes + "R"));
        }
    }
}