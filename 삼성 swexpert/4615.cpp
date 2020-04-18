#include <iostream>
using namespace std;

int map[8][8] = { 0, };
int N, M; //보드의 한변의 길이, 돌 놓는 횟수

int dy[] = { 0,0,1,1,1,-1,-1,-1 };
int dx[] = { 1, -1,0,-1,1,0,-1,1 };
void simulation(int y, int x)
{
	for (int dir = 0; dir < 8; dir++)
	{
		int color = map[y][x];
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		bool flag = false;
		
		while (ny < N && ny >= 0 && nx < N && nx >= 0 && map[ny][nx] != 0)
		{
			//처음과 같은 색 찾을 때까지 반복
			
			if (map[ny][nx] == color)
			{
				flag = true;
				break;
			}
			ny += dy[dir];
			nx += dx[dir];
			
		}

		while (flag)
		{
			//같은 색 찾은 경로 전부 색 바꾸기
			if (ny == y && nx == x)
				break;
			
			map[ny][nx] = color;
			ny -= dy[dir];
			nx -= dx[dir];
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		cin >> N >> M;
		
		//초기 맵 초기화
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				map[y][x] = 0;
			}
		}

		map[(N / 2) - 1][(N / 2) - 1] = 2;
		map[(N / 2) - 1][(N / 2)] = 2;
		map[(N / 2)][(N / 2) - 1] = 2;
		map[(N / 2)][(N / 2)] = 2;


		for (int m = 0; m < M; m++)
		{
			int y, x, c;
			cin >> y >> x >> c;
			map[y - 1][x - 1] = c;
			simulation(y-1, x-1);
		}

		int bc = 0; //흑돌 수
		int wc = 0; //백돌 수

		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (map[y][x] == 1)
					bc++;
				else if (map[y][x] == 2)
					wc++;
			}
		}

		cout << "#" << t + 1 << " " << bc << " " << wc << "\n";
	}
	return 0;
}