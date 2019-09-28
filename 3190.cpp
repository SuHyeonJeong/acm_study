#include <iostream>
#include <queue>
using namespace std;



//출력
//첫째 줄에 게임이 몇 초에 끝나는지 출력한다.
int N, K, L;

//게임은 NxN 정사각 보드위에서 진행되고, 몇몇 칸에는 사과가 놓여져 있다.

int map[101][101];
char cmd[10001];
int snake_y[10101], snake_x[10101];

int time = 0;
//보드의 상하좌우 끝에 벽이 있다.게임이 시작할때 뱀은 맨위 맨좌측에 위치하고 뱀의 길이는 1 이다
int head_x = 1, head_y = 1, tail_index = time;
//뱀은 처음에 오른쪽을 향한다.
int dir = 0;

const int dy[] = { 0,1,0,-1 };
const int dx[] = { 1,0,-1,0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//입력
	//첫째 줄에 보드의 크기 N이 주어진다. (2 ≤ N ≤ 100) 다음 줄에 사과의 개수 K가 주어진다. (0 ≤ K ≤ 100)
	//다음 K개의 줄에는 사과의 위치가 주어지는데, 첫 번째 정수는 행, 두 번째 정수는 열 위치를 의미한다.
	//사과의 위치는 모두 다르며, 맨 위 맨 좌측(1행 1열) 에는 사과가 없다.
	cin >> N >> K;
	for (int i = 0; i < K; i++)
	{
		int y, x;
		cin >> y >> x;
		map[y][x] = 1;
	}
	//다음 줄에는 뱀의 방향 변환 횟수 L 이 주어진다. (1 ≤ L ≤ 100)
	//다음 L개의 줄에는 뱀의 방향 변환 정보가 주어지는데, 정수 X와 문자 C로 이루어져 있으며.
	//게임 시작 시간으로부터 X초가 끝난 뒤에 왼쪽(C가 'L') 또는 오른쪽(C가 'D')로 90도 방향을 회전시킨다는 뜻이다.
	//X는 10, 000 이하의 양의 정수이며, 방향 전환 정보는 X가 증가하는 순으로 주어진다.
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int x;
		cin >> x;
		cin >> cmd[x];

	}

	snake_y[time] = head_y;
	snake_x[time] = head_x;
	map[snake_y[time]][snake_x[time]] = -1;


	while (1)
	{
		time++;

		//먼저 뱀은 몸길이를 늘려 머리를 다음칸에 위치시킨다.
		head_y += dy[dir], head_x += dx[dir];

		//'Dummy' 라는 도스게임이 있다.이 게임에는 뱀이 나와서 기어다니는데, 사과를 먹으면 뱀 길이가 늘어난다.

		//뱀이 이리저리 기어다니다가 벽 또는 자기자신의 몸과 부딪히면 게임이 끝난다.
		if (map[head_y][head_x] == -1 || head_x > N || head_y > N || head_x < 1 || head_y < 1)
		{
			break;
		}

		snake_x[time] = head_x;
		snake_y[time] = head_y;

		
		//만약 이동한 칸에 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다.즉, 몸길이는 변하지 않는다.
		if(map[head_y][head_x]== 0)
		{
			int tail_y = snake_y[tail_index];
			int tail_x = snake_x[tail_index];
			map[tail_y][tail_x] = 0;
			tail_index++;
		}

		//만약 이동한 칸에 사과가 있다면, 그 칸에 있던 사과가 없어지고 꼬리는 움직이지 않는다.
		map[head_y][head_x] = -1;

		if (cmd[time] == 'D')
		{
			dir = (dir + 1) % 4;
		}
		else if (cmd[time] == 'L')
		{
			dir = (dir + 3) % 4;
		}

	}

	//사과의 위치와 뱀의 이동경로가 주어질 때 이 게임이 몇 초에 끝나는지 계산하라.
	cout << time << "\n";
	return 0;
}