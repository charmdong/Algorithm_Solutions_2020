
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
    ios_base ::sync_with_stdio(false);
    
    cin.tie(NULL);
    cout.tie(NULL);

    int t, sy, sx, dy, dx;
    cin >> t;
    for(int test = 1; test <= t; test++) {
        cin >> sy >> sx >> dy >> dx;
        
        int rDiff = abs(sy - dy);
        int cDiff = abs(sx - dx);

        cout << "#" << test << " " << ((rDiff + cDiff) % 2 == 0 ? max(rDiff, cDiff) * 2 : max(rDiff, cDiff) * 2 - 1) << endl; 
    }

    return 0;
}