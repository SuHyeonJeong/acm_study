#include <iostream>
using namespace std;

int map[50][50];
bool visit[50][50];

int w, h;

const int dy[] = { -1,1,0,0,-1,-1,1,1 };
const int dx[] = { 0,0,-1,1,1,-1,1,-1 };

void DFS(int y, int x)
{
	for (int dir = 0; dir < 8; dir++)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny >= h || ny < 0 || nx >= w || nx < 0) continue;
		if (map[ny][nx] && !visit[ny][nx])
		{
			visit[ny][nx] = true;
			DFS(ny, nx);
		}
	}
}
int main()
{
	while (1)
	{
		
		int cnt = 0;
		cin >> w >> h;

		if (w == 0 && h == 0)
		{
			break;
		}

		
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				cin >> map[y][x];
				visit[y][x] = false;
			}
		}

		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				if (map[y][x] && !visit[y][x])
				{
					visit[y][x] = true;
					DFS(y, x);
					cnt++;
				}
			}
		}

		cout << cnt << "\n";
	}

	return 0;
}