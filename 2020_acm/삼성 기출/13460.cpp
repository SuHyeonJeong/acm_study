//��, ���� ������ �Ķ� ������ ũ��� �� ĭ�� ��� �����Ѵ�.
//����̴� ������ �׸��ϴ� ���� �� �̻� ������ �������� ���� �� �����̴�.
//������ ���°� �־����� ��, �ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ���ϴ� ���α׷��� �ۼ�.
//������ ������ �� �� �̸�, ���� ������ �Ķ� ������ �׻� 1���� �־�����.
//�ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ����Ѵ�.
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

//�������� ����̱�, ���������� ����̱�, �������� ����̱�, �Ʒ������� ����̱�� ���� �� ���� ������ �����ϴ�.
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

		//����, 10�� ���Ϸ� �������� ���� ������ ������ ���� ���� �� ������ - 1�� ����Ѵ�.
		if (cur.cnt > 10) break;

		//���� �ϳ��� �� �ִ�.������ ��ǥ�� ���� ������ ������ ���ؼ� ������ ���̴�.
		//�̶�, �Ķ� ������ ���ۿ� ���� �� �ȴ�.
		//������ ���ۿ��� ���� ���ÿ� �����δ�.���� ������ ���ۿ� ������ ����������, �Ķ� ������ ���ۿ� ������ �����̴�.
		//���� ������ �Ķ� ������ ���ÿ� ���ۿ� ������ �����̴�.
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


			//�������� ������
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


			//�Ķ����� ������
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

			//���� ������ �Ķ� ������ ���ÿ� ���� ĭ�� ���� �� ����.
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
	//������ ���� ũ��� N, ���� ũ��� M�̰�, ���ǻ� 1��1ũ���� ĭ���� �������� �ִ�.
	cin >> N >> M;

	//���� N���� �ٿ� ������ ����� ��Ÿ���� ���� M�� ���ڿ��� �־�����.
	//�� ���ڿ��� '.', '#', 'O', 'R', 'B' �� �̷���� �ִ�.
	//'.'�� �� ĭ�� �ǹ��ϰ�, '#'�� ���� �̵��� �� ���� ��ֹ� �Ǵ� ���� �ǹ��ϸ�, 
	//'O'�� ������ ��ġ�� �ǹ��Ѵ�. 'R'�� ���� ������ ��ġ, 'B'�� �Ķ� ������ ��ġ�̴�.
	//�ԷµǴ� ��� ������ �����ڸ����� ��� '#'�� �ִ�
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