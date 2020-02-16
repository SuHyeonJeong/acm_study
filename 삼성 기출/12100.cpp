#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N;
int arr[21][21];
bool visit[21][21]; //이미 더해진건 또 더해질 수 없음 -> 표시
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
	//입력
	//첫째 줄에 보드의 크기 N(1 ≤ N ≤ 20)이 주어진다.둘째 줄부터 N개의 줄에는 게임판의 초기 상태가 주어진다. 0은 빈 칸을 나타내며, 이외의 값은 모두 블록을 나타낸다.블록에 쓰여 있는 수는 2보다 크거나 같고, 1024보다 작거나 같은 2의 제곱꼴이다.블록은 적어도 하나 주어진다.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> arr[i][j];
		}
	}
	//출력
	//최대 5번 이동시켜서 얻을 수 있는 가장 큰 블록을 출력한다.

	dfs(0);
	cout << ans << "\n";
	return 0;

}