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

int temperature_map[400][MAX][MAX]; // 각 온풍기에서 나온 바람 각각 저장
int sum_map[MAX][MAX]; // 각 온풍기에서 나온 바람 합산한 맵

vector<heater> heater_list; //heater 정보(좌표, 방향) 저장한 list
vector<pair<int, int>> check_list; //마지막에 check 해야하는 좌표 저장한 list
vector<int> wall_map[MAX][MAX]; //벽 정보 저장한 3차원 vector -> 해당 좌표에 0과 1로 방향포함 벽 정보 저장

queue<pair<int, int>> q;


//오, 왼, 위, 아래 : 온풍기 방향=d
const int dy[5] = { 0,0,0,-1,1 };
const int dx[5] = { 0,1,-1,0,0 };

//온풍기 방향에 따라 바람 나가는 3방향 : 
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

			// 벽 있으면 continue.[y - 1][x], [y + 1][x]도 검사해야함
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
				//바람 세기 조절
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
	//집에 있는 모든 온풍기에서 바람이 한 번 나오는 과정을 설명하면 다음과 같다.
	//<그림 1>은 크기가 7×8인 집에 온풍기가 (3, 1)에 설치되어 있는 상황이다. 온풍기는 바람이 나오는 방향이 있는데, 그 방향은 오른쪽, 왼쪽, 위, 아래 중 하나이다. 
	//온풍기에서 따뜻한 바람이 한 번 나오면, 다음과 같은 영역의 온도가 칸에 적힌 값만큼 증가하게 된다. 
	//아래 그림은 오른쪽 방향으로 바람이 나온 예시이며, 온풍기에서 바람이 나오는 방향에 따라 <그림 2>를 회전시켜서 해당하는 방향으로 바람이 나왔을 때 증가하는 온도를 구할 수 있다.

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
		int d = heater_list[n].d; //1:우 2:좌  3:상 4:하

		y = y + wind_dy[d][1];
		x = x + wind_dx[d][1];

		//바로 앞칸 5
		temperature_map[n][y][x] = 5;

		//이 다음부터 1씩 줄어들면서 3~5~7~9 로 idx 늘어나기


		q.push(make_pair(y, x));

		BFS(n, y, x, d);



	}


}

void sum_temperature()
{
	//각 온풍기에서 나온 바람을 sum_map에 합산

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
	//온도가 조절되는 과정은 다음과 같다.
	//모든 인접한 칸에 대해서, 온도가 높은 칸에서 낮은 칸으로 (두 칸의 온도의 차이) / 4큼 온도가 조절된다.
	//온도가 높은 칸은 이 값만큼 온도가 감소하고, 낮은 칸은 온도가 상승한다.
	//인접한 두 칸 사이에 벽이 있는 경우에는 온도가 조절되지 않는다.이 과정은 모든 칸에 대해서 동시에 발생한다.

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
				//온풍기가 있는 칸도 다른 온풍기에 의해 온도 상승 가능
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
		//해당 좌표에 벽 방향 저장
		int y, x, t;
		cin >> y >> x >> t;

		//t-> 0:위, 1:오른쪽에 벽 있는거임
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