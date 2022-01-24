#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N;
const int MAX = 26;

int map[MAX][MAX];
bool visit[MAX][MAX];

queue<pair<int,int>> q;


int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

int cnt = 0;
vector<int> building_cnt;



void BFS(int y, int x)
{
	int temp_cnt = 0;
	q.push(make_pair(y, x));
	temp_cnt++;

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N)
				continue;

			if (map[ny][nx] && !visit[ny][nx])
			{
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
				temp_cnt++;
			}
		}
	}

	building_cnt.push_back(temp_cnt);
}

int main()
{
	//<그림 1>과 같이 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다.
	//철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다.여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다.
	//대각선상에 집이 있는 경우는 연결된 것이 아니다. <그림 2>는 <그림 1>을 단지별로 번호를 붙인 것이다.
	//지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.

	//입력
	//첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.

	//출력
	//첫 번째 줄에는 총 단지수를 출력하시오.그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < N; j++)
		{
			map[i][j] = str[j] - '0';
		}
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (map[i][j] && !visit[i][j])
			{
				visit[i][j] = true;
				BFS(i, j);
				cnt++;
			}
		}
	}

	sort(building_cnt.begin(), building_cnt.end());

	cout << cnt << "\n";
	
	for (int i = 0; i < building_cnt.size(); i++)
	{
		cout << building_cnt[i] << "\n";
	}

	return 0;
}