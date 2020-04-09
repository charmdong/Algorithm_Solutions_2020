/**
 * @author : donggun.chung
 * @date : 2020. 04. 07
 * @site : BOJ
 * @probInfo : 17837 새로운 게임 2  
 * @time : 0ms
 * @memory : 1988KB
 */ 

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int board[13][13];
vector<int> chessPos[13][13];
vector<pair<pair<int, int>, int> > chessList;

int dy[5] = {0, 0, 0, -1, 1};
int dx[5] = {0, 1, -1, 0, 0};

int solution();
int move(int index);
bool isInBoard(int y, int x);

int main()
{
	ios_base ::sync_with_stdio(false);
	
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N >> K;
	
	chessList.assign(K, make_pair(make_pair(0, 0), 0));
	
	for(int row = 1; row <= N; row++) {
		for(int col = 1; col <= N; col++) {
			cin >> board[row][col];
		}
	}
	
	int y, x, dir;
	for(int index = 0; index < K; index++) {
		cin >> y >> x >> dir;
		chessList[index].first = make_pair(y, x);
		chessList[index].second = dir;
		chessPos[y][x].push_back(index);
	}
	
	cout << solution() << endl;
	
	return 0;
}

int solution() {
	int answer = 0 ;
	
	while(answer <= 1000) {
		answer++;
		for(int index = 0; index < K; index++) {
			if(move(index) >= 4) return answer;
		}
	}
	
	return -1;
}

int move(int index) {
	int &curRow = chessList[index].first.first;
	int &curCol = chessList[index].first.second;
	int &curDir = chessList[index].second;
	
	int ny = curRow + dy[curDir];
	int nx = curCol + dx[curDir];
	
	if(!isInBoard(ny, nx) || board[ny][nx] == 2) {
		curDir += (curDir % 2 == 0) ? -1 : 1;
		
		ny = curRow + dy[curDir];
		nx = curCol + dx[curDir];
		
		if(!isInBoard(ny, nx) || board[ny][nx] == 2) return 0;
	}
	
	vector<int> &current = chessPos[curRow][curCol];
	vector<int> &next = chessPos[ny][nx];
	auto search = find(current.begin(), current.end(), index);
	
	if(board[ny][nx] == 1) reverse(search, current.end());
	
	for(auto iter = search; iter != current.end(); iter++) {
		chessList[*iter].first = make_pair(ny, nx);
		next.push_back(*iter);
	}
	
	current.erase(search, current.end());
	return next.size();
}

bool isInBoard(int y, int x) {
	return (y > 0 && y <= N && x > 0 && x <= N);
}
