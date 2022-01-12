#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int arr[21][21];
bool visit[21][21]; //�̹� �������� �� ������ �� ���� -> ǥ��
int ans = 0;

void move(int dir)
{
	queue <int> q;


	switch (dir)
	{
	case 0:
	{

		//up
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (arr[x][y])
					q.push(arr[x][y]);
				arr[x][y] = 0;
			}

			int idx = 0;

			while (!q.empty())
			{
				int data = q.front();
				q.pop();

				if (arr[idx][y] == 0)
				{
					arr[idx][y] = data;
				}
				else if (arr[idx][y] == data)
				{
					arr[idx][y] += data;
					idx++;
				}
				else
				{
					idx++;
					arr[idx][y] = data;
				}
			}
		}
		break;
		
	}
	case 1:
	{
		//down
		for (int y = 0; y < N; y++)
		{
			for (int x = N - 1; x >= 0; x--)
			{
				if (arr[x][y])
					q.push(arr[x][y]);
				arr[x][y] = 0;
			}
			int idx = N - 1;

			while (!q.empty())
			{
				int data = q.front();
				q.pop();

				if (arr[idx][y] == 0)
				{
					arr[idx][y] = data;
				}
				else if (arr[idx][y] == data)
				{
					arr[idx][y] += data;
					idx--;
				}
				else
				{
					idx--;
					arr[idx][y] = data;
				}
			}
		}
		break;
	}
	case 2:
	{
		//left
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (arr[y][x])
					q.push(arr[y][x]);
				arr[y][x] = 0;
			}
			int idx = 0;

			while (!q.empty())
			{
				int data = q.front();
				q.pop();

				if (arr[y][idx] == 0)
				{
					arr[y][idx] = data;
				}
				else if (arr[y][idx] == data)
				{
					arr[y][idx] += data;
					idx++;
				}
				else
				{
					idx++;
					arr[y][idx] = data;
				}
			}
		}
		break;
	}
	case 3:
	{
		//right
		for (int y = 0; y < N; y++)
		{
			for (int x = N-1; x >= 0; x--)
			{
				if (arr[y][x])
					q.push(arr[y][x]);
				arr[y][x] = 0;
			}
			int idx = N - 1;

			while (!q.empty())
			{
				int data = q.front();
				q.pop();

				if (arr[y][idx] == 0)
				{
					arr[y][idx] = data;
				}
				else if (arr[y][idx] == data)
				{
					arr[y][idx] += data;
					idx--;
				}
				else
				{
					idx--;
					arr[y][idx] = data;
				}
			}
		}
		break;
	}
	default:
		break;
	}
}
void dfs(int cnt)
{
	if (cnt == 5)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				ans = max(ans, arr[i][j]);
			}
		}
		return;
	}

	int temp[21][21];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			temp[i][j] = arr[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		move(i);
		dfs(cnt + 1);

		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				arr[y][x] = temp[y][x];
			}
		}

	}
	
	
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//�Է�
	//ù° �ٿ� ������ ũ�� N(1 �� N �� 20)�� �־�����.��° �ٺ��� N���� �ٿ��� �������� �ʱ� ���°� �־�����. 0�� �� ĭ�� ��Ÿ����, �̿��� ���� ��� ����� ��Ÿ����.��Ͽ� ���� �ִ� ���� 2���� ũ�ų� ����, 1024���� �۰ų� ���� 2�� �������̴�.����� ��� �ϳ� �־�����.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> arr[i][j];
		}
	}
	//���
	//�ִ� 5�� �̵����Ѽ� ���� �� �ִ� ���� ū ����� ����Ѵ�.

	dfs(0);
	cout << ans << "\n";
	return 0;

}