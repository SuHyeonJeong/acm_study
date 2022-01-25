
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int M, N, H;
const int MAX = 101;
int map[MAX][MAX][MAX];
bool visit[MAX][MAX][MAX];

queue<pair<pair<int,int>, int>> q;

int dy[6] = {-1,1,0,0,0,0};
int dx[6] = {0,0,-1,1,0,0};
int dh[6] = {0,0,0,0,-1,1};

void BFS()
{
	//ö���� �丶�� ���忡���� �丶�並 �����ϴ� ū â�� ������ �ִ�.�丶��� �Ʒ��� �׸��� ���� ���ڸ�� ������ ĭ�� �ϳ��� ���� ����, ���ڵ��� �������� �׾� �÷��� â�� �����Ѵ�.

	//â�� �����Ǵ� �丶��� �߿��� �� ���� �͵� ������, ���� ���� ���� �丶��鵵 ���� �� �ִ�.
	//���� �� �Ϸ簡 ������, ���� �丶����� ������ ���� �ִ� ���� ���� �丶����� ���� �丶���� ������ �޾� �Ͱ� �ȴ�.
	//�ϳ��� �丶�信 ������ ���� ��, �Ʒ�, ����, ������, ��, �� ���� ���⿡ �ִ� �丶�並 �ǹ��Ѵ�.
	//�밢�� ���⿡ �ִ� �丶��鿡�Դ� ������ ���� ���ϸ�, �丶�䰡 ȥ�� ������ �ʹ� ���� ���ٰ� �����Ѵ�.
	//ö���� â�� ������ �丶����� ��ĥ�� ������ �� �Ͱ� �Ǵ��� �� �ּ� �ϼ��� �˰� �;� �Ѵ�.

	//�丶�並 â�� �����ϴ� ���ڸ���� ���ڵ��� ũ��� ���� �丶���� ���� ���� �丶����� ������ �־����� ��, ��ĥ�� ������ �丶����� ��� �ʹ���, �� �ּ� �ϼ��� ���ϴ� ���α׷��� �ۼ��϶�.
	//��, ������ �Ϻ� ĭ���� �丶�䰡 ������� ���� ���� �ִ�.


	while (!q.empty())
	{
		int h = q.front().second;
		int y = q.front().first.first;
		int x = q.front().first.second;

		q.pop();

		for (int dir = 0; dir < 6; dir++)
		{
			int nh = h + dh[dir];
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (nh >= H || ny >= N || nx >= M || nh < 0 || ny < 0 || nx < 0)
				continue;

			if (map[nh][ny][nx] == 0 && !visit[nh][ny][nx])
			{
				map[nh][ny][nx] = map[h][y][x] + 1;
				visit[nh][ny][nx] = true;
				q.push(make_pair(make_pair(ny, nx), nh));

			}
		}

	}
}

int main()
{

	//�Է�
	//ù �ٿ��� ������ ũ�⸦ ��Ÿ���� �� ���� M, N�� �׾ƿ÷����� ������ ���� ��Ÿ���� H�� �־�����.
	//M�� ������ ���� ĭ�� ��, N�� ������ ���� ĭ�� ���� ��Ÿ����.��, 2 �� M �� 100, 2 �� N �� 100, 1 �� H �� 100 �̴�.
	//��° �ٺ��ʹ� ���� ���� ���ں��� ���� ���� ���ڱ����� ����� �丶����� ������ �־�����.��, ��° �ٺ��� N���� �ٿ��� �ϳ��� ���ڿ� ��� �丶���� ������ �־�����.
	//�� �ٿ��� ���� �����ٿ� ����ִ� �丶����� ���°� M���� ������ �־�����.���� 1�� ���� �丶��, ���� 0 �� ���� ���� �丶��, ���� - 1�� �丶�䰡 ������� ���� ĭ�� ��Ÿ����.
	//�̷��� N���� ���� H�� �ݺ��Ͽ� �־�����.

	//�丶�䰡 �ϳ� �̻� �ִ� ��츸 �Է����� �־�����.

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> M >> N >> H;

	bool oneflag = true;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				cin >> map[i][j][k];
				if (map[i][j][k] != 1 || map[i][j][k] != -1)
					oneflag = false;
			}
		}
	}

	//����, ����� ������ ��� �丶�䰡 �;��ִ� �����̸� 0�� ����ؾ� �ϰ�
	if (oneflag == true)
	{
		cout << 0 << "\n";
		return 0;
	}



	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				if (map[i][j][k] == 1 && !visit[i][j][k])
				{
					q.push(make_pair(make_pair(j, k), i));
				}
			}
		}
	}

	BFS();
	

	
	//���

	int max = -100;
	bool maxflag = false;
	bool zeroflag = false;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				if (map[i][j][k] > max)
				{
					max = map[i][j][k];
						maxflag = true;
				}

				if (map[i][j][k] == 0)
					zeroflag = true;

			}
		}
	}

	// �丶�䰡 ��� ������ ���ϴ� ��Ȳ�̸� - 1�� ����ؾ� �Ѵ�.
	if (zeroflag)
	{
		cout << -1 << "\n";
		return 0;
	}

	//�������� �丶�䰡 ��� ���� ������ �ּ� ��ĥ�� �ɸ������� ����ؼ� ����ؾ� �Ѵ�.
	if (maxflag)
	{
		cout << max-1 << "\n";
		return 0;
	}
	

	

}