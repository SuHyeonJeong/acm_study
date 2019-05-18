#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int T, N; //N : 적군 진영의 숫자
bool visit[3001];

queue<pair<int, int>> q;
vector<pair<int, int>> v;
int r[3001];

vector<int> answer;

void BFS(int idx)
{
	visit[idx] = true;
	q.push(v[idx]);

	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;

		q.pop();

		for (int i = 0; i < v.size(); i++)
		{
			if (!visit[i] && (pow((x - v[i].first), 2) + pow((y - v[i].second), 2) <= pow((r[idx] + r[i]), 2)))
			{
				visit[i] = true;
				q.push(make_pair(v[i].first, v[i].second));
			}
		}

	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		v.clear();

		cin >> N;
		int x, y, R;
		int cnt = 0;
		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> R; //R : 통신 가능 거리
			v.push_back(make_pair(x, y));
		}
		
		for (int i = 0; i < N; i++)
		{
			if (!visit[i])
			{
				BFS(i);
				cnt++;
			}
		}
		
		answer.push_back(cnt);
	}

	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << "\n";
	}

	return 0;
}