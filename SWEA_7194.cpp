/**
 * @author : donggun.chung
 * @date : 2020. 03. 20
 * @site : SWEA
 * @probInfo : 7194 화섭이의 미생물 배양
 * @time : 44ms
 * @memory : 12,572KB
 */ 

#include <iostream>

using namespace std;

int T, s, t, a, b;


int main()
{
	cin >> T;
	for(int test = 1; test <= T; test++) {
		int answer = 0;
        
        cin >> s >> t >> a >> b;
		
        if(b == 1) {
            int diff = t - s;
            answer = (diff % a == 0) ? (t - s) / a : -1;
        } else {
            while(s != t) {
                answer++;
                if(t % b == 0) {
                    if(t / b < s) t -= a;
                    else t /= b;
                } else {
                    t -= a;
                }

                if(s > t) {
                    answer = -1;
                    break;
                }
            }
        }

        cout << "#" << test << " " << answer << endl;
	}
	return 0;
}

