/**
 * @author : donggun.chung
 * @date : 2020. 04. 29
 * @site : SWEA
 * @probInfo : 5658 보물상자 비밀번호
 * @time : 11ms
 * @memory : 12,688kb
 */ 

#include <iostream>
#include <math.h>
#include <string>
#include <set>
using namespace std;

int N, K;
int solution(string str);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    string str;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> K;
        cin >> str;

        cout << "#" << test << " " << solution(str) << endl;
    }

    return 0;
}

int solution(string str) {
    int answer = 0;
    set<string, greater<string> > password;

    int cnt = 0;
    while(cnt++ < N){
        for(int index = 0; index < str.length(); index+=(N / 4)) {
            password.insert(str.substr(index, N / 4));
        }

        str.push_back(str[0]);
        str.erase(0, 1);
    }

    auto iter = password.begin();
    for(int i = 1; i < K; i++) iter++;
    string res = *iter;

    for(int index = N / 4 - 1; index >= 0; index--) {
        if(res[index] >= '0' && res[index] <= '9') {
            answer += (res[index] - '0') * pow(16, N / 4 - index - 1);
        } else {
            answer += (res[index] - 55) * pow(16, N / 4 - index - 1);
        }
    }

    return answer;
}