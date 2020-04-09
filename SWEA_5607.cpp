/**
 * @author : donggun.chung
 * @date : 2020. 04. 02
 * @site : SWEA
 * @probInfo : 5607 [Professional]조합
 * @time : 152ms
 * @memory : 21,396KB
 */ 

#include <iostream>
#include <vector>
#define MOD 1234567891
using namespace std;

int T, N, R;
vector<long> factorial;

long solution(long n, int x);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> R;
        factorial.assign(N + 1, 0);
        factorial[0] = 1;
        for(int index = 1; index <= N; index++) {
            factorial[index] = (factorial[index - 1] * index) % MOD;
        }

        long denominator = ((factorial[N - R] % MOD) * (factorial[R]) % MOD) % MOD;
        long answer = ((factorial[N] % MOD) * (solution(denominator, MOD - 2) % MOD)) % MOD;

        cout << "#" << test << " " << answer << endl;
    }

    return 0;
}

long solution(long n, int x) {
    if(x == 0) return 1;

    long tmp = solution(n, x / 2);
    long result = ((tmp % MOD) * (tmp % MOD)) % MOD;

    if(x % 2 == 0) return result;
    else return (result * n) % MOD;
}