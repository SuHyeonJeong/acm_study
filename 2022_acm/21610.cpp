#include <iostream>
#include <vector>
using namespace std;

int N, M;
const int MAX = 51;

int bucket_map[MAX][MAX] = { 0, }; //바구니에 저장된 물 양
int cloud_map[MAX][MAX] = { 0, }; //구름 위치
vector<pair<int, int>> cmd; //구름 이동 정보

//구름 이동 방향 : 좌, 좌상, 상, 상우, 우, 우하, 하, 하좌
const int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };
const int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };

//물복사버그 마법 시전 방향 : 대각선
const int diagonal_dy[4] = { -1,-1,1,1 };
const int diagonal_dx[4] = { -1,1,-1,1 };


void print(int map[MAX][MAX])
{
	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			cout << map[y][x] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void move_cloud(int d, int s)
{
	int temp[MAX][MAX] = { 0, };

	while (1)
	{
		if (s <= N)
			break;

		if (s > N)
			s -= N;
	}


	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			if (cloud_map[y][x])
			{
				int ny = y + s * dy[d];
				int nx = x + s * dx[d];

				if (ny < 1)
					ny += N;
				if (nx < 1)
					nx += N;
				if (ny > N)
					ny -= N;
				if (nx > N)
					nx -= N;

				temp[ny][nx] = 1;
			}
		}
	}

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			cloud_map[y][x] = temp[y][x];
		}
	}
}

void rain()
{
	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			if (cloud_map[y][x])
				bucket_map[y][x]++;
		}
	}
}

void disappear_cloud()
{
	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			cloud_map[y][x] = 0;
		}
	}
}

void copy_water()
{
	int temp[MAX][MAX] = { 0, };
	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			if (cloud_map[y][x])
			{
				int cnt = 0;
				for (int dir = 0; dir < 4; dir++)
				{
					int ny = y + diagonal_dy[dir];
					int nx = x + diagonal_dx[dir];

					if (ny > N || nx > N || ny < 1 || nx < 1)	continue;

					if (bucket_map[ny][nx])
						cnt++;
				}
				temp[y][x] += cnt;
			}
		}
	}

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			bucket_map[y][x] += temp[y][x];
		}
	}
}

void appear_cloud()
{
	int temp[MAX][MAX] = { 0, };

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			if (bucket_map[y][x] >= 2 && !cloud_map[y][x])
			{
				temp[y][x] = 1;
				bucket_map[y][x] -= 2;
			}
		}
	}

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			cloud_map[y][x] = temp[y][x];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> N >> M;

	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			cin >> bucket_map[y][x];
		}
	}

	for (int i = 0; i < M; i++)
	{
		int d, s;
		cin >> d >> s;
		cmd.push_back(make_pair(d, s));
	}

	cloud_map[N][1] = cloud_map[N][2] = cloud_map[N - 1][1] = cloud_map[N - 1][2] = 1;

	for (int i = 0; i < M; i++)
	{
		int d = cmd[i].first;
		int s = cmd[i].second;

		move_cloud(d, s);

		rain();

		copy_water();

		appear_cloud();

	}

	int cnt = 0;
	for (int y = 1; y <= N; y++)
	{
		for (int x = 1; x <= N; x++)
		{
			cnt += bucket_map[y][x];
		}
	}

	cout << cnt << "\n";


	return 0;
}