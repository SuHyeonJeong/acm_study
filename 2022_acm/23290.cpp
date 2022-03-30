#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int M, S;

//(r, c)�� ������ r�� c���� �ǹ��Ѵ�. ������ ���� ���� �� ĭ�� (1, 1)�̰�, ���� ������ �Ʒ� ĭ�� (4, 4)�̴�.
int map[5][5];

int sx, sy; // ��� ��ǥ

int max_eat = -1;

struct fish
{
	int x, y, d;
};


vector<fish> fishmap[5][5];
vector<fish> copy_fishmap[5][5]; //��ų ���� �� �����س��� ��

const int s_dy[5] = {0,-1,0,1,0}; //����� ������ üũ 
const int s_dx[5] = {0,0,-1,0,1}; //1:�� 2:�� 3:�� 4:��

vector<int> shark_best_route;


const int f_dy[17] = {0,0,-1,-1,-1,0,1,1,1, 0,-1,-1,-1,0,1,1,1 }; //����� ���� üũ
const int f_dx[17] = {0,-1,-1,0,1,1,1,0,-1, -1,-1,0,1,1,1,0,-1 }; //1:�� 2:�»� 3:�� 4:��� 5:�� 6:���� 7:�� 8:����

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
	//1.�� ��� ����⿡�� ���� ������ �����Ѵ�. ���� ������ �ð��� ���� �ɸ��� ������, �Ʒ� 5������ ����Ⱑ �����Ǿ� ĭ�� ��Ÿ����.
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
	//��� ����Ⱑ �� ĭ �̵��Ѵ�. �� �ִ� ĭ, ������� ������ �ִ� ĭ, ������ ������ ����� ĭ���δ� �̵��� �� ����. 
	//�� ������ �ڽ��� ������ �ִ� �̵� ������ �̵��� �� �ִ� ĭ�� ���� ������ ������ 45�� �ݽð� ȸ����Ų��. 
	//����, �̵��� �� �ִ� ĭ�� ������ �̵��� ���� �ʴ´�. �� ���� ��쿡�� �� ĭ���� �̵��� �Ѵ�. ������� ������ �Ʒ� 3���� �����Ѵ�.

	vector<fish> tempmap[5][5]; //�Ű��� �� fish map
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

				//�ƹ����⵵ ���� ���ϰ� �������� �״�� ����
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
	//route ��� ��� �ùķ��̼�
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
	//�� �����ؼ� 3ĭ �̵��Ѵ�. ���� ���� ĭ���� �����¿�� ������ ĭ���� �̵��� �� �ִ�. 
	//�����ؼ� �̵��ϴ� ĭ �߿� ������ ������ ����� ĭ�� ������, �� ����� �Ұ����� �̵� ����̴�.  
	//�����ؼ� �̵��ϴ� �߿� �� ����Ⱑ �ִ� ���� ĭ���� �̵��ϰ� �ȴٸ�, �� ĭ�� �ִ� ��� ������ ���ڿ��� ���ܵǸ�, ���ܵǴ� ��� ������ ����� ������ �����. 
	//������ �̵� ��� �߿��� ���ܵǴ� ������� ���� ���� ���� ������� �̵��ϸ�, �׷��� ����� ���������� ��� ���� ������ ���� �ռ��� ����� �̿��Ѵ�. ���� ���� ���� ������ �ϴ� ��Ʈ�� �ִ�.

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

	//�Է�
	//ù° �ٿ� ������� �� M, �� ������ ������ Ƚ�� S�� �־�����.��° �ٺ��� M���� �ٿ��� ������� ���� fx, fy, d�� �־�����. (fx, fy)�� ������� ��ġ�� �ǹ��ϰ�, d�� ������ �ǹ��Ѵ�.
	//������ 8 ������ �ڿ����� ǥ���ϰ�, 1���� ������� ��, ��, ��, ��, ��, ��, ��, �� �̴�.������ �ٿ��� sx, sy�� �־�����, ��(sx, sy)�� ������ �ǹ��Ѵ�.

	//���� ���� �ִ� ������� ���� �׻� 1, 000, 000 ������ �Է¸� �־�����.
	
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