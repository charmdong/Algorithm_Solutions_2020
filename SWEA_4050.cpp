/**
 * @author : donggun.chung
 * @date : 2020. 04. 29
 * @site : SWEA
 * @probInfo : 4050 재관이의 대량 할인
 * @time : 428ms
 * @memory : 13,084KB
 */ 

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    vector<int> price;
    int T, N;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N;
        price.assign(N, 0);
        for(int index = 0; index < N; index++) {
            cin >> price[index];
        }

        sort(price.rbegin(), price.rend());
        int answer = 0;
        for(int index = 0; index < price.size(); index++) {
            if(index % 3 != 2) answer += price[index];
        }
        
        cout << "#" << test << " " << answer << endl;
    }

    return 0;
}