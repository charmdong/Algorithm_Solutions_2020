/**
 * @author : donggun.chung
 * @date : 2020. 03. 08
 * @site : BOJ
 * @probInfo : 1107 리모컨
 * @time : 968ms
 * @memory : 1984KB
 */ 

#include <iostream>
#include <string>
using namespace std;

int N, M, answer;
bool num[10];

void dfs(int len, string cur = "", int cnt = 0);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    cin >> M;
    
    int n;
    for(int iter = 0; iter < M; iter++) {
        cin >> n;
        num[n] = true;        
    }

    answer = abs(N - 100);

    dfs(to_string(N).length() - 1);
    dfs(to_string(N).length());
    dfs(to_string(N).length() + 1);

    cout << answer << endl;

    return 0;
}

void dfs(int len, string cur, int cnt) {
    if(cnt > answer) return;
    if(cnt == len) {
        if(cur == "") {
            return;
        }
        int res = cnt + abs(N - stoi(cur));

        if(answer > res) answer = res;
        return;
    }

    for(int index = 0; index < 10; index++) {
        if(!num[index]) {
            dfs(len, cur + to_string(index), cnt + 1);
        }
    }
}