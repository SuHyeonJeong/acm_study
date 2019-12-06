#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, M;

int map[8][8];
int copy_map[8][8]; // ¿øº»
bool visit[8][8];
int flag = 0;

queue <pair<int, int>> q;

const int dy[] = { -1,1,0,0 };
const int dx[] = { 0,0,-1,1 };

int BFS()
{
	
	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny >= N || ny < 0 || nx >= M || nx < 0) continue;

			if (map[ny][nx] == 0 && !visit[ny][nx])
			{
				map[ny][nx] = 2;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}
		}
	}

	int cnt = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			if (map[y][x] == 0)
			{
				cnt++;
			}
		}
	}

	return cnt;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			cin >> map[y][x];
			copy_map[y][x] = map[y][x];

			if (map[y][x] == 2)
			{
				q.push(make_pair(y, x));
				visit[y][x] = true;
			}
		}
	}

	/*for (int y = 0; y < N; ++y) {
		for (int x = 0; x < M; ++x) {
			cout << map[y][x] << " ";
		}
		cout << endl;
	}*/

	int answer = -1;

	for (int y1 = 0; y1 < N; y1++)
	{
		for (int x1 = 0; x1 < M; x1++)
		{
			if (map[y1][x1] != 0) continue;
			for (int y2 = 0; y2 < N; y2++)
			{
				for (int x2 = 0; x2 < M; x2++)
				{
					if (y1 == y2 && x1 == x2) continue;
					if (map[y2][x2] != 0) continue;

					for (int y3 = 0; y3 < N; y3++)
					{
						for (int x3 = 0; x3 < M; x3++)
						{
							if (y3 == y1 && x3 == x1) continue;
							if (y3 == y2 && x3 == x2) continue;
							if (map[y3][x3] != 0) continue;
							map[y1][x1] = map[y2][x2] = map[y3][x3] = 1;

							answer = max(BFS(), answer);

							//map[y1][x1] = map[y2][x2] = map[y3][x3] = 0;

							
							for (int y = 0; y < N; y++)
							{
								for (int x = 0; x < M; x++)
								{
									map[y][x] = copy_map[y][x];
									visit[y][x] = false;
									if (map[y][x] == 2)
									{
										q.push(make_pair(y, x));

										visit[y][x] = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << answer << "\n";
	
	return 0;
}