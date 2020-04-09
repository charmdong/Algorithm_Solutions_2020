/**
 * @author : donggun.chung
 * @date : 2020. 03. 15
 * @site : SWEA
 * @probInfo : 4012 요리사
 * @time : 771ms
 * @memory : 12,688KB
 */ 

#include <iostream>
#include <vector>
#define MAX 20000 * 16
using namespace std;

int T, N, answer;
int senergy[16][16];

void dfs(int cur = 0, int cnt = 0, int check = 0);
int getScore(vector<int>);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        answer = MAX;
        
        cin >> N;
        
        // input senergy
        for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
                cin >> senergy[row][col];
            }
        }

        dfs();
        cout << "#" << test << " " << answer << endl;
    }

    return 0;
}

void dfs(int cur, int cnt, int check) {
    if(cnt == N / 2) {
        vector<int> a, b;

        for(int index = 0; index < N; index++) {
            ((check & (1 << index)) == 0) ? a.push_back(index) : b.push_back(index);
        }

        int score1 = getScore(a);
        int score2 = getScore(b);
        int diff = abs(score1 - score2);

        if(answer > diff) answer = diff;

        return;
    }

    for(int index = cur; index < N; index++) {
        if((check & (1 << index)) == 0) {
            dfs(index + 1, cnt + 1, (check | (1 << index)));
        }
    }
}

int getScore(vector<int> taste) {
    int score = 0;

    for(int src : taste) {
        for(int des : taste) {
            score += senergy[src][des];
        }
    }

    return score;
}