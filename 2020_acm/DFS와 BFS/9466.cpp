#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int T, n, cnt;
int arr[100001];
bool visit[100001];
bool done[100001]; //방문 끝났는지 여부
void DFS(int idx)
{
	visit[idx] = true;

	int next = arr[idx];
	if (!visit[next])
	{
		DFS(next);
	}

	else if (!done[next])
	{
		for (int i = next; i != idx; i = arr[i])
			cnt++;//팀원수
		cnt++; //자기자신
	}

	done[idx] = true;

}
int main()
{
	ios_base::sync_with_stdio(false);

	cin >> T;

	for (int t = 0; t < T; t++)
	{
		memset(done, false, sizeof(done));
		memset(visit, false, sizeof(visit));
		cin >> n;

		cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> arr[i];
		}

		for (int j = 1; j <= n; j++)
		{
			if (!visit[j])
			{
				DFS(j);
			}
		}

		cout << n - cnt << "\n";
	}
	

	return 0;
}