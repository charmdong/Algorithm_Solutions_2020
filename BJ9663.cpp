/**
 * @author : donggun.chung
 * @date : 2020. 03. 08
 * @site : BOJ
 * @probInfo : 9663 N-Queen
 * @time : 4460ms
 * @memory : 1984KB
 */ 

#include <iostream>

using namespace std;

int N;
int col[15];
int answer = 0;

void dfs(int index = 0);
bool isPossible(int index);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    dfs();

    cout << answer << endl;

    return 0;
}

void dfs(int cnt) {
    if(cnt == N) {
        answer++;
        return;
    }

    for(int index = 0; index < N; index++) {
        col[cnt] = index;   // 같은 열 체크
        if(isPossible(cnt)) {
            dfs(cnt + 1);
        }
    }
}

bool isPossible(int index) {
    for(int row = 0; row < index; row++) {
        if(col[row] == col[index] || abs(col[index] - col[row]) == index - row) {
            return false;
        }
    }

    return true;
}