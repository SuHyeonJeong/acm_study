#include <iostream>
#include <string>
#include <queue>
using namespace std;

int map[16][16];
bool visit[16][16];

bool check;

const int dy[] = { -1,1,0,0 };
const int dx[] = { 0,0,-1,1 };

void DFS(int y, int x)
{

	for (int dir = 0; dir < 4; dir++)
	{
		visit[y][x] = true;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (map[ny][nx] == 3)
		{
			check = true;
		}

		if (!visit[ny][nx] && map[ny][nx] == 0)
		{
			DFS(ny, nx);
		}
		visit[y][x] = false;


	
	}
}
int main()
{
	for (int i = 0; i < 10; i++)
	{
		check = 0;
		char n[1];
		cin >> n;
		
		for (int y = 0; y < 16; y++)
		{
			char str[16];
			cin >> str;
			for (int x = 0; x < 16; x++)
			{
				map[y][x] = str[x] - '0';
			}
			
		}

		cout << "#" << i+1 << " ";
		DFS(1, 1);
		cout << check << "\n";
	}
	return 0;
}