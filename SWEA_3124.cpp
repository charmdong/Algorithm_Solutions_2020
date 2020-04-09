/**
 * @author : donggun.chung
 * @date : 2020. 04. 09
 * @site : SWEA
 * @probInfo : 3124 최소 스패닝 트리
 * @time : 5,388ms
 * @memory : 24,116kb
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, V, E;
vector<vector<int> > edgeList;
vector<int> parent;

bool compare(const vector<int>& v1, const vector<int>& v2) {
	return v1[2] < v2[2];
}

void makeSet(int index);
int findSet(int index);
bool unionSet(int src, int des);

int main()
{
	ios_base ::sync_with_stdio(false);
	
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> T;
	for(int test = 1; test <= T; test++) {
		cin >> V >> E;
		parent.assign(V + 1, 0);
		edgeList.assign(E, vector<int>(3, 0));
		
		for(int index = 1; index <= V; index++) makeSet(index);
		
		for(int index = 0; index < E; index++) {
			cin >> edgeList[index][0] >> edgeList[index][1] >> edgeList[index][2];
		}
		
		sort(edgeList.begin(), edgeList.end(), compare);
		
		long answer = 0;
		int edgeCnt = 0;
		for(auto edge : edgeList) {
			if(unionSet(edge[0], edge[1])) {
				answer += edge[2];
				if(++edgeCnt == V - 1) break;
			}
		}
		
		cout << "#" << test << " " << answer << endl;
	}
	
	return 0;
}

void makeSet(int index) {
	parent[index] = index;
}

int findSet(int index) {
	if(parent[index] == index) return index;
	else return (parent[index] = findSet(parent[index]));
}

bool unionSet(int src, int des) {
	int ps = findSet(src);
	int pd = findSet(des);
	
	if(ps != pd) {
		parent[ps] = pd;
		return true;
	}
	
	return false;
}
