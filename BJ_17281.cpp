

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int hit[50][10];
vector<int> orderCombination;

int solution(vector<int> &order);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    for(int num = 2; num <= 9; num++)
        orderCombination.push_back(num);

    cin >> N;
    for(int inning = 0; inning < N; inning++) {
        for(int hitter = 1; hitter <= 9; hitter++) {
            cin >> hit[inning][hitter];
        }
    }

    int answer = 0;

    while(true) {
        vector<int> tmpOrder = orderCombination;
        tmpOrder.insert(tmpOrder.begin() + 3, 1);

        int res = solution(tmpOrder);
        if(answer < res) answer = res;

        if(!next_permutation(orderCombination.begin(), orderCombination.end())) break;
    }

    cout << answer << endl;

    return 0;
}

int solution(vector<int> &order) {
    int score = 0;
    int hIndex = 0;
    vector<bool> base(3, false);

    for(int inning = 0; inning < N; inning++) {
        int outCnt = 0;

        while(outCnt < 3) {
            int hitRes = hit[inning][order[hIndex++]];

            switch(hitRes) {
            case 0:
                outCnt++;
                break;

            case 1:
                if(base[2]) score++;
                base[2] = base[1];
                base[1] = base[0];
                base[0] = true;
                break;

            case 2:
                if(base[2]) score++;
                if(base[1]) score++;
                base[2] = base[0]; // 1루 주자 -> 3루
                base[0] = false; // 1루 비었음
                base[1] = true; // 2루 주자 있음
                break;

            case 3:
                for(int index = 0; index < 3; index++) {
                    if(base[index]) score++;
                    base[index] = false;
                }
                base[2] = true; // 3루에만 주자 있음
                break;

            case 4:
                score++;
                for(int index = 0; index < 3; index++) {
                    if(base[index]) score++;
                    base[index] = false;
                }
            }

            hIndex %= 9;
        }
    }

    return score;
}