#include <iostream>
#include <algorithm>
#include <queue>
typedef pair<int, pair<int, int >> pa;

const int MAX = 101;
const int dy[] = { -1,1,0,0,0,0 };
const int dx[] = { 0,0,-1,1,0,0 };
const int dz[] = { 0,0,0,0,-1,1 };
int N, M, H, map[MAX][MAX][MAX];

queue<pa> q;

using namespace std;
int main()
{
	cin >> M >> N >> H;
	for (int z = 0; z < H; z++)
	{
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < M; x++)
			{
				cin >> map[z][y][x];
			}
		}
	}

	for (int z = 0; z < H; z++)
	{
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < M; x++)
			{
				cout << map[z][y][x] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}