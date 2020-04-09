
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int T;
int N, K;
vector<int> classList;

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> K;
        
        classList.assign(N, 0);
        for(int index = 0; index < N; index++) {
            cin >> classList[index];
        }

        sort(classList.begin(), classList.end());
        
        double answer = 0;
        for(int index = N - K; index < N; index++) {
            answer = (answer + classList[index]) / 2;
        }

        printf("#%d %.6f\n", test, answer);
    }

    return 0;
}