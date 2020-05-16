/**
 * @author : donggun.chung
 * @date : 2020. 05. 14
 * @site : BOJ
 * @probInfo : 1774 우주신과의 교감  
 * @time : 108ms
 * @memory : 14308KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int N, M;
double answer;
vector<int> parent;
vector<pair<int, int> > position;

struct cmp {
    bool operator()(const pair<pair<int, int>, double> &p1, const pair<pair<int, int>, double> &p2) {
        return p1.second > p2.second;
    }
};

int findParent(int index);
bool unionSet(int src, int des);

int main() {
    cin >> N >> M;

    position.assign(N + 1, make_pair(0, 0));
    for(int index = 1; index <= N; index++) {
        cin >> position[index].first >> position[index].second;
    }

    parent.assign(N + 1, 0);
    for(int index = 1; index <= N; index++) {
        parent[index] = index;
    }

    priority_queue<pair<pair<int, int>, double>, vector<pair<pair<int, int>, double> >, cmp> q;

    for(int src = 1; src < N; src++) {
        for(int des = src + 1; des <= N; des++) {
            double rowDiff = pow(position[src].first - position[des].first, 2);
            double colDiff = pow(position[src].second - position[des].second, 2);
            double dist = sqrt(rowDiff + colDiff);

            q.push(make_pair(make_pair(src, des), dist));
        }
    }

    int src, des;
    int edgeCnt = 0;
    for(int iter = 0; iter < M; iter++) {
        cin >> src >> des;
        unionSet(src, des);
        edgeCnt++;
    }

    double dist;
    while(!q.empty()) {
        src = q.top().first.first;
        des = q.top().first.second;
        dist = q.top().second;
        q.pop();

        if(unionSet(src, des)) {
            answer += dist;
            if(++edgeCnt == N - 1) {
                break;
            }
        }
    }

    printf("%.2f\n", answer);

    return 0;
}

int findParent(int index) {
    if(parent[index] == index) return index;
    return parent[index] = findParent(parent[index]);
}

bool unionSet(int src, int des) {
    int sp = findParent(src);
    int sd = findParent(des);

    if(sp != sd) {
        parent[sp] = sd;
        return true;
    }

    return false;
}