/**
 * @author : donggun.chung
 * @date : 2020. 03. 18
 * @site : BOJ
 * @probInfo : 17140  이차원 배열과 연산
 * @time : 0ms
 * @memory : 2024KB
 */ 

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int r, c, k, answer = 101;
int R = 3, C = 3;
int board[101][101];

struct compare{
	bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) {
		if(p1.second == p2.second) return p1.first > p2.first;
		else return p1.second > p2.second;
	}
};

void rowOperation();
void colOperation();
void dfs(int cnt = 0);

void print(){
	for(int row = 1; row <= R; row++) {
		for(int col = 1; col <= C; col++) {
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	ios_base ::sync_with_stdio(false);
	
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> r >> c >> k;
	
	for(int row = 1; row <= R; row++) {
		for(int col = 1; col <= C; col++) {
			cin >> board[row][col];
		}
	}
	
	dfs();
	
	cout << answer << endl;
	
	return 0;
}

void dfs(int cnt) {
	if(answer == -1) return;
	
	if(cnt > 100) {
		answer = -1;
		return;
	}

	if(board[r][c] == k) {
		answer = cnt;
		return;
	}
	
	(R < C) ? colOperation() : rowOperation();
	dfs(cnt + 1);
}

void rowOperation() {
	priority_queue<pair<int, int>, vector<pair<int, int> >, compare> q;
	int newCol = 0;
	
	for(int row = 1; row <= R; row++) {
		vector<int> cnt(101, 0);
		
		// 숫자 등장 횟수 파악
		for(int col = 1; col <= C; col++) {
			if(board[row][col] == 0) continue;
			cnt[board[row][col]]++;
		}
		
		// 기준에 맞게 정렬
		for(int index = 1; index <= 100; index++) {
			if(cnt[index] == 0) continue;
			
			q.push(make_pair(index, cnt[index]));
			if(q.size() >= 50) break;
		}
		
		// 열 길이 갱신
		if(newCol < q.size() * 2) newCol = q.size() * 2;
		
		// 배열 재배치
		memset(board[row], 0, sizeof(board[row]));
		for(int index = 1; !q.empty(); index += 2) {
			pair<int, int> current = q.top();
			q.pop();
			
			board[row][index] = current.first;
			board[row][index + 1] = current.second;
		}
	}
	
	C = newCol;
}

void colOperation() {
	priority_queue<pair<int, int>, vector<pair<int, int> >, compare> q;
	int newRow = 0;
	
	for(int col = 1; col <= C; col++) {
		vector<int> cnt(101, 0);
		
		for(int row = 1; row <= R; row++) {
			if(board[row][col] == 0) continue;
			cnt[board[row][col]]++;
		}
		
		for(int index = 1; index <= 100; index++) {
			if(cnt[index] == 0) continue;
			
			q.push(make_pair(index, cnt[index]));
			if(q.size() >= 50) break;
		}
		
		if(newRow < q.size() * 2) newRow = q.size() * 2;
		
		for(int row = 1; row <= 100; row++) board[row][col] = 0;
		for(int index = 1; !q.empty(); index += 2) {
			pair<int, int> current = q.top();
			q.pop();
			
			board[index][col] = current.first;
			board[index + 1][col] = current.second;
		}
	}
	
	R = newRow;
}
