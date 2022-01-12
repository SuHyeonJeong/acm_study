#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };
int N, M;
const int MAX = 1001;
int map[MAX][MAX];
queue <pair<int, int>> q;

int BFS()
{

	if (q.empty())
	{
		return -1;
	}

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();


		for (int j = 0; j < 4; j++)
		{
			int next_y = y + dy[j];
			int next_x = x + dx[j];

			if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < M && map[next_y][next_x] == 0)
			{
				map[next_y][next_x] = map[y][x] + 1;
				q.push(make_pair(next_y, next_x));
			}
		}


		
	
	}
	
	int mx = -1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 0)
			{
				return -1;
			}
			mx = max(mx, map[i][j]);
		}
	}

	return mx - 1;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> M >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
			{
				q.push(make_pair(i,j));
			}
			
		}
	}


	cout << BFS() << "\n";
	return 0;
}