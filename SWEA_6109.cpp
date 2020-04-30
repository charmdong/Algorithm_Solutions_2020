/**
 * @author : donggun.chung
 * @date : 2020. 05. 01
 * @site : SWEA
 * @probInfo : 6109 추억의 2048게임
 * @time : 228ms
 * @memory : 12,708KB
 */ 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int T, N;
vector<vector<int> > board;
vector<vector<bool> > merged;

void move(string dir);
void printBoard();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    string direction;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> direction;

        board.assign(N, vector<int>(N, 0));
        merged.assign(N, vector<bool>(N, false));
        for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
                cin >> board[row][col];
            }
        }

        move(direction);
        cout << "#" << test << endl;
        printBoard();
    }

    return 0;
}

void move(string direction) {
    if(direction == "left") {
        for(int row = 0; row < N; row++) {
            for(int col = 1; col < N; col++) {
                if(board[row][col] == 0) continue;
                
                for(int next = col - 1; next >= 0; next--) {
                    if(board[row][next] == 0) {
                        board[row][next] = board[row][next + 1];
                        board[row][next + 1] = 0;
                    } else {
                        if(board[row][next] == board[row][next + 1] && !merged[row][next]) {
                            board[row][next] *= 2;
                            board[row][next + 1] = 0;
                            merged[row][next] = true;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    } else if(direction == "right") {
        for(int row = 0; row < N; row++) {
            for(int col = N - 2; col >= 0; col--) {
                if(board[row][col] == 0) continue;

                for(int next = col + 1; next < N; next++) {
                    // 다음 칸이 비어있는 경우
                    if(board[row][next] == 0) {
                        board[row][next] = board[row][next - 1];
                        board[row][next - 1] = 0;
                    } 
                    // 다음 칸이 비어있지 않은 경우
                    else {
                        // 다음 칸이 같은 숫자이면서 합칠 수 있는 경우
                        if(board[row][next] == board[row][next - 1] && !merged[row][next]) {
                            board[row][next] *= 2;
                            board[row][next - 1] = 0;
                            merged[row][next] = true;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    } else if(direction == "up") {
        for(int col = 0; col < N; col++) {
            for(int row = 1; row < N; row++) {
                if(board[row][col] == 0) continue;

                for(int next = row - 1; next >= 0; next--) {
                    if(board[next][col] == 0) {
                        board[next][col] = board[next + 1][col];
                        board[next + 1][col] = 0;
                    } else {
                        if(board[next][col] == board[next + 1][col] && !merged[next][col]) {
                            board[next][col] *= 2;
                            board[next + 1][col] = 0;
                            merged[next][col] = true;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    } else {
        for(int col = 0; col < N; col++) {
            for(int row = N - 2; row >= 0; row--) {
                if(board[row][col] == 0) continue;

                for(int next = row + 1; next < N; next++) {
                    if(board[next][col] == 0) {
                        board[next][col] = board[next - 1][col];
                        board[next - 1][col] = 0;
                    } else {
                        if(board[next][col] == board[next - 1][col] && !merged[next][col]) {
                            board[next][col] *= 2;
                            board[next - 1][col] = 0;
                            merged[next][col] = true;
                            break;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void printBoard() {
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}