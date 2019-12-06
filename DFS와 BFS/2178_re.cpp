#include <iostream>
#include <string>
#include <queue>
using namespace std;
int map[101][101];
bool visit[101][101];
int N, M;
queue<pair<int, int>> q;

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

void BFS()
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

			if (ny > N || ny <0 || nx >M || nx < 0) continue;
			if (!visit[ny][nx] && map[ny][nx])
			{
				map[ny][nx] = map[y][x] + 1; //지나야하는 칸 수 세기 위해
				visit[ny][nx] = true;
				q.push(make_pair(ny, nx));
			}
		}
	}

	cout << map[N - 1][M - 1] << "\n";
}
int main()
{
	//1은 이동할 수 있는칸, 0은 이동할 수 없는 칸
	//(1,1)->[0][0]에서 출발, (N,M)까지 이동
	//지나야하는 최소 칸 수 출력

	ios_base::sync_with_stdio(false);
	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		string str;
		cin >> str;
		for (int x = 0; x < M; x++)
		{
			map[y][x] = str[x]-'0';
		}
	}

	q.push(make_pair(0, 0));
	visit[0][0] = true;

	BFS();
	
	return 0;
}