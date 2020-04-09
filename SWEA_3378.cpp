

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int T, N, M, R, C, S;
vector<string> stylish, myStr;
stack<char> bracket[3];

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> M;

        stylish.assign(N, "");
        myStr.assign(M, "");

        for(int index = 0; index < N; index++) {
            cin >> stylish[index];
        }

        for(int index = 0; index < M; index++) {
            cin >> myStr[index];
        }

        
    }

    return 0;
}