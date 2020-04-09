/**
 * @author : donggun.chung
 * @date : 2020. 03. 23
 * @site : BOJ
 * @probInfo : 17143 낚시왕 
 * @time : 768ms
 * @memory : 2104KB
 */ 

#include <iostream>
#include <queue>
#define SPEED 0
#define DIR 1
#define SIZE 2
using namespace std;

int R, C, M;

int dy[5] = {0, -1, 1, 0, 0};
int dx[5] = {0, 0, 0, 1, -1};

int origin[101][101][3];

queue<pair<int, int> > sharkPos;

int solution();
int getShark(int col);
void moveShark();

int main() {
	int r, c, s, d, z;
	
	cin >> R >> C >> M;
	for(int index = 0; index < M; index++) {
        cin >> r >> c >> s >> d >> z;
        origin[r][c][SPEED] = s;
        origin[r][c][DIR] = d;
        origin[r][c][SIZE] = z;
        sharkPos.push(make_pair(r, c));
    }
    cout << solution() << endl;
	
	return 0;
}


int solution() {
    int answer = 0;

    for(int index = 1; index <= C; index++) {
        answer += getShark(index);
        moveShark();
    }

    return answer;
}

int getShark(int col) {
    int res = 0;

    for(int row = 1; row <= R; row++) {
        if(origin[row][col][SIZE] > 0) {
            res = origin[row][col][SIZE];
            origin[row][col][SIZE] = 0;
            break;
        }
    }

    return res;
}

void moveShark() {
    int nextBoard[101][101][3] = {0, };
    int len = sharkPos.size();
    for(int index = 0; index < len; index++) {
        int y = sharkPos.front().first;
        int x = sharkPos.front().second;
        int curSpeed = origin[y][x][SPEED];
        int curDir = origin[y][x][DIR];
        int curSize = origin[y][x][SIZE];
        sharkPos.pop();

        // move
        int dist = curSpeed;
        while(dist-- > 0) {
            if(curDir == 1) {
                if(y - 1 < 1) {
                    curDir = 2;
                    y++;
                } else {
                    y--;
                }
            } else if(curDir == 2) {
                if(y + 1 > R) {
                    curDir = 1;
                    y--;
                } else {
                    y++;
                }
            } else if(curDir == 3) {
                if(x + 1 > C) {
                    curDir = 4;
                    x--;
                } else {
                    x++;
                }
            } else {
                if(x - 1 < 1) {
                    curDir = 3;
                    x++;
                } else {
                    x--;
                }
            }
        }

        // If there is a shark which is smaller than current shark
        if (nextBoard[y][x][SIZE] < curSize) {
            nextBoard[y][x][SPEED] = curSpeed;
            nextBoard[y][x][DIR] = curDir;
            nextBoard[y][x][SIZE] = curSize;
        }
    }

    for(int row = 1; row <= R; row++) {
        for(int col = 1; col <= C; col++) {
            origin[row][col][SIZE] = 0;
            if(nextBoard[row][col][SIZE] > 0) {
                origin[row][col][SPEED] = nextBoard[row][col][SPEED];
                origin[row][col][DIR] = nextBoard[row][col][DIR];
                origin[row][col][SIZE] = nextBoard[row][col][SIZE];
                sharkPos.push(make_pair(row, col));
            }
        }
    }
}