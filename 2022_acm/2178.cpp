#include <iostream>
#include <queue>
#include <string>
using namespace std;

int N, M;
const int MAX = 101;
int map[MAX][MAX];
bool visit[MAX][MAX];
queue<pair<int, int>> q;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void BFS() 
{
	
	//�̷��� �̷ΰ� �־����� ��, (1, 1)���� ����Ͽ� (N, M)�� ��ġ�� �̵��� �� ������ �ϴ� �ּ��� ĭ ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�. 
	//�� ĭ���� �ٸ� ĭ���� �̵��� ��, ���� ������ ĭ���θ� �̵��� �� �ִ�.
	//101111
	//101010
	//101011
	//111011
	//���� �������� 15ĭ�� ������(N, M)�� ��ġ�� �̵��� �� �ִ�.ĭ�� �� ������ ���� ��ġ�� ���� ��ġ�� �����Ѵ�.

	while (!q.empty())
	{
		int y = q.front().first;
		int x = q.front().second;

		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (ny > N || nx > M || ny < 1 || nx < 1)
				continue;

			if (map[ny][nx] && !visit[ny][nx])
			{
				q.push(make_pair(ny, nx));
				visit[ny][nx] = true;
				map[ny][nx] = map[y][x] + 1;
			}
		}

		

	}

	cout << map[N][M] << "\n";

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	//N��Mũ���� �迭�� ǥ���Ǵ� �̷ΰ� �ִ�.
	//�̷ο��� 1�� �̵��� �� �ִ� ĭ�� ��Ÿ����, 0�� �̵��� �� ���� ĭ�� ��Ÿ����. 
	//�Է�
	//ù° �ٿ� �� ���� N, M(2 �� N, M �� 100)�� �־�����.���� N���� �ٿ��� M���� ������ �̷ΰ� �־�����.������ ������ �پ �Է����� �־�����.

	cin >> N >> M;

	for (int y = 1; y <= N; y++)
	{
		string str;
		cin >> str;

		for (int x = 1; x <= M; x++)
		{
			map[y][x] = str[x - 1] - '0';
		}
	}

	q.push(make_pair(1, 1));
	visit[1][1] = true;

	BFS();


	//���
	//ù° �ٿ� ������ �ϴ� �ּ��� ĭ ���� ����Ѵ�.�׻� ������ġ�� �̵��� �� �ִ� ��츸 �Է����� �־�����.
	return 0;
}