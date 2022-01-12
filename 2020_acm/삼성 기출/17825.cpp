#include <iostream>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

#define start 0
#define end 100
map<int, int> red = {
	{start,2}, {2,4},{4,6}, {6,8}
	,{8,10}, {10,12},{12,14}, {14,16}
	,{16,18}, {18,20},{20,22}, {22,24}
	,{24,26}, {26,28},{28,30}, {30,32}
	,{32,34}, {34,36},{36,38}, {38,40},{40,end} 
};
map<int, int> blue = {
	{10,13}, {13,16},{16,19}, {19,25}
	,{20,22} ,{22,24}, {24,25},{30,28}
	,{28,27} ,{27,26}, {26,25}
};
map<int, int> blue_goal = {
	{25,30}, {30,35},{35,40}, {40,end}
};

int cmd[10];
pair<int, int> horse[4] = { {0,0}, };
int ans = 0;

int moving(int depth, int index)
{
	int next = horse[index].first;
	//dir 0:red, 1:blue, 2:bluegoal
	int next_dir = horse[index].second;
	int cnt = cmd[depth]; //주사위 몇칸

	for (int i = 0; i < cnt; i++)
	{
		if (next_dir == 0)
		{
			next = red[next];
		}
		else if (next_dir == 1)
		{
			next = blue[next];
		}
		else if (next_dir == 2)
		{
			next = blue_goal[next];
		}

		if (next == 25)
		{
			next_dir = 2;
		}
		else if (next == end)
		{
			horse[index].first = end;
			break;
		}
	}

	if (next != end)
	{
		//현재 방향이 red이고, 코너일 때 blue로 바꿈
		if (next_dir == 0 && (next == 10 || next == 20 || next == 30))
			next_dir = 1;

		bool flag = true;

		for (int i = 0; i < 4; i++)
		{
			if (index == i)
				continue;
			//가려고 하는 next 자리에 이미 말이 있을 때
			if (next == horse[i].first && (next == 40 || next_dir == horse[i].second))
			{
				flag = false;
				break;
			}
		}
		//가려는 곳에 말이 없으면
		if (flag)
		{
			//이번 말의 위치와 방향 바꿔주기
			horse[index].first = next;
			horse[index].second = next_dir;
			return next;
		}
		else
			return -1;
	}

	//next가 도착일 때
	return 0;
}
void dfs(int depth, int value)
{
	if (depth == 10)
	{
		ans = max(ans, value);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int cur = horse[i].first;
		int cur_dir = horse[i].second;

		int temp = moving(depth, i);

		if (temp > -1)
			dfs(depth + 1, value + temp);

		horse[i].first = cur;
		horse[i].second = cur_dir;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 0; i < 10; i++)
		cin >> cmd[i];

	dfs(0, 0);
	cout << ans << "\n";
	return 0;
}