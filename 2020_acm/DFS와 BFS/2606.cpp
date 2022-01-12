#include <iostream>
#include <vector>
using namespace std;

int com, line;
int cnt = 0;

vector <vector<int>> map;
bool visit[101];

void DFS(int idx)
{
	visit[idx] = true;

	for (int i = 0; i < map[idx].size(); i++)
	{
		if (!visit[map[idx][i]])
		{
			DFS(map[idx][i]);
			cnt++;
		}
	}
	
	return;
	
}
int main()
{
	ios_base::sync_with_stdio(false);

	cin >> com >> line;

	map.resize(com + 1);


	for (int i = 0; i < line; i++)
	{
		int n1, n2;
		cin >> n1 >> n2;
		map[n1].push_back(n2);
		map[n2].push_back(n1);
	}

	DFS(1);

	cout << cnt << "\n";

	return 0;
}