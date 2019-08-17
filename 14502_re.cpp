#include <iostream>
#include <queue>
using namespace std;
//ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 8)
int N, M;
int map[8][8];
int copy_map[8][8]; //map ���� ����
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

	//�Ϻ� ĭ�� ���̷����� �����ϸ�, �� ���̷����� �����¿�� ������ �� ĭ���� ��� �������� �� �ִ�.
	//���� ���� �� �ִ� ���� ������ 3���̸�, �� 3���� ������ �Ѵ�.
	//���� 3�� ���� ��, ���̷����� ���� �� ���� ���� ���� �����̶�� �Ѵ�.

	//�����Ҵ� ũ�Ⱑ N��M�� ���簢������ ��Ÿ�� �� ������, ���簢���� 1��1 ũ���� ���簢������ �������� �ִ�.�����Ҵ� �� ĭ, ������ �̷���� ������, ���� ĭ �ϳ��� ���� �����Ѵ�.
	//��° �ٺ��� N���� �ٿ� ������ ����� �־�����. 0�� �� ĭ, 1�� ��, 2�� ���̷����� �ִ� ��ġ�̴�.
	//2�� ������ 2���� ũ�ų� ����, 10���� �۰ų� ���� �ڿ����̴�.
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

	//ù° �ٿ� ���� �� �ִ� ���� ������ �ִ� ũ�⸦ ����Ѵ�.

	cout << ans << "\n";

	return 0;
}