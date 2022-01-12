#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
using namespace std;

int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };

int N, M;
int map[51][51];
int copy_map[51][51];

bool check[51] = { false, };

vector<pair<int, int>> v; //Ȱ��ȭ ���̷���
queue<pair<int, int>> q; //��ü ���̷���

int answer = INT_MAX;

void DFS(int idx, int cnt)
{
	if (cnt > M)	return;

	//M��ŭ Ȱ��ȭ ���̷��� ������� ��
	if (cnt == M)
	{
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				copy_map[y][x] = -1;
			}
		}

		for (int i = 0; i < 51; i++)
		{
			if (check[i])
			{
				copy_map[v[i].first][v[i].second] = 0;
				q.push(make_pair(v[i].first, v[i].second));
			}
		}

		while (!q.empty())
		{
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int dir = 0; dir < 4; dir++)
			{
				int ny = y + dy[dir];
				int nx = x + dx[dir];
				
				if (ny >= N || nx >= N || ny < 0 || nx < 0)
					continue;

				if (map[ny][nx] != 1 && copy_map[ny][nx] == -1)
				{
					copy_map[ny][nx] = copy_map[y][x] + 1;
					q.push(make_pair(ny, nx));
				}
			}

		}

		bool isClear = true;
		int maxtime = 0;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				//��ĭ�ε� ���̷��� ������ �ʾ��� ���
				if (map[y][x] == 0)
				{
					if (copy_map[y][x] == -1)
					{
						isClear = false;
						break;
					}
					else
					{
						maxtime = max(maxtime, copy_map[y][x]);
					}
				}
				
			}
		}

		//�ּҽð�
		if (isClear)
		{
			answer = min(answer, maxtime);
		}
	}

	for (int i = idx; i < v.size(); i++)
	{
		check[i] = true;
		DFS(i + 1, cnt + 1);
		check[i] = false;
	}


}
int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);

	//�Է�
	//ù° �ٿ� �������� ũ�� N(4 �� N �� 50), ���� �� �ִ� ���̷����� ���� M(1 �� M �� 10)�� �־�����.

	//��° �ٺ��� N���� �ٿ� �������� ���°� �־�����.
	//0�� �� ĭ, 1�� ��, 2�� ���̷����� ���� �� �ִ� ��ġ�̴�. 
	//2�� ������ M���� ũ�ų� ����, 10���� �۰ų� ���� �ڿ����̴�.
	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 2)
			{
				v.push_back(make_pair(y, x));
			}
		}
	}

	DFS(0, 0);

	if (answer == INT_MAX)
	{
		answer = -1;
	}

	cout << answer << "\n";


	//���
	//�������� ��� �� ĭ�� ���̷����� �ְ� �Ǵ� �ּ� �ð��� ����Ѵ�.
	//���̷����� ��� ���Ƶ� ��� �� ĭ�� ���̷����� �۶߸� �� ���� ��쿡�� - 1�� ����Ѵ�.
	return 0;
}
