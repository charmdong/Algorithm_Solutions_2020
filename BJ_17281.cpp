/**
 * @author : donggun.chung
 * @date : 2020. 04. 15
 * @site : BOJ
 * @probInfo : 17281 ⚾️
 * @time : 352ms
 * @memory : 1984KB
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int N, answer;
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
	
	answer = 0;
	
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
	int hIndex = 0; // 타자 순서 저장
	
	for(int inning = 0; inning < N; inning++) {
		int outCnt = 0;
		vector<bool> base(3, false);

		while(outCnt < 3) {
			int hitRes = hit[inning][order[hIndex++]];
			
			switch(hitRes) {
				case 0: // 아웃인 경우
					outCnt++;
					break;
					
				case 1: // 안타인 경우 1루씩 전진
					if(base[2]) score++; 	// 3루에 주자가 있는 경우 득점
					base[2] = base[1]; 		// 2루 주자 -> 3루
					base[1] = base[0]; 		// 1루 주자 -> 2루
					base[0] = true; 		// 1루에 주자 생김
					break;
					
				case 2: // 2루타인 경우 2루씩 전진
					// 3루에 주자가 있는 경우 -> 득점
					if(base[2]) {
						score++;
						base[2] = false;
					}
					// 2루에 주자가 있는 경우 -> 득점
					if(base[1]) {
						score++;
						base[1] = false;
					}
					base[2] = base[0]; 	// 1루 주자 -> 3루
					base[0] = false;	// 1루에 주자가 있었던 경우를 대비해서 변경
					base[1] = true;	// 2루에 주자 생김
					break;
					
				case 3: // 3루타인 경우 3루씩 전진
					for(int index = 0; index < 3; index++) {
						if(base[index]) score++;
						base[index] = false;
					}
					base[2] = true; // 3루에만 주자 있음
					break;
					
				case 4: // 홈런인 경우 모두 득점
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
