/**
 * @author : donggun.chung
 * @date : 2020. 03. 05
 * @site : SWEA
 * @probInfo : 1808 지희의 고장난 계산기
 * @time : 48ms
 * @memory : 16,588KB
 */ 

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#define MAX 987654321
using namespace std;

int T, X;
vector<int> buttons;
int memo[1000001];

int solution(int num);
int clickCount(int num);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        buttons.assign(10, 0);
        
        for(int index = 0; index < 10; index++) {
            cin >> buttons[index];
            if(buttons[index] == 1) memo[index] = 1;
        }

        cin >> X;
        
        int answer = solution(X);
        answer = (answer == MAX) ? -1 : memo[X] + 1; 
        
        cout << "#" << test << " " << answer << endl;
        
        memset(memo, 0, sizeof(memo));
    }

    return 0;
}

int solution(int num) {
    if(memo[num] != 0) return memo[num];

    memo[num] = clickCount(num);

    for(int index = 1; index <= sqrt(num); index++) {
        if(num % index == 0) {
            int num1 = solution(index);
            int num2 = solution(num / index);

            memo[num] = min(memo[num], num1 == MAX || num2 == MAX ? MAX : num1 + num2 + 1);
        }
    }

    return memo[num];
}

int clickCount(int num) {
    int count = 0;

    while(num > 0) {
        int tmp = num % 10;
        if(buttons[tmp] == 0) return MAX;

        num /= 10;
        count++;
    }

    return count;
}