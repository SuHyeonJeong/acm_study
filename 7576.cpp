#include <iostream>
#include <queue>
using namespace std;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };
int N, M;
const int MAX = 1001;
int map[MAX][MAX];
queue <pair<int, int>> q;
int blank = 0;

int BFS()
{
	int cnt = 0;

	if (q.empty())
	{
		return -1;
	}

	while (!q.empty())
	{
		cnt++;
		int y = q.front().first;
		int x = q.front().second;

		for (int j = 0; j < 4; j++)
		{
			int next_y = y + dy[j];
			int next_x = x + dx[j];

			if (next_y >= 0 && next_y < N && next_x >= 0 && next_x < M && map[next_y][next_x] == 0)
			{
				map[next_y][next_x] = 1;
				q.push(make_pair(next_y, next_x));
			}
		}

		for (int s = 0; s < N; s++)
		{
			for (int t = 0; t < M; t++)
			{
				cout << map[s][t] << " ";
			}
			cout << endl;
		}
		cout << endl;

		q.pop();

		if (q.size() == 0)
		{
			int tomato_cnt = 0;
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (map[i][j] == 1)
					{
						tomato_cnt++;
					}
				}
			}
			if (tomato_cnt == N * M - blank)
			{
				return cnt;
			}
			else
			{
				return -1;
			}
		}
	
	}
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
			else if (map[i][j] == -1)
			{
				blank++;
			}
		}
	}


	cout << BFS();
	return 0;
}