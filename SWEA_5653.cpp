#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define INACTIVE 0
#define ACTIVE 1
#define DEAD 2
using namespace std;

int T, N, M, K;

int life[400][400];
int status[400][400];
int pass[400][400];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
queue<pair<int, int> > q;

int solution();

int main()
{
	ios_base ::sync_with_stdio(false);
	
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> T;
	for(int test = 1; test <= T; test++) {
		cin >> N >> M >> K;
		
		for(int row = 151; row < 151 + N; row++) {
			for(int col = 151; col < 151 + M; col++) {
				cin >> life[row][col];
				if(life[row][col] > 0) {
					q.push(make_pair(row, col));
				}
			}
		}
		
		cout << "#" << test << " " << solution() << endl;
		memset(life, 0, sizeof(life));
		memset(status, 0, sizeof(status));
		memset(pass, 0, sizeof(pass));
		while(!q.empty()) q.pop();
	}
	
	return 0;
}

int solution() {
	int answer = 0;
	int next[400][400];
	memset(next, 0, sizeof(next));
	
	for(int time = 1; time <= K; time++) {
		int qSize = q.size();
		for(int index = 0; index < qSize; index++) {
			pair<int, int> now = q.front();
			q.pop();
			
			if(life[now.first][now.second] <= pass[now.first][now.second]) {
				if(status[now.first][now.second] == INACTIVE) {
					for(int dir = 0; dir < 4; dir++) {
						int ny = now.first + dy[dir];
						int nx = now.second + dx[dir];
						
						if(life[ny][nx] == 0) {
							if(next[ny][nx] == 0) {
								q.push(make_pair(ny, nx));
								next[ny][nx] = life[now.first][now.second];
							} else {
								next[ny][nx] = max(next[ny][nx], life[now.first][now.second]);
							}
						}
					}
					pass[now.first][now.second] = 1;
					status[now.first][now.second] = ACTIVE;
					q.push(now);
				} else if(status[now.first][now.second] == ACTIVE) {
					status[now.first][now.second] = DEAD;
					pass[now.first][now.second] = 0;
				}
			} else {
				if(status[now.first][now.second] != DEAD) {
					pass[now.first][now.second]++;
					q.push(now);
				}
			}
		}
		
		for(int row = 0; row < 400; row++) {
			for(int col = 0; col < 400; col++) {
				if(next[row][col] > 0) {
					life[row][col] = next[row][col];
					next[row][col] = 0;
				}
			}
		}
	}
	
	for(int row = 0; row < 400; row++) {
		for(int col = 0; col < 400; col++) {
			if(life[row][col] > 0 && life[row][col] == pass[row][col]) {
				status[row][col]++;
			}
			if(life[row][col] > 0 && status[row][col] != DEAD) answer++;
		}
	}
	
	return answer;
}
