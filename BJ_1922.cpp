/**
 * @author : donggun.chung
 * @date : 2020. 05. 03
 * @site : BOJ
 * @probInfo : 1922 네트워크 연결 
 * @time : 28ms
 * @memory : 4420KB
 */ 
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cmp {
    bool operator()(const pair<pair<int, int>, int> &p1, const pair<pair<int, int>, int> &p2) {
        return p1.second > p2.second;
    }
};

int N, M;
vector<int> parent;
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int> >, cmp> q;

int findSet(int index);
bool unionSet(int a, int b);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    parent.assign(N + 1, 0);
    
    for(int index = 1; index <= N; index++) {
        parent[index] = index;
    }

    for(int index = 0; index < M; index++) {
        int src, des, weight;
        cin >> src >> des >> weight;
        q.push(make_pair(make_pair(src, des), weight));
    }

    int answer = 0;
    int cnt = 0;

    while (!q.empty())
    {
        int a = q.top().first.first;
        int b = q.top().first.second;
        int w = q.top().second;
        q.pop();

        if (unionSet(a, b))
        {
            answer += w;
            if (++cnt == N - 1)
                break;
        }
    }

    cout << answer << endl;

    return 0;
}

int findSet(int index) {
    if(parent[index] == index) return index;
    return (parent[index] = findSet(parent[index]));
}

bool unionSet(int a, int b) {
    int pa = findSet(a);
    int pb = findSet(b);

    if(pa != pb) {
        parent[pb] = pa;
        return true;
    }

    return false;
}