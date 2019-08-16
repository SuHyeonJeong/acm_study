//또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다.
//기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.
//보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성.
//구멍의 개수는 한 개 이며, 빨간 구슬과 파란 구슬은 항상 1개가 주어진다.
//최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력한다.
#include <iostream>
#include <queue>
using namespace std;
struct INFO
{
	int ry, rx, by, bx, cnt;
};

INFO start;
int N, M;
char map[10][11];
int visit[10][10][10][10]; //ry,rx,by,bx visit

//왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int BFS()
{
	queue<INFO> q;
	q.push(start);
	visit[start.ry][start.rx][start.by][start.bx] = 1;

	int ret = -1;

	while (!q.empty())
	{
		INFO cur = q.front();
		q.pop();

		//만약, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 - 1을 출력한다.
		if (cur.cnt > 10) break;

		//각각 하나씩 들어가 있다.게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다.
		//이때, 파란 구슬이 구멍에 들어가면 안 된다.
		//각각의 동작에서 공은 동시에 움직인다.빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다.
		//빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다.
		if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O')
		{
			ret = cur.cnt;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int n_ry = cur.ry;
			int n_rx = cur.rx;
			int n_by = cur.by;
			int n_bx = cur.bx;


			//빨간공의 움직임
			while (1)
			{
				if (map[n_ry][n_rx] != '#' && map[n_ry][n_rx] != 'O')
				{
					n_ry += dy[i];
					n_rx += dx[i];
				}
				else
				{
					if (map[n_ry][n_rx] == '#')
					{
						n_ry -= dy[i];
						n_rx -= dx[i];
					}
					break;
				}
			}


			//파란공의 움직임
			while (1)
			{
				if (map[n_by][n_bx] != '#' && map[n_by][n_bx] != 'O')
				{
					n_by += dy[i];
					n_bx += dx[i];
				}
				else
				{
					if (map[n_by][n_bx] == '#')
					{
						n_by -= dy[i];
						n_bx -= dx[i];
					}
					break;
				}
			}

			//빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다.
			if (n_ry == n_by && n_rx == n_bx)
			{
				if (map[n_ry][n_rx] != 'O')
				{
					int red_dist = abs(n_ry - cur.ry) + abs(n_rx - cur.rx);
					int blue_dist = abs(n_by - cur.by) + abs(n_bx - cur.bx);

					if (red_dist > blue_dist)
					{
						n_ry -= dy[i];
						n_rx -= dx[i];
					}
					else
					{
						n_by -= dy[i];
						n_bx -= dx[i];
					}

				}

				
			}
			if (visit[n_ry][n_rx][n_by][n_bx] == 0)
			{
				visit[n_ry][n_rx][n_by][n_bx] = 1;
				INFO next;
				next.ry = n_ry;
				next.rx = n_rx;
				next.by = n_by;
				next.bx = n_bx;
				next.cnt = cur.cnt + 1;
				q.push(next);
			}
		}
	}

	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다.
	cin >> N >> M;

	//다음 N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열이 주어진다.
	//이 문자열은 '.', '#', 'O', 'R', 'B' 로 이루어져 있다.
	//'.'은 빈 칸을 의미하고, '#'은 공이 이동할 수 없는 장애물 또는 벽을 의미하며, 
	//'O'는 구멍의 위치를 의미한다. 'R'은 빨간 구슬의 위치, 'B'는 파란 구슬의 위치이다.
	//입력되는 모든 보드의 가장자리에는 모두 '#'이 있다
	for (int y = 0; y < N; y++)
	{
		cin >> map[y];
	}

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			if (map[y][x] == 'R')
			{
				start.ry = y;
				start.rx = x;
			}
			else if (map[y][x] == 'B')
			{
				start.by = y;
				start.bx = x;
			}
		}
	}

	start.cnt = 0;

	int ret = BFS();
	cout << ret << "\n";
	return 0;
}