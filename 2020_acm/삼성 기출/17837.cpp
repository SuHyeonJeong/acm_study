#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dy[] = { 0, 0, 0, -1, 1 };
int dx[] = { 0 ,1, -1, 0, 0 };
int turn[5] = { 0, 2, 1, 4, 3 };
int N, K;
int colors[13][13]; //ü���� ���� ����
vector<int> map[13][13]; //ü���� �� ���� ���� ����
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

	//���� ����ų� �Ķ���
	if (ny > N || nx > N || ny < 1 || nx < 1 || colors[ny][nx] == 2)
	{
		//���� �ٲ�
		horses[idx].d = turn[horses[idx].d];
		
		ny = horses[idx].y + dy[horses[idx].d];
		nx = horses[idx].x + dx[horses[idx].d];

		//�ݴ� ���⵵ �Ķ�
		if (ny > N || nx > N || ny < 1 || nx < 1 || colors[ny][nx] == 2)
			return 0;
	}

	vector<int> &cur = map[horses[idx].y][horses[idx].x];
	vector<int> &next = map[ny][nx];
	auto s = find(cur.begin(), cur.end(), idx);

	//������
	//�̵��� �Ŀ� A�� ���� �� ���� �ִ� ��� ���� �׿��ִ� ������ �ݴ�� �ٲ۴�.
	if (colors[ny][nx] == 1)
	{
		reverse(s, cur.end());
	}
	
	//�̵�
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
				//���
				//������ ����Ǵ� ���� ��ȣ�� ����Ѵ�.
				return round;
			}
		}
	}

	//�� ���� 1, 000���� ũ�ų� ����� ������ ������� �ʴ� ��쿡�� - 1�� ����Ѵ�.
	return -1;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//�Է�
	//ù° �ٿ� ü������ ũ�� N, ���� ���� K�� �־�����.��° �ٺ��� N���� �ٿ� ü������ ������ �־�����.
	//ü������ ������ ������ �̷���� �ְ�, �� ������ ĭ�� ���� �ǹ��Ѵ�. 
	//0�� ���, 1�� ������, 2�� �Ķ����̴�.
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> colors[i][j];
		}
	}
	//���� K���� �ٿ� ���� ������ 1�� ������ ������� �־�����.
	//���� ������ �� ���� ������ �̷���� �ְ�, ������� ��, ���� ��ȣ, �̵� �����̴�.
	//��� ���� ��ȣ�� 1���� �����ϰ�, �̵� ������ 4���� �۰ų� ���� �ڿ����̰� 1���� ������� ��, ��, ��, ���� �ǹ̸� ���´�.
	//���� ĭ�� ���� �� �� �̻� �ִ� ���� �Է����� �־����� �ʴ´�.
	for (int i = 0; i < K; i++)
	{
		horse& ho = horses[i];
		cin >> ho.y >> ho.x >> ho.d;
		map[ho.y][ho.x].push_back(i);
	}

	cout << simulation();
	
	return 0;
}