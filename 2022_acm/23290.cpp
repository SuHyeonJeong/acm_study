#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int M, S;

//(r, c)는 격자의 r행 c열을 의미한다. 격자의 가장 왼쪽 윗 칸은 (1, 1)이고, 가장 오른쪽 아랫 칸은 (4, 4)이다.
int map[5][5];

int sx, sy; // 상어 좌표

int max_eat = -1;

struct fish
{
	int x, y, d;
};


vector<fish> fishmap[5][5];
vector<fish> copy_fishmap[5][5]; //스킬 시전 후 복사해놓을 맵

const int s_dy[5] = {0,-1,0,1,0}; //상어의 움직임 체크 
const int s_dx[5] = {0,0,-1,0,1}; //1:상 2:좌 3:하 4:우

vector<int> shark_best_route;


const int f_dy[17] = {0,0,-1,-1,-1,0,1,1,1, 0,-1,-1,-1,0,1,1,1 }; //물고기 방향 체크
const int f_dx[17] = {0,-1,-1,0,1,1,1,0,-1, -1,-1,0,1,1,1,0,-1 }; //1:좌 2:좌상 3:상 4:상우 5:우 6:우하 7:하 8:하좌

void print_fishmap()
{
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			cout << fishmap[i][j].size() << " ";
		}
		cout << "\n";
	}
	cout << "\n";

}


void cast_copy_fishes()
{
	//1.상어가 모든 물고기에게 복제 마법을 시전한다. 복제 마법은 시간이 조금 걸리기 때문에, 아래 5번에서 물고기가 복제되어 칸에 나타난다.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			copy_fishmap[i][j] = fishmap[i][j];
		}
	}
}

void move_fishes()
{
	//모든 물고기가 한 칸 이동한다. 상어가 있는 칸, 물고기의 냄새가 있는 칸, 격자의 범위를 벗어나는 칸으로는 이동할 수 없다. 
	//각 물고기는 자신이 가지고 있는 이동 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다. 
	//만약, 이동할 수 있는 칸이 없으면 이동을 하지 않는다. 그 외의 경우에는 그 칸으로 이동을 한다. 물고기의 냄새는 아래 3에서 설명한다.

	vector<fish> tempmap[5][5]; //옮겨줄 빈 fish map
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < fishmap[i][j].size(); k++)
			{
				int y = fishmap[i][j][k].y;
				int x = fishmap[i][j][k].x;
				int d = fishmap[i][j][k].d;
				bool flag = false;

				for (int dir = d + 8; dir > d; dir--)
				{
					int ny = y + f_dy[dir];
					int nx = x + f_dx[dir];
					if (ny < 1 || nx < 1 || ny > 4 || nx > 4 || map[ny][nx] > 0 || (ny == sy && nx == sx))
						continue;
					
					fish f;
					f.y = ny;
					f.x = nx;
					if (dir > 8)
						f.d = dir - 8;
					else
						f.d = dir;

					tempmap[ny][nx].push_back(f);
					flag = true;
					break;
					
				}

				//아무방향도 가지 못하고 나왔으면 그대로 저장
				if (!flag)
				{
					fish f;
					f.y = y;
					f.x = x;
					f.d = d;
					tempmap[y][x].push_back(f);
				}
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			fishmap[i][j] = tempmap[i][j];
		}
	}


}

int simulation_shark(vector<int> route)
{
	//route 대로 상어 시뮬레이션
	bool visit[5][5] = { false, };
	int eat=0;
	int nsy = sy;
	int nsx = sx;
	for (auto dir : route)
	{
		nsy += s_dy[dir];
		nsx += s_dx[dir];
		
		if (nsy < 1 || nsx < 1 || nsy > 4 || nsx > 4)
			return -1;
		if (!visit[nsy][nsx])
		{
			visit[nsy][nsx] = true;
			eat += fishmap[nsy][nsx].size();
		}
		
	}

	return eat;
}

void calculate_best_route(vector<int> route)
{
	if (route.size() == 3)
	{
		int eat = simulation_shark(route);
		if (eat > max_eat)
		{
			max_eat = eat;
			shark_best_route = route;
		}
		return;
	}

	for (int dir = 1; dir < 5; dir++)
	{
		route.push_back(dir);
		calculate_best_route(route);
		route.pop_back();
	}
}

void move_shark()
{
	//상어가 연속해서 3칸 이동한다. 상어는 현재 칸에서 상하좌우로 인접한 칸으로 이동할 수 있다. 
	//연속해서 이동하는 칸 중에 격자의 범위를 벗어나는 칸이 있으면, 그 방법은 불가능한 이동 방법이다.  
	//연속해서 이동하는 중에 상어가 물고기가 있는 같은 칸으로 이동하게 된다면, 그 칸에 있는 모든 물고기는 격자에서 제외되며, 제외되는 모든 물고기는 물고기 냄새를 남긴다. 
	//가능한 이동 방법 중에서 제외되는 물고기의 수가 가장 많은 방법으로 이동하며, 그러한 방법이 여러가지인 경우 사전 순으로 가장 앞서는 방법을 이용한다. 사전 순에 대한 문제의 하단 노트에 있다.

	for (auto dir : shark_best_route)
	{
		sy += s_dy[dir];
		sx += s_dx[dir];
		if (fishmap[sy][sx].size() != 0)
		{
			fishmap[sy][sx].clear();
			map[sy][sx] = 1;
		}
	}
	

}

void complete_copy_fish()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < copy_fishmap[i][j].size(); k++)
			{
				fishmap[i][j].push_back(copy_fishmap[i][j][k]);
			}
		}
	}
}

void check_smell()
{

	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (map[i][j] == 3)
				map[i][j] = 0;
		}
	}
}

void up_smell()
{
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (map[i][j])
				map[i][j]++;
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//입력
	//첫째 줄에 물고기의 수 M, 상어가 마법을 연습한 횟수 S가 주어진다.둘째 줄부터 M개의 줄에는 물고기의 정보 fx, fy, d가 주어진다. (fx, fy)는 물고기의 위치를 의미하고, d는 방향을 의미한다.
	//방향은 8 이하의 자연수로 표현하고, 1부터 순서대로 ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 이다.마지막 줄에는 sx, sy가 주어지며, 상어가(sx, sy)에 있음을 의미한다.

	//격자 위에 있는 물고기의 수가 항상 1, 000, 000 이하인 입력만 주어진다.
	
	cin >> M >> S;

	for (int i = 0; i < M; i++)
	{
		int y, x, d;
		cin >> y >> x >> d;
		fish f;
		f.x = x;
		f.y = y;
		f.d = d;
		fishmap[y][x].push_back(f);
	}

	cin >> sy >> sx;


	for (int s = 0; s < S; s++)
	{
		cast_copy_fishes();
		
		up_smell();
		

		move_fishes();

		
		max_eat = -1;
		vector<int> temp;
		calculate_best_route(temp);


		move_shark();


		check_smell();
		
		
		complete_copy_fish();
		
	}
	
	int cnt = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cnt += fishmap[i][j].size();
		}
	}

	cout << cnt << "\n";
	
	return 0;
}