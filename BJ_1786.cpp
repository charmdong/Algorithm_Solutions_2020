/**
 * @author : donggun.chung
 * @date : 2020. 04. 13
 * @site : BOJ
 * @probInfo : 1786 찾기 
 * @time : 148ms
 * @memory : 11096KB
 */ 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string T, P;
vector<int> answer;

vector<int> getFail(string pattern);
void KMP(string origin, string pattern);
void solution();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    getline(cin, T);
    getline(cin, P);

    solution();

    return 0;
}

void solution() {
    KMP(T, P);

    cout << answer.size() << endl;
    for(int index : answer) {
        cout << index << " ";
    }
    cout << endl;
}

vector<int> getFail(string pattern) {
    vector<int> fail(pattern.length(), 0);
    int j = 0;
    // i : 접두사, j : 접미사 인덱스라고 생각하자.
    for(int i = 1; i < pattern.length(); i++) {
        while(j > 0 && pattern[i] != pattern[j]) j = fail[j - 1];
        if(pattern[i] == pattern[j]) fail[i] = ++j;
    }

    return fail;
}

void KMP(string origin, string pattern) {
    vector<int> fail = getFail(pattern);
    int j = 0;

    for(int i = 0; i < origin.length(); i++) {
        while(j > 0 && origin[i] != pattern[j]) j = fail[j - 1];

        if(origin[i] == pattern[j]) {
            if(j == pattern.length() - 1) {
                answer.push_back(i - pattern.length() + 2);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
}