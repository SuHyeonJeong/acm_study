#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M; // N:컴퓨터 개수, M:신뢰 관계 개수

vector <vector<int>> map;
bool visit[100001];
int cnt;
int ans = -1;

void DFS(int idx)
{

	visit[idx] = true;

	for (int i = 0; i < map[idx].size(); i++)
	{
		if (!visit[map[idx][i]])
		{
			cnt++;
			DFS(map[idx][i]);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> N >> M;

	map.resize(N + 1);

	for (int i = 0; i < M; i++)
	{
		int n1, n2;
		cin >> n1 >> n2;
		map[n2].push_back(n1);
	}

	vector<int> answer;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			visit[j] = false;
		}

		cnt = 0;
		DFS(i);

		if (cnt > ans)
		{
			ans = cnt;
			answer.clear();
			answer.push_back(i);
		}
		else if (cnt == ans)
		{
			answer.push_back(i);
		}

	}

	sort(answer.begin(), answer.end());
	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << " ";
	}
	cout << "\n";

	

	return 0;
}