#include <iostream>
#include <queue>
using namespace std;
struct Cell
{
	int status = -1; //세포 상태
	int vitality; //생명력
	int activeTime; //활성화 시간
	int unactiveTime; //비활성화 시간

};
int T, N, M, K; 
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

Cell map[350][350];

int main()
{
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		
		for (int y = 0; y < 350; y++)
		{
			for (int x = 0; x < 350; x++)
			{
				Cell c;
				c.status = -1;
				c.vitality = 0;
				c.activeTime = 0;
				c.unactiveTime = 0;
				map[y][x] = c;
			}
		}

		cin >> N >> M >> K;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < M; x++)
			{
				int vital;
				cin >> vital;
				if (vital > 0)
				{
					Cell c;
					c.status = 0;
					c.vitality = vital;
					c.activeTime = vital;
					c.unactiveTime = vital;
					map[y + 150][x + 150] = c;
				}
				
			}
		}

		int time = 0;
		while (time < K)
		{
			queue<pair<int, int>> q;
			for (int y = 0; y < 350; y++)
			{
				for (int x = 0; x < 350; x++)
				{
					if (map[y][x].status == 0)
					{
						if (map[y][x].unactiveTime > 0)
							map[y][x].unactiveTime--;
						if (map[y][x].unactiveTime == 0)
							map[y][x].status = 1;
					}
					else if (map[y][x].status == 1)
					{
						if (map[y][x].activeTime > 0)
						{
							map[y][x].activeTime--;
							q.push(make_pair(y, x));
						}
						if (map[y][x].activeTime == 0)
						{
							map[y][x].status = 2;
						}
					}
				}
			}

			while (!q.empty())
			{
				int y = q.front().first;
				int x = q.front().second;
				q.pop();

				for (int i = 0; i < 4; i++)
				{
					int ny = y + dy[i];
					int nx = x + dx[i];
					if (ny < 0 || ny >= 350 || nx < 0 || nx >= 350)
						continue;
					if (map[ny][nx].status < 0)
					{
						//빈 칸
						map[ny][nx].status = 0;
						map[ny][nx].vitality = map[y][x].vitality;
						map[ny][nx].unactiveTime = map[y][x].vitality;
						map[ny][nx].activeTime = map[y][x].vitality;
					}
					else if (map[ny][nx].status == 0 && map[ny][nx].vitality == map[ny][nx].unactiveTime)
					{
						if (map[ny][nx].vitality < map[y][x].vitality)
						{
							map[ny][nx].vitality = map[y][x].vitality;
							map[ny][nx].unactiveTime = map[y][x].vitality;
							map[ny][nx].activeTime = map[y][x].vitality;
						}
					}
				}

			
			}
			time++;
		}

		int answer = 0;
		for (int y = 0; y < 350; y++)
		{
			for (int x = 0; x < 350; x++)
			{
				if (map[y][x].status == 0 || map[y][x].status == 1)
					answer++;
			}
		}

		cout << "#" << t+1 << " " << answer << "\n";
	}
	return 0;
}