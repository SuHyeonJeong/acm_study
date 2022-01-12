#include <iostream>
#include <string>
#include <queue>
using namespace std;

//미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다.
// (1, 1)에서 출발하여(N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오.
//한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.

int N, M;
int map[100][100];
bool visit[100][100];
int cnt = 0;

queue<pair<int, int>> q;

const int dy[] = { -1,1,0,0 };
const int dx[] = { 0,0,-1,1 };

void BFS()
{
	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny >= N || ny < 0 || nx >= M || nx < 0)continue;

			if (map[ny][nx] == 1 && !visit[ny][nx])
			{
				map[ny][nx] = map[y][x] + 1;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}

		}
		
	}

	/*for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			cout << map[y][x] << " ";
		}
		cout << "\n";
	}
	cout << "\n";*/

	cout << map[N-1][M-1] << "\n";
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;

	for (int y = 0; y < N; y++)
	{
		string str;
		cin >> str;

		for (int x = 0; x < M; x++)
		{
			map[y][x] = str[x] - '0';
		}

	}

	q.push(make_pair(0,0));
	visit[0][0] = true;
	BFS();


	return 0;
}