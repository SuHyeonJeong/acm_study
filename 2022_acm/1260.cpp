#include <iostream>
#include <queue>
using namespace std;

int N, M, V;
const int MAX = 1001;
int graph[MAX][MAX];
bool visit[MAX];
queue <int> q;


//문제
//그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오.
//단, 방문할 수 있는 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고, 더 이상 방문할 수 있는 점이 없는 경우 종료한다.
//정점 번호는 1번부터 N번까지이다.

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


	//입력
	//첫째 줄에 정점의 개수 N(1 ≤ N ≤ 1, 000), 간선의 개수 M(1 ≤ M ≤ 10, 000), 탐색을 시작할 정점의 번호 V가 주어진다.
	//다음 M개의 줄에는 간선이 연결하는 두 정점의 번호가 주어진다.어떤 두 정점 사이에 여러 개의 간선이 있을 수 있다.입력으로 주어지는 간선은 양방향이다.

	cin >> N >> M >> V;

	for (int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		graph[u][v] = 1;
		graph[v][u] = 1;
	}


	//출력
	//첫째 줄에 DFS를 수행한 결과를, 그 다음 줄에는 BFS를 수행한 결과를 출력한다.V부터 방문된 점을 순서대로 출력하면 된다.

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