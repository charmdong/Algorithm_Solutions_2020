

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Tree {
    int row, col;
    int age;
    bool isDead;

    Tree(int y, int x, int age, bool dead) : row(y), col(x), age(age), isDead(dead) {}
};

int N, M, K;
vector<vector<int> > nutrient, A;
vector<Tree> treeList;

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct cmp {
    bool operator()(const Tree &t1, const Tree& t2) {
        if(t1.row == t2.row) {
            if(t1.col == t2.col) {
                return t1.age > t2.age;
            } else {
                return t1.col > t2.col;
            }
        } else {
            return t1.row > t2.row;
        }
    } 
};

int bfs();

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;
    nutrient.assign(N + 1, vector<int>(N + 1, 5));
    A.assign(N + 1, vector<int>(N + 1, 0));

    for(int row = 1; row <= N; row++) {
        for(int col = 1; col <= N; col++) {
            cin >> A[row][col];
        }
    }

    int x, y, age;
    for(int index = 0; index < M; index++) {
        cin >> y >> x >> age;
        treeList.push_back(Tree(y, x, age, false));
    }
    
    cout << bfs() << endl;

    return 0;
}

int bfs() {
    priority_queue<Tree, vector<Tree>, cmp> q;
    queue<Tree> tmp;

    for(Tree t : treeList) {
        q.push(t);
    }

    while(K > 0 && !q.empty()) {
        // Spring (q -> tmp)
        while(!q.empty()) {
            Tree cur = q.top();
            int curRow = cur.row;
            int curCol = cur.col;
            int curAge = cur.age;
            q.pop();

            if(nutrient[curRow][curCol] >= curAge) {
                nutrient[curRow][curCol] -= curAge;
                tmp.push(Tree(curRow, curCol, curAge + 1, false));
            } else {
                tmp.push(Tree(curRow, curCol, 0, true));
            }
        }

        // Summer (tmp -> tmp)
        int treeCnt = tmp.size();
        for(int index = 0; index < treeCnt; index++) {
            Tree cur = tmp.front();
            int curRow = cur.row;
            int curCol = cur.col;
            int curAge = cur.age;
            bool isDead = cur.isDead;
            tmp.pop();

            if(isDead) {
                nutrient[curRow][curCol] += (curAge / 2);
            } else {
                tmp.push(cur);
            }
        }

        // Fall (tmp -> q)
        while(!tmp.empty()) {
            Tree cur = tmp.front();
            int curRow = cur.row;
            int curCol = cur.col;
            int curAge = cur.age;
            tmp.pop();

            if(curAge % 5 == 0) {
                for(int dir = 0; dir < 8; dir++) {
                    int ny = curRow + dy[dir];
                    int nx = curCol + dx[dir];

                    if(ny > 0 && ny <= N && nx > 0 && nx <= N) {
                        q.push(Tree(ny, nx, 1, false));
                    }
                }
            }
            q.push(cur);
        }

        // Winter
        for(int row = 1; row <= N; row++) {
            for(int col = 1; col <= N; col++) {
                nutrient[row][col] += A[row][col];
            }
        }
        K--;
    }
    
    return q.size();
}