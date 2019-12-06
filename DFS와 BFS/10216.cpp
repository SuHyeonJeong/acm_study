#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int T, N; //N : 적군 진영의 숫자

queue<int> q;
vector<pair<int, int>> v;
int r[3001];
vector<vector<int>> link; //인접한 진영
bool visit[3001];

int cnt;

int getDistance(int x1, int y1, int x2, int y2)
{
	int d =pow(x1 - x2, 2) + pow(y1 - y2, 2);
	return d;
}

void BFS()
{
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		visit[cur] = true;

		for (int i = 0; i < link[cur].size(); i++)
		{
			if (!visit[link[cur][i]])
			{
				visit[link[cur][i]] = true;
				q.push(link[cur][i]);
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
		cin >> N;
		int x, y, R;
		cnt = 0;


		for (int i = 0; i < N; i++)
		{
			visit[i] = false;
		}
		v.clear();
		link.clear();
		link.resize(3001);


		for (int i = 0; i < N; i++)
		{
			cin >> x >> y >> r[i];
			v.push_back(make_pair(x, y));
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i != j)//서로 다른 진영일 때
				{
					if (pow(r[i] + r[j],2) >= getDistance(v[i].first, v[j].first, v[i].second, v[j].second)) //두 진영 거리가 통신가능 거리보다 작거나 같을 때
					{
						link[i].push_back(j);
					}
				}
			}
		}

		for (int i = 0; i < N; i++)
		{
			if (!visit[i])
			{
				q.push(i);
				BFS();
				cnt++;
			}
		}

		cout << cnt << "\n";
		
	}


	return 0;
}