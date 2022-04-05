#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int R, C, K, W;
int chocolate = 0;
const int MAX = 21;

struct heater
{
	int y, x, d;
};

int temperature_map[400][MAX][MAX]; // �� ��ǳ�⿡�� ���� �ٶ� ���� ����
int sum_map[MAX][MAX]; // �� ��ǳ�⿡�� ���� �ٶ� �ջ��� ��

vector<heater> heater_list; //heater ����(��ǥ, ����) ������ list
vector<pair<int, int>> check_list; //�������� check �ؾ��ϴ� ��ǥ ������ list
vector<int> wall_map[MAX][MAX]; //�� ���� ������ 3���� vector -> �ش� ��ǥ�� 0�� 1�� �������� �� ���� ����

queue<pair<int, int>> q;


//��, ��, ��, �Ʒ� : ��ǳ�� ����=d
const int dy[5] = { 0,0,0,-1,1 };
const int dx[5] = { 0,1,-1,0,0 };

//��ǳ�� ���⿡ ���� �ٶ� ������ 3���� : 
const int wind_dy[5][3] = { {0,0,0}, {-1,0,1}, {-1,0,1}, {-1,-1,-1}, {1,1,1} };
const int wind_dx[5][3] = { {0,0,0}, {1,1,1}, {-1,-1,-1}, {-1,0,1}, {-1,0,1} };

void print()
{
	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			cout << sum_map[y][x] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void BFS(int n, int initial_y, int initial_x, int d)
{

	bool visit[MAX][MAX] = { false, };
	int wind = 4;



	while (!q.empty())
	{
		if (wind == 0)
			break;

		int y = q.front().first;
		int x = q.front().second;
		q.pop();


		for (int dir = 0; dir < 3; dir++)
		{
			int ny = y + wind_dy[d][dir];
			int nx = x + wind_dx[d][dir];

			if (ny > R || nx > C || ny < 1 || nx < 1)	continue;

			// �� ������ continue.[y - 1][x], [y + 1][x]�� �˻��ؾ���
			bool flag = false;

			if (d == 1)
			{
				if (dir == 0)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 0)
							flag = true;
					}

					for (int i = 0; i < wall_map[y - 1][x].size(); i++)
					{
						if (wall_map[y - 1][x][i] == 1)
							flag = true;
					}
				}

				if (dir == 1)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 1)
							flag = true;
					}
				}

				if (dir == 2)
				{
					for (int i = 0; i < wall_map[y + 1][x].size(); i++)
					{
						if (wall_map[y + 1][x][i] == 0 || wall_map[y + 1][x][i] == 1)
							flag = true;
					}
				}
			}

			else if (d == 2)
			{
				if (dir == 0)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 0)
							flag = true;
					}
					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 1)
							flag = true;
					}
				}

				if (dir == 1)
				{
					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 1)
							flag = true;
					}
				}

				if (dir == 2)
				{
					for (int i = 0; i < wall_map[y + 1][x].size(); i++)
					{
						if (wall_map[y + 1][x][i] == 0)
							flag = true;
					}

					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 1)
							flag = true;
					}
				}
			}

			else if (d == 3)
			{

				if (dir == 0)
				{

					for (int i = 0; i < wall_map[y][x - 1].size(); i++)
					{
						if (wall_map[y][x - 1][i] == 0 || wall_map[y][x - 1][i] == 1)
							flag = true;
					}
				}

				if (dir == 1)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 0)
							flag = true;
					}
				}

				if (dir == 2)
				{
					for (int i = 0; i < wall_map[y][x + 1].size(); i++)
					{
						if (wall_map[y][x + 1][i] == 0)
							flag = true;
					}
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 1)
							flag = true;
					}
				}
			}

			else
			{

				if (dir == 0)
				{
					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 0)
							flag = true;
					}
					for (int i = 0; i < wall_map[y][x - 1].size(); i++)
					{
						if (wall_map[y][x - 1][i] == 1)
							flag = true;
					}

				}

				if (dir == 1)
				{
					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 0)
							flag = true;
					}
				}

				if (dir == 2)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 1)
							flag = true;
					}

					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 0)
							flag = true;
					}
				}
			}

			if (flag)	continue;


			if (!visit[ny][nx])
			{
				//�ٶ� ���� ����
				if (d == 3 || d == 4)
					wind = 5 - abs(initial_y - ny);
				else
					wind = 5 - abs(initial_x - nx);


				temperature_map[n][ny][nx] = wind;
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
			}

		}

	}

}

void work_heater()
{
	//���� �ִ� ��� ��ǳ�⿡�� �ٶ��� �� �� ������ ������ �����ϸ� ������ ����.
	//<�׸� 1>�� ũ�Ⱑ 7��8�� ���� ��ǳ�Ⱑ (3, 1)�� ��ġ�Ǿ� �ִ� ��Ȳ�̴�. ��ǳ��� �ٶ��� ������ ������ �ִµ�, �� ������ ������, ����, ��, �Ʒ� �� �ϳ��̴�. 
	//��ǳ�⿡�� ������ �ٶ��� �� �� ������, ������ ���� ������ �µ��� ĭ�� ���� ����ŭ �����ϰ� �ȴ�. 
	//�Ʒ� �׸��� ������ �������� �ٶ��� ���� �����̸�, ��ǳ�⿡�� �ٶ��� ������ ���⿡ ���� <�׸� 2>�� ȸ�����Ѽ� �ش��ϴ� �������� �ٶ��� ������ �� �����ϴ� �µ��� ���� �� �ִ�.

	for (int n = 0; n < heater_list.size(); n++)
	{
		for (int y = 1; y <= R; y++)
		{
			for (int x = 1; x <= C; x++)
			{
				temperature_map[n][y][x] = 0;
			}
		}
	}



	for (int n = 0; n < heater_list.size(); n++)
	{
		while (!q.empty()) q.pop();

		int y = heater_list[n].y;
		int x = heater_list[n].x;
		int d = heater_list[n].d; //1:�� 2:��  3:�� 4:��

		y = y + wind_dy[d][1];
		x = x + wind_dx[d][1];

		//�ٷ� ��ĭ 5
		temperature_map[n][y][x] = 5;

		//�� �������� 1�� �پ��鼭 3~5~7~9 �� idx �þ��


		q.push(make_pair(y, x));

		BFS(n, y, x, d);



	}


}

void sum_temperature()
{
	//�� ��ǳ�⿡�� ���� �ٶ��� sum_map�� �ջ�

	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			for (int i = 0; i < heater_list.size(); i++)
			{
				sum_map[y][x] += temperature_map[i][y][x];
			}
		}
	}


}

void control_temperature()
{
	//�µ��� �����Ǵ� ������ ������ ����.
	//��� ������ ĭ�� ���ؼ�, �µ��� ���� ĭ���� ���� ĭ���� (�� ĭ�� �µ��� ����) / 4ŭ �µ��� �����ȴ�.
	//�µ��� ���� ĭ�� �� ����ŭ �µ��� �����ϰ�, ���� ĭ�� �µ��� ����Ѵ�.
	//������ �� ĭ ���̿� ���� �ִ� ��쿡�� �µ��� �������� �ʴ´�.�� ������ ��� ĭ�� ���ؼ� ���ÿ� �߻��Ѵ�.

	int temp_map[MAX][MAX];
	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			temp_map[y][x] = sum_map[y][x];
		}
	}


	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			for (int dir = 1; dir < 5; dir++)
			{
				int flag = false;
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				if (ny < 1 || nx < 1 || ny > R || nx > C)	continue;
				if (dir == 1)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 1)
						{
							flag = true;
							break;
						}
					}
				}
				else if (dir == 2)
				{
					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 1)
						{
							flag = true;
							break;
						}
					}
				}
				else if (dir == 3)
				{
					for (int i = 0; i < wall_map[y][x].size(); i++)
					{
						if (wall_map[y][x][i] == 0)
						{
							flag = true;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < wall_map[ny][nx].size(); i++)
					{
						if (wall_map[ny][nx][i] == 0)
						{
							flag = true;
							break;
						}
					}
				}
				if (flag)	continue;


				if (sum_map[y][x] > sum_map[ny][nx])
				{
					temp_map[y][x] -= ((sum_map[y][x] - sum_map[ny][nx]) / 4);
					temp_map[ny][nx] += ((sum_map[y][x] - sum_map[ny][nx]) / 4);
				}
			}
		}
	}

	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			sum_map[y][x] = temp_map[y][x];
		}
	}

}

void decrease_outside_temperature()
{
	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			if (y == 1 || x == 1 || y == R || x == C)
			{
				if (sum_map[y][x] > 0)
					sum_map[y][x]--;
			}
		}
	}
}

bool check_temperature()
{
	bool flag = true;
	for (int i = 0; i < check_list.size(); i++)
	{
		if (sum_map[check_list[i].first][check_list[i].second] < K)
		{
			flag = false;
			break;
		}

	}

	return flag;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C >> K;

	for (int y = 1; y <= R; y++)
	{
		for (int x = 1; x <= C; x++)
		{
			int idx;
			cin >> idx;
			if (idx)
			{
				if (idx == 5)
					check_list.push_back(make_pair(y, x));
				//��ǳ�Ⱑ �ִ� ĭ�� �ٸ� ��ǳ�⿡ ���� �µ� ��� ����
				else
				{
					heater h = { y,x,idx };
					heater_list.push_back(h);
				}
			}
		}
	}

	cin >> W;

	for (int i = 0; i < W; i++)
	{
		//�ش� ��ǥ�� �� ���� ����
		int y, x, t;
		cin >> y >> x >> t;

		//t-> 0:��, 1:�����ʿ� �� �ִ°���
		wall_map[y][x].push_back(t);


	}


	int flag = false;

	while (1)
	{
		if (flag == true)
			break;

		work_heater();
		sum_temperature();
		control_temperature();
		decrease_outside_temperature();
		chocolate++;

		flag = check_temperature();


		if (chocolate > 100)
		{
			cout << 101 << "\n";
			return 0;
		}


	}

	cout << chocolate << "\n";

	return 0;
}