#include <iostream>
using namespace std;

int T, N;
int arr[1001];
bool visit[1001];

void DFS(int idx)
{
	visit[idx] = true;

	if (!visit[arr[idx]])
	{
		DFS(arr[idx]);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		

		cin >> N;
		int cnt = 0;
		for (int i = 1; i <= N; i++)
		{
			cin >> arr[i];
		}

		for (int i = 1; i <= N; i++)
		{
			if (!visit[i])
			{
				DFS(i);
				cnt++;
			}
		}

		for (int i = 1; i <= N; i++)
		{
			visit[i] = false;
		}
		

		cout << cnt << "\n";
	}

	

	return 0;
}