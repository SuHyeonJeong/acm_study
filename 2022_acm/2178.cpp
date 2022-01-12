#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, M;
const int MAX = 101;
int map[MAX][MAX];
bool visit[MAX][MAX];
queue<pair<int, int>> q;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void BFS() 
{
	
	//이러한 미로가 주어졌을 때, (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 
	//한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.
	//101111
	//101010
	//101011
	//111011
	//위의 예에서는 15칸을 지나야(N, M)의 위치로 이동할 수 있다.칸을 셀 때에는 시작 위치와 도착 위치도 포함한다.

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny > N || nx > M || ny < 1 || nx < 1)
				continue;

			if (map[ny][nx] && !visit[ny][nx])
			{
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
				map[ny][nx] = map[y][x] + 1;
			}
		}

		

	}

	cout << map[N][M] << "\n";

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	//N×M크기의 배열로 표현되는 미로가 있다.
	//미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 
	//입력
	//첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다.다음 N개의 줄에는 M개의 정수로 미로가 주어진다.각각의 수들은 붙어서 입력으로 주어진다.

	cin >> N >> M;

	for (int y = 1; y <= N; y++)
	{
		string str;
		cin >> str;

		for (int x = 1; x <= M; x++)
		{
			map[y][x] = str[x - 1] - '0';
		}
	}

	q.push(make_pair(1, 1));
	visit[1][1] = true;

	BFS();


	//출력
	//첫째 줄에 지나야 하는 최소의 칸 수를 출력한다.항상 도착위치로 이동할 수 있는 경우만 입력으로 주어진다.
	return 0;
}