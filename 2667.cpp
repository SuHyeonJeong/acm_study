#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0,0,-1,1 };

const int MAX = 26;
int map[MAX][MAX];
bool visit[MAX][MAX];
int N;
int cnt = 0; //단지 내 집 수 
vector<int> house_cnt;
void DFS(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		int next_y = y + dy[i];
		int next_x = x + dx[i];

		if (map[next_y][next_x] == 1 && visit[next_y][next_x] == 0)
		{
			visit[next_y][next_x] = true;
			cnt++;
			DFS(next_y, next_x);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> N;
	string str;

	for (int y = 0; y < N; y++)
	{
		cin >> str;

		for (int x = 0; x < N; x++)
		{
			if (str[x] == '1')
			{
				map[y][x] = 1;
			}
			else
			{
				map[y][x] = 0;
			}
		}
	}

	/*for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
		}
	}*/

	

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (map[y][x] == 1 && visit[y][x] == 0)
			{
				visit[y][x] = true;
				cnt++;
				DFS(y, x);
				house_cnt.push_back(cnt);
				cnt = 0;
			}
		}
	}

	sort(house_cnt.begin(), house_cnt.end());

	cout << house_cnt.size() << "\n";
	for (int i = 0; i < house_cnt.size(); i++)
	{
		cout << house_cnt[i] << "\n";
	}

	return 0;
}