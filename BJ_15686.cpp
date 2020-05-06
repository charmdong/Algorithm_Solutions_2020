/**
 * @author : donggun.chung
 * @date : 2020. 05. 04
 * @site : BOJ
 * @probInfo : 15685 치킨 배달
 * @time : 0ms
 * @memory : 1984KB
 */ 

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int N, M, answer = 10000;
vector<pair<int, int> > house, chicken, selected;

void solution(int index = 0);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    int pos;
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            cin >> pos;
            if(pos == 1) {
                house.push_back(make_pair(row, col));
            } else if(pos == 2) {
                chicken.push_back(make_pair(row, col));
            } 
        }
    }

    solution();

    cout << answer << endl;

    return 0;
}

void solution(int index) {
    if(selected.size() == M) {
        int total = 0;
        
        for(pair<int, int> h : house) {
            int dist = 100;
            
            for(pair<int, int> pos : selected) {
                dist = min(dist, abs(h.first - pos.first) + abs(h.second - pos.second));
            }

            total += dist;
        }

        answer = min(answer, total);
        return;
    }

    for(int cur = index; cur < chicken.size(); cur++) {
        selected.push_back(chicken[cur]);
        solution(cur + 1);
        selected.pop_back();
    }
}