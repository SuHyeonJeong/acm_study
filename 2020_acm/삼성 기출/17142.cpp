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

vector<pair<int, int>> v; //활성화 바이러스
queue<pair<int, int>> q; //전체 바이러스

int answer = INT_MAX;

void DFS(int idx, int cnt)
{
	if (cnt > M)	return;

	//M만큼 활성화 바이러스 만들었을 때
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
				//빈칸인데 바이러스 퍼지지 않았을 경우
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

		//최소시간
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

	//입력
	//첫째 줄에 연구소의 크기 N(4 ≤ N ≤ 50), 놓을 수 있는 바이러스의 개수 M(1 ≤ M ≤ 10)이 주어진다.

	//둘째 줄부터 N개의 줄에 연구소의 상태가 주어진다.
	//0은 빈 칸, 1은 벽, 2는 바이러스를 놓을 수 있는 위치이다. 
	//2의 개수는 M보다 크거나 같고, 10보다 작거나 같은 자연수이다.
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


	//출력
	//연구소의 모든 빈 칸에 바이러스가 있게 되는 최소 시간을 출력한다.
	//바이러스를 어떻게 놓아도 모든 빈 칸에 바이러스를 퍼뜨릴 수 없는 경우에는 - 1을 출력한다.
	return 0;
}
