/**
 * @author : donggun.chung
 * @date : 2020. 05. 01
 * @site : SWEA
 * @probInfo : 4366 정식이의 은행업무
 * @time : 6ms
 * @memory : 12,692KB
 */ 

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

int T;
string binary, tenary;

int solution();
int stringToDecimal(string num, bool isBinary = true);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> binary >> tenary;

        cout << "#" << test << " " << solution() << endl;
    }    

    return 0;
}

int solution() {
    vector<int> res;
    // 2진수 -> 2^2자리부터 하나씩 바꿔보기 !!!!
    for(int index = 1; index < binary.size(); index++) {
        char ch = binary[index];
        
        binary[index] = (ch == '0') ? '1' : '0';
        res.push_back(stringToDecimal(binary));
        binary[index] = ch;
    }

    // 3진수 -> 3^2자리부터 하나씩 바꿔보기 !!!!
    // 맨 앞은 1이면 2로 나머지는 0 -> 1, 2 / 1 -> 0, 2 / 2 -> 0, 1
    for(int index = 0; index < tenary.size(); index++) {
        char ch = tenary[index];
        
        if(index == 0) {
            tenary[index] = (ch == '1') ? '2' : '1';
            int val = stringToDecimal(tenary, false);
            
            if(find(res.begin(), res.end(), val) != res.end()) return val;
            
            tenary[index] = ch;
        } else {
            vector<char> replace;
            
            if(ch == '0') {
                replace.push_back('1');
                replace.push_back('2');
            } else if(ch == '1') {
                replace.push_back('0');
                replace.push_back('2');
            } else {
                replace.push_back('0');
                replace.push_back('1');
            }

            for(char r : replace) {
                tenary[index] = r;

                int val = stringToDecimal(tenary, false);
                if(find(res.begin(), res.end(), val) != res.end()) return val;
                
                tenary[index] = ch;
            }
        }
    }
}

int stringToDecimal(string num, bool isBinary) {
    int answer = 0;
    int bottom = isBinary ? 2 : 3;
    
    for(int index = num.size() - 1; index >= 0; index--) {
        answer += (num[index] - '0') * pow(bottom, num.size() - index - 1);
    }

    return answer;
}
