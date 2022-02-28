#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
const int MAX = 8;
int map[MAX][MAX];
int copy_map[MAX][MAX];
bool visit[MAX][MAX];
queue<pair<int, int>> q;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void print()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			cout << map[y][x] << " ";
		}
		cout << "\n";
	}
}

void reset()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			map[y][x] = copy_map[y][x];
			visit[y][x] = 0;
			if (map[y][x] == 2)
			{
				q.push(make_pair(y, x));
				visit[y][x] = 1;
			}
		}
	}
}

int BFS()
{
	//문제
	//인체에 치명적인 바이러스를 연구하던 연구소에서 바이러스가 유출되었다.다행히 바이러스는 아직 퍼지지 않았고, 바이러스의 확산을 막기 위해서 연구소에 벽을 세우려고 한다.

	//연구소는 크기가 N×M인 직사각형으로 나타낼 수 있으며, 직사각형은 1×1 크기의 정사각형으로 나누어져 있다.연구소는 빈 칸, 벽으로 이루어져 있으며, 벽은 칸 하나를 가득 차지한다.

	//일부 칸은 바이러스가 존재하며, 이 바이러스는 상하좌우로 인접한 빈 칸으로 모두 퍼져나갈 수 있다.새로 세울 수 있는 벽의 개수는 3개이며, 꼭 3개를 세워야 한다.


	//연구소의 지도가 주어졌을 때 얻을 수 있는 안전 영역 크기의 최댓값을 구하는 프로그램을 작성하시오.

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny < 0 || nx < 0 || ny >= N || nx >= M)
				continue;

			if (map[ny][nx] == 0 && !visit[ny][nx])
			{
				q.push(make_pair(ny, nx));
				map[ny][nx] = 2;
				visit[ny][nx] = 1;
			}
		}
	}

	int cnt = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			if (map[y][x] == 0)
				cnt++;
		}
	}

	return cnt;

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//입력
	//첫째 줄에 지도의 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 8)
	//둘째 줄부터 N개의 줄에 지도의 모양이 주어진다. 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 위치이다. 2의 개수는 2보다 크거나 같고, 10보다 작거나 같은 자연수이다.
	//빈 칸의 개수는 3개 이상이다.

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
				visit[y][x] = 1;
			}
		}
	}



	int answer = -1;
	for (int i1 = 0; i1 < N; i1++)
	{
		for (int j1 = 0; j1 < M; j1++)
		{
			if (map[i1][j1]) continue;

			for (int i2 = 0; i2 < N; i2++)
			{
				for (int j2 = 0; j2 < M; j2++)
				{
					if (i1 == i2 && j1 == j2) continue;
					if (map[i2][j2]) continue;

					for (int i3 = 0; i3 < N; i3++)
					{
						for (int j3 = 0; j3 < M; j3++)
						{
							if (i1 == i3 && j1 == j3) continue;
							if (i2 == i3 && j2 == j3) continue;
							if (map[i3][j3]) continue;

							map[i1][j1] = 1;
							map[i2][j2] = 1;
							map[i3][j3] = 1;

							answer = max(BFS(),answer);

							
							reset();

						}
					}
				}
			}
		}
	}



	

	//출력
	//첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력한다.

	cout << answer << "\n";


	return 0;
}