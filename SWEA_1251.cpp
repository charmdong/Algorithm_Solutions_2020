/**
 * @author : donggun.chung
 * @date : 2020. 03. 11
 * @site : SWEA
 * @probInfo : 1251
 * @time : 588ms
 * @memory : 29,212KB
 */ 

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX 1000
using namespace std;

struct edge{
    int src;
    int des;
    long long weight;

    edge(int s, int d, long long w) : src(s), des(d), weight(w) {}
};

int T, N;
double tax;

vector<pair<int, int> > island;

int parent[MAX];

bool compare(const edge& e1, const edge& e2) {
    return e1.weight < e2.weight;
}

int findParent(int ver);
void unionGraph(int a, int b);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        vector<edge> eList;

        cin >> N;

        fill(parent, parent + N, -1);
        island.assign(N, make_pair(0, 0));
        for(int index = 0; index < N; index++) {
            parent[index] = index;
            cin >> island[index].first;
        }

        for(int index = 0; index < N; index++) {
            cin >> island[index].second;
        }
        cin >> tax;

        for(int src = 0; src < N; src++) {
            for(int des = src + 1; des < N; des++) {
                long long colLen = pow(island[src].first - island[des].first, 2);
                long long rowLen = pow(island[src].second - island[des].second, 2);
                
                eList.push_back(edge(src, des, rowLen + colLen));
            }
        }

        sort(eList.begin(), eList.end(), compare);
        
        long long answer = 0;

        for(edge e : eList) {
            if(findParent(e.src) != findParent(e.des)) {
                unionGraph(e.src, e.des);
                answer += e.weight;
            }
        }

        printf("#%d %.f\n", test, (double)(answer * tax));
    }

    return 0;
}

int findParent(int ver) {
    if(parent[ver] == ver) return ver;
    else return parent[ver] = findParent(parent[ver]);
}

void unionGraph(int src, int des) {
    src = findParent(src);
    des = findParent(des);

    if(src != des) parent[src] = des;
}