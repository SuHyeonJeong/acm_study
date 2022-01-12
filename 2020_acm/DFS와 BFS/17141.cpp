#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int dy[] = { -1,1,0,0 };
const int dx[] = { 0,0,-1,1 };

int N, M;
int ans = 10000;
int map[50][50];
int copy_map[50][50];

bool visit[50][50];
bool check[10];

vector <pair<int, int>> v; //바이러스 전부
queue <pair<int,int>> q; //선택된 바이러스

void BFS()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			copy_map[y][x] = map[y][x];
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

			if (ny >= N || ny < 0 || nx >= N || nx < 0) continue;
			if (map[ny][nx] == 0 && !visit[ny][nx])
			{
				copy_map[ny][nx] = copy_map[y][x] + 1;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}

		}
	}

	/*for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << map[y][x] << " ";
		}
		cout << "\n";
	}*/
}
void DFS(int idx, int cnt)
{
	if (cnt > M)
	{
		return;
	}

	if (cnt = M)
	{
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				copy_map[y][x] = -1;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (check[i])
			{
				copy_map[v[i].first][v[i].second];
				q.push(make_pair(v[i].first, v[i].second));
			}
		}

		BFS();

		bool flag = true;
		int mx=0;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (map[y][x] == 0)
				{
					flag = false;
					break;
				}
				else
				{
					mx = max(mx, copy_map[y][x]);
				}
			}
		}

		if (flag == true)
		{
			ans = min(ans, mx);
		}

		
	}

	for (int i = idx; i < v.size(); i++)
	{
		if (check[i] == true) continue;
		
		check[i] = true;
		DFS(i+1, cnt + 1);
		check[i] = false;
	}

}


int main()
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 2)
			{
				//q.push(make_pair(y, x));
				v.push_back(make_pair(y, x));
				visit[y][x] == true;
			}
		}
	}
	

	DFS(0, 0);

	if (ans == 10000)
	{
		ans = -1;
	}
	cout << ans << "\n";
	
	
	return 0;
}