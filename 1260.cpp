#include <iostream>
#include <queue>
using namespace std;

const int MAX = 1001;
int n, m, v;
int graph[MAX][MAX];
bool visit[MAX];
queue <int> q;

void DFS(int idx)
{
	visit[v] = true; // v에서 시작
	cout << idx << " ";

	for (int i = 1; i <= n; i++)
	{
		if (graph[idx][i] && !visit[i])
		{
			visit[i] = true;
			DFS(i); //인접한 노드에 다시 DFS
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

		for (int i = 1; i <= n; i++)
		{
			if (graph[idx][i] && !visit[i])
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
	
	cin >> n >> m >> v;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		graph[u][v] = 1;
		graph[v][u] = 1;
	}

	
	DFS(v);
	cout << "\n";

	for (int i = 0; i < MAX; i++)
	{
		visit[i] = false;
	}

	BFS(v);
	cout << "\n";
	return 0;
}