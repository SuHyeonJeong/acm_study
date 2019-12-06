#include <iostream>
#include <queue>
using namespace std;
//첫째 줄에 지도의 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 8)
int N, M;
int map[8][8];
int copy_map[8][8]; //map 원본 저장
bool visit[8][8];
queue <pair<int,int>> q;

int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int BFS()
{
	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= N || ny <0 || nx >= M || nx < 0) continue;

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

	//일부 칸은 바이러스가 존재하며, 이 바이러스는 상하좌우로 인접한 빈 칸으로 모두 퍼져나갈 수 있다.
	//새로 세울 수 있는 벽의 개수는 3개이며, 꼭 3개를 세워야 한다.
	//벽을 3개 세운 뒤, 바이러스가 퍼질 수 없는 곳을 안전 영역이라고 한다.

	//연구소는 크기가 N×M인 직사각형으로 나타낼 수 있으며, 직사각형은 1×1 크기의 정사각형으로 나누어져 있다.연구소는 빈 칸, 벽으로 이루어져 있으며, 벽은 칸 하나를 가득 차지한다.
	//둘째 줄부터 N개의 줄에 지도의 모양이 주어진다. 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 위치이다.
	//2의 개수는 2보다 크거나 같고, 10보다 작거나 같은 자연수이다.
	cin >> N >> M;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			cin >> map[y][x];
			copy_map[y][x] = map[y][x];

			if (map[y][x] == 2)
			{
				visit[y][x] = true;
				q.push(make_pair(y, x));
			}
		}
	}

	int ans = -1;
	for (int y1 = 0; y1 < N; y1++)
	{
		for (int x1 = 0; x1 < M; x1++)
		{
			if (map[y1][x1] != 0) continue;

			for (int y2 = 0; y2 < N; y2++)
			{
				for (int x2 = 0; x2 < M; x2++)
				{
					if (map[y2][x2] != 0) continue;
					if (y2 == y1 && x2 == x1) continue;

					for (int y3 = 0; y3 < N; y3++)
					{
						for (int x3 = 0; x3 < M; x3++)
						{
							if (map[y3][x3] != 0) continue;
							if (y3 == y1 && x3 == x1) continue;
							if (y3 == y2 && x3 == x2) continue;
							
							map[y3][x3] = map[y2][x2] = map[y1][x1] = 1;

							ans = max(BFS(), ans);

							for (int y = 0; y < N; y++)
							{
								for (int x = 0; x < M; x++)
								{
									map[y][x] = copy_map[y][x];
									visit[y][x] = false;
									if (map[y][x] == 2)
									{
										visit[y][x] = true;
										q.push(make_pair(y, x));
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력한다.

	cout << ans << "\n";

	return 0;
}