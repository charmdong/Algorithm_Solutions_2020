/**
 * @author : donggun.chung
 * @date : 2020. 03. 01
 * @site : BOJ
 * @probInfo : 1254 팰린드롬 만들기
 * @time : 0ms
 * @memory : 1988KB
 */ 

#include <iostream>
#include <string>
using namespace std;

int solution(string str);
bool isPanlin(string str);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    string str;

    cin >> str;
    
    cout << solution(str) << endl;

    return 0;
}

int solution(string str) {
    int len = str.length();

    for(int index = 1; index < len; index++) {
        string sub = str.substr(index);

        if(isPanlin(sub)) {
            return index;
        }
    }

    return str.length();
}

bool isPanlin(string str) {
    int len = str.length();

    for(int index = 0; index < len / 2; index++) {
        if(str[index] != str[len - index - 1]) {
            return false;
        }
    }

    return true;
}