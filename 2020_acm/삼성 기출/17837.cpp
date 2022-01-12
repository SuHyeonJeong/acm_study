#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dy[] = { 0, 0, 0, -1, 1 };
int dx[] = { 0 ,1, -1, 0, 0 };
int turn[5] = { 0, 2, 1, 4, 3 };
int N, K;
int colors[13][13]; //체스판 색상 저장
vector<int> map[13][13]; //체스판 위 말의 순서 저장
struct horse
{
	int y;
	int x;
	int d;
}horses[10];

int move(int idx)
{
	int d = horses[idx].d;
	int ny = horses[idx].y + dy[d];
	int nx = horses[idx].x + dx[d];

	//맵을 벗어나거나 파란색
	if (ny > N || nx > N || ny < 1 || nx < 1 || colors[ny][nx] == 2)
	{
		//방향 바꿈
		horses[idx].d = turn[horses[idx].d];
		
		ny = horses[idx].y + dy[horses[idx].d];
		nx = horses[idx].x + dx[horses[idx].d];

		//반대 방향도 파랑
		if (ny > N || nx > N || ny < 1 || nx < 1 || colors[ny][nx] == 2)
			return 0;
	}

	vector<int> &cur = map[horses[idx].y][horses[idx].x];
	vector<int> &next = map[ny][nx];
	auto s = find(cur.begin(), cur.end(), idx);

	//빨간색
	//이동한 후에 A번 말과 그 위에 있는 모든 말의 쌓여있는 순서를 반대로 바꾼다.
	if (colors[ny][nx] == 1)
	{
		reverse(s, cur.end());
	}
	
	//이동
	for (auto iter = s; iter != cur.end(); ++iter)
	{
		horses[*iter].y = ny;
		horses[*iter].x = nx;
		next.push_back(*iter);
	}

	cur.erase(s, cur.end());
	return next.size();
}
int simulation()
{
	int flag;

	for(int round = 1; round<=1000; round++)
	{
		for (int i = 0; i < K; i++)
		{
			flag = move(i);

			if (flag >= 4)
			{
				//출력
				//게임이 종료되는 턴의 번호를 출력한다.
				return round;
			}
		}
	}

	//그 값이 1, 000보다 크거나 절대로 게임이 종료되지 않는 경우에는 - 1을 출력한다.
	return -1;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//입력
	//첫째 줄에 체스판의 크기 N, 말의 개수 K가 주어진다.둘째 줄부터 N개의 줄에 체스판의 정보가 주어진다.
	//체스판의 정보는 정수로 이루어져 있고, 각 정수는 칸의 색을 의미한다. 
	//0은 흰색, 1은 빨간색, 2는 파란색이다.
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> colors[i][j];
		}
	}
	//다음 K개의 줄에 말의 정보가 1번 말부터 순서대로 주어진다.
	//말의 정보는 세 개의 정수로 이루어져 있고, 순서대로 행, 열의 번호, 이동 방향이다.
	//행과 열의 번호는 1부터 시작하고, 이동 방향은 4보다 작거나 같은 자연수이고 1부터 순서대로 →, ←, ↑, ↓의 의미를 갖는다.
	//같은 칸에 말이 두 개 이상 있는 경우는 입력으로 주어지지 않는다.
	for (int i = 0; i < K; i++)
	{
		horse& ho = horses[i];
		cin >> ho.y >> ho.x >> ho.d;
		map[ho.y][ho.x].push_back(i);
	}

	cout << simulation();
	
	return 0;
}