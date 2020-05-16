
#include <iostream>
#include <vector>

using namespace std;

int T, N, M, answer, daily;
vector<vector<int> > board;
vector<bool> visited;
vector<pair<char, pair<int, int> > > infoList;
vector<int> route, res;

void printBoard()
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

void dfs(int day, int curPos, int totalTime, int satisfaction, int total);

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> N >> M;

        board.assign(N, vector<int>(N, 0));
        visited.assign(N, false);
        infoList.assign(N, make_pair('\0', make_pair(0, 0)));

        for(int row = 0; row < N - 1; row++) {
            for(int col = row + 1; col < N; col++) {
                cin >> board[row][col];
                board[col][row] = board[row][col];
            }
        }

        for(int index = 0; index < N; index++) {
            cin >> infoList[index].first;

            if(infoList[index].first == 'P') {
                cin >> infoList[index].second.first >> infoList[index].second.second;
            }
        }

        dfs(1, 0, 0, 0, 0);
        cout << answer << endl;
        for(int r : res) {
            cout << r << " ";
        }
        cout << endl;
    }

    return 0;
}

void dfs(int day, int curPos, int spendTime, int satisfaction, int total) {
    if(spendTime > 540) {
        return;
    }

    // 마지막 날이 아니고, 도착 장소가 호텔인 경우 (하루 일정이 마무리 됨)
    if(day < M) {
        if(infoList[curPos].first == 'H') {
            for(int next = 0; next < N; next++) {
                if(infoList[next].first == 'P' && !visited[next]) {
                    dfs(day + 1, next, board[curPos][next], 0, total + satisfaction);
                }
            }

            return;
        }
    } 
    // 마지막 날이고, 도착 장소가 공항인 경우 (여행이 끝남)
    else {
        if(infoList[curPos].first == 'A') {
            if(answer < total) {
                answer = total;
                res = route;
            }
            for(int r : route) {
                cout << r << " ";
            }
            cout << endl;
        }

        return;
    }

    visited[curPos] = true;
    route.push_back(curPos);

    for(int next = 0; next < N; next++) {
        int time = board[curPos][next];

        if(next == curPos) continue;
        // 다음 장소가 관광 포인트인 경우
        if(infoList[next].first == 'P') {
            if(!visited[next]) {
                dfs(day, next, spendTime + time + infoList[curPos].second.first, satisfaction + infoList[curPos].second.second, total);
            }
        } 
        // 다음 장소가 호텔이나 공항인 경우
        else {
            dfs(day, next, spendTime + time, satisfaction, total);
        }
    }

    route.pop_back();
    visited[curPos] = false;
}