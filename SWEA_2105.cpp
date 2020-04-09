#include <iostream>
#include <cstring>
using namespace std;

int dy[4] = { 1,1,-1,-1};
int dx[4] = { 1,-1,-1,1};
int N, ans;
int sy, sx;
int map[20][20];
bool number[101];
bool visited[20][20];

void dfs(int y, int x ,int direct, int dist=0);
bool isInMap(int y, int x);

int main()
{
	int test;
	cin >> test;
	for (int i = 1; i <= test; i++) {
		ans = -1;
		cin >> N;
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				scanf("%d", &map[j][k]);

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				sy = j;
				sx = k;
				number[map[j][k]] = true;
				dfs(j, k, 0);
				number[map[j][k]] = false;
			}
		}
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}

void dfs(int y, int x, int d, int dist) {
	if (y == sy && x == sx && dist > 1) {
		ans = ans > dist ? ans : dist;
		return;
	}

	for(int i=0; i<2; i++){
		int ny = y + dy[d+i];
		int nx = x + dx[d+i];

		if (ny == sy && nx == sx) {
			dfs(ny, nx, d + i, dist + 1);
			continue;
		}

		if (isInMap(ny, nx) && !visited[ny][nx] && !number[map[ny][nx]]) {
			visited[ny][nx] = true;
			number[map[ny][nx]] = true;
			dfs(ny, nx, d+i, dist + 1);
			visited[ny][nx] = false;
			number[map[ny][nx]] = false;
		}
	}
}

bool isInMap(int y, int x) {
	if (y > -1 && y < N)
		if (x > -1 && x < N)
			return true;
	return false;
}