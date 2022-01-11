#include <iostream>
#include <queue>
using namespace std;

int N, M, V;
const int MAX = 1001;
int graph[MAX][MAX];
bool visit[MAX];
queue <int> q;


//����
//�׷����� DFS�� Ž���� ����� BFS�� Ž���� ����� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
//��, �湮�� �� �ִ� ������ ���� ���� ��쿡�� ���� ��ȣ�� ���� ���� ���� �湮�ϰ�, �� �̻� �湮�� �� �ִ� ���� ���� ��� �����Ѵ�.
//���� ��ȣ�� 1������ N�������̴�.

void DFS(int idx)
{
	visit[idx] = true;
	
	cout << idx << " ";

	for (int i = 1; i <= N; i++)
	{
		if (graph[idx][i] & !visit[i])
		{
			visit[i] = true;
			DFS(i);
		}
	}

}

void BFS(int idx)
{
	q.push(idx);
	visit[idx] = true;

	while (!q.empty())
	{
		idx = q.front();
		q.pop();

		cout << idx << " ";

		for (int i = 1; i <= N; i++)
		{
			if (graph[idx][i] & !visit[i])
			{
				visit[i] = true;
				q.push(i);
			}
		}

	}
}

int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);


	//�Է�
	//ù° �ٿ� ������ ���� N(1 �� N �� 1, 000), ������ ���� M(1 �� M �� 10, 000), Ž���� ������ ������ ��ȣ V�� �־�����.
	//���� M���� �ٿ��� ������ �����ϴ� �� ������ ��ȣ�� �־�����.� �� ���� ���̿� ���� ���� ������ ���� �� �ִ�.�Է����� �־����� ������ ������̴�.

	cin >> N >> M >> V;

	for (int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		graph[u][v] = 1;
		graph[v][u] = 1;
	}


	//���
	//ù° �ٿ� DFS�� ������ �����, �� ���� �ٿ��� BFS�� ������ ����� ����Ѵ�.V���� �湮�� ���� ������� ����ϸ� �ȴ�.

	DFS(V);

	cout << "\n";

	for (int i = 0; i < MAX; i++)
	{
		visit[i] = false;
	}

	BFS(V);

	cout << "\n";




	return 0;
}