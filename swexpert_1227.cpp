#include <iostream>
#include <string>
#include <queue>
using namespace std;

int map[100][100];
bool visit[100][100];

bool check;

const int dy[] = { -1,1,0,0 };
const int dx[] = { 0,0,-1,1 };

queue<pair<int, int>> q;
/*
void DFS(int y, int x)
{

	for (int dir = 0; dir < 4; dir++)
	{
		visit[y][x] = true;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (map[ny][nx] == 3)
		{
			check = true;
		}

		if (!visit[ny][nx] && map[ny][nx] == 0)
		{
			DFS(ny, nx);
		}
		visit[y][x] = false;



	}
}*/

void BFS()
{
	check = false;

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;


		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny >= 100 || ny < 0 || nx >= 100 || nx < 0) continue;

			if (map[ny][nx] == 3)
			{
				check = true;
			}

			if (!visit[ny][nx] && map[ny][nx] == 0)
			{
				map[ny][nx] == 2;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}
		}
	}
}
int main()
{
	for (int i = 0; i < 10; i++)
	{
		check = 0;
		char n;
		cin >> n;

		for (int y = 0; y < 100; y++)
		{
			for (int x = 0; x < 100; x++)
			{
				visit[y][x] = false;
			}
		}

		for (int y = 0; y < 100; y++)
		{
			char str[100];
			cin >> str;
			for (int x = 0; x < 100; x++)
			{
				map[y][x] = str[x] - '0';
				if (map[y][x] == 2)
				{
					q.push(make_pair(y, x));
					visit[y][x] = true;
				}
			}

		}

		cout << "#" << i + 1 << " ";
		BFS();
		cout << check << "\n";
	}
	return 0;
}