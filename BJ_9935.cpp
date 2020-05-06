#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getFail(string pattern);
vector<int> KMP(string origin, string pattern);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    string origin, pattern;
    cin >> origin >> pattern;
    
    while(true) {
        vector<int> del = KMP(origin, pattern);
        if(del.size() == 0) break;

        int gap = 0;
        for(int index : del) {
            origin.erase(index, pattern.length() - pattern.length() * (gap++));
        }
        //cout << origin << endl;
    }

    if(origin == "") cout << "FRULA\n";
    else cout << origin << endl; 

    return 0;
}

vector<int> getFail(string pattern) {
    vector<int> fail(pattern.length(), 0);
    int j = 0;

    for(int index = 1; index < pattern.length(); index++) {
        while(j > 0 && pattern[index] != pattern[j]) j = fail[j - 1];
        if(pattern[index] == pattern[j]) fail[index] = ++j;
    }

    return fail;
}

vector<int> KMP(string origin, string pattern) {
    vector<int> fail = getFail(pattern);
    vector<int> del;
    int j = 0;

    for(int i = 0; i < origin.length(); i++) {
        while(j > 0 && origin[i] != pattern[j]) j = fail[j - 1];

        if(origin[i] == pattern[j]) {
            if(j == pattern.length() - 1) {
                del.push_back(i - pattern.length() + 1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }

    return del;
}