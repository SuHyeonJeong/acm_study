#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;
int N;
int cnt = 0;

const int dy[] = { -1,1,0,0 };
const int dx[] = { 0,0,-1,1 };

int map[100][100];
int copy_map[100][100];

bool visit[100][100];

void DFS(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
		if (copy_map[ny][nx] != -1 && !visit[ny][nx])
		{
			visit[ny][nx] = true;
			DFS(ny, nx);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	int mx = INT_MIN;
	int mn = INT_MAX;
	
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
			mx = max(mx, map[y][x]);
			mn = min(mn, map[y][x]);
		}
	}

	int ans = -1;
	for (int r = mn; r < mx + 1; r++)
	{
		cnt = 0;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				visit[y][x] = false;
				copy_map[y][x] = map[y][x];
				if (map[y][x] < r)
				{
					copy_map[y][x] = -1;
				}
			}
		}

		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (copy_map[y][x] != -1 && !visit[y][x])
				{
					visit[y][x] = true;
					DFS(y, x);
					cnt++;
				}
			}
		}

		if (ans < cnt)
		{
			ans = cnt;
		}
	}
	
	

	cout << ans << "\n";
	return 0; 
}