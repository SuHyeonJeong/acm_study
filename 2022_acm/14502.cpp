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
	//����
	//��ü�� ġ������ ���̷����� �����ϴ� �����ҿ��� ���̷����� ����Ǿ���.������ ���̷����� ���� ������ �ʾҰ�, ���̷����� Ȯ���� ���� ���ؼ� �����ҿ� ���� ������� �Ѵ�.

	//�����Ҵ� ũ�Ⱑ N��M�� ���簢������ ��Ÿ�� �� ������, ���簢���� 1��1 ũ���� ���簢������ �������� �ִ�.�����Ҵ� �� ĭ, ������ �̷���� ������, ���� ĭ �ϳ��� ���� �����Ѵ�.

	//�Ϻ� ĭ�� ���̷����� �����ϸ�, �� ���̷����� �����¿�� ������ �� ĭ���� ��� �������� �� �ִ�.���� ���� �� �ִ� ���� ������ 3���̸�, �� 3���� ������ �Ѵ�.


	//�������� ������ �־����� �� ���� �� �ִ� ���� ���� ũ���� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

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

	//�Է�
	//ù° �ٿ� ������ ���� ũ�� N�� ���� ũ�� M�� �־�����. (3 �� N, M �� 8)
	//��° �ٺ��� N���� �ٿ� ������ ����� �־�����. 0�� �� ĭ, 1�� ��, 2�� ���̷����� �ִ� ��ġ�̴�. 2�� ������ 2���� ũ�ų� ����, 10���� �۰ų� ���� �ڿ����̴�.
	//�� ĭ�� ������ 3�� �̻��̴�.

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



	

	//���
	//ù° �ٿ� ���� �� �ִ� ���� ������ �ִ� ũ�⸦ ����Ѵ�.

	cout << answer << "\n";


	return 0;
}