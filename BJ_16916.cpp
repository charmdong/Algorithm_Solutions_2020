/**
 * @author : donggun.chung
 * @date : 2020. 04. 16
 * @site : BOJ
 * @probInfo : 16916  부분 문자열
 * @time : 32ms
 * @memory : 3816KB
 */ 
#include <iostream>

using namespace std;

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    char S[1000001], P[1000001];

    cin >> S >> P;

    char *ptr = strstr(S, P);
    if(ptr == NULL) cout << 0 << endl;
    else cout << 1 << endl;

    return 0;
}