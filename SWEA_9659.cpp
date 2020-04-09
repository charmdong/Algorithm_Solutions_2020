/**
 * @author : donggun.chung
 * @date : 2020. 04. 04
 * @site : SWEA
 * @probInfo : 9659 다항식 계산
 * @time : 7ms
 * @memory : 12,688kb
 */ 

#include <iostream>
#include <vector>
#define MOD 998244353
using namespace std;

int T, N, M;
int values[51][3];
vector<int> domainList;
vector<long long> dp;
void solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N;
        dp.assign(N + 1, 0);
        dp[0] = 1;
        
        // tn, an, bn 입력
        for(int i = 2; i <= N; i++) {
            for(int index = 0; index < 3; index++) {
                cin >> values[i][index];
            }
        }

        cin >> M;
        domainList.assign(M, 0);
        // 정의역 입력
        for(int index = 0; index < M; index++) {
            cin >> domainList[index];
        }

        cout << "#" << test << " ";
        solution();
    }

    return 0;
}

void solution() {
    for(int domain : domainList) {
        dp[1] = domain;

        for(int index = 2; index <= N; index++) {
            switch(values[index][0]) {
            case 1:
                dp[index] = (dp[values[index][1]] + dp[values[index][2]]) % MOD;
                break;
            case 2:
                dp[index] = (values[index][1] * dp[values[index][2]]) % MOD;
                break;
            case 3:
                dp[index] = (dp[values[index][1]] * dp[values[index][2]]) % MOD;
                break;
            }
        }

        cout << dp[N] << " ";
    }
    cout << endl;
}