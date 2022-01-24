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
	//<�׸� 1>�� ���� ���簢�� ����� ������ �ִ�. 1�� ���� �ִ� ����, 0�� ���� ���� ���� ��Ÿ����.
	//ö���� �� ������ ������ ����� ���� ������ ������ �����ϰ�, ������ ��ȣ�� ���̷� �Ѵ�.���⼭ ����Ǿ��ٴ� ���� � ���� �¿�, Ȥ�� �Ʒ����� �ٸ� ���� �ִ� ��츦 ���Ѵ�.
	//�밢���� ���� �ִ� ���� ����� ���� �ƴϴ�. <�׸� 2>�� <�׸� 1>�� �������� ��ȣ�� ���� ���̴�.
	//������ �Է��Ͽ� �������� ����ϰ�, �� ������ ���ϴ� ���� ���� ������������ �����Ͽ� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

	//�Է�
	//ù ��° �ٿ��� ������ ũ�� N(���簢���̹Ƿ� ���ο� ������ ũ��� ������ 5��N��25)�� �Էµǰ�, �� ���� N�ٿ��� ���� N���� �ڷ�(0Ȥ�� 1)�� �Էµȴ�.

	//���
	//ù ��° �ٿ��� �� �������� ����Ͻÿ�.�׸��� �� ������ ���� ���� ������������ �����Ͽ� �� �ٿ� �ϳ��� ����Ͻÿ�.

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