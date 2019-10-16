#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int r, c, k;
int row, col;
int arr[101][101];
int time = 0;
void R()
{
	time++;

	int tempcol=0;
	//<개수, 해당숫자>
	for (int i = 1; i <= row; i++)
	{
		vector<pair<int, int>> v;

		int start = 1;

		while (1)
		{
			if (arr[i][start] != 0)
			{
				v.push_back(make_pair(1, arr[i][start]));
				break;
			}
			else
			{
				start++;
			}
		}
		for (int j = start+1; j <= col; j++)
		{
			if (arr[i][j] == 0)
				continue;
			bool flag = false;
			for (int k = 0; k < v.size(); k++)
			{
				if (v[k].second == arr[i][j])
				{
					v[k].first++;
					flag = true;
					break;
				}
				
			}
			if (!flag)
			{
				v.push_back(make_pair(1, arr[i][j]));
			}
		}

		int s = v.size() * 2;
		tempcol = max(tempcol, s);
		sort(v.begin(), v.end());
		

		int cnt = 0;
		for (int j = 1; j <= tempcol; j++)
		{
			if (cnt >= v.size())
			{
				arr[i][j] = 0;
			}
			else
			{
				arr[i][j] = v[cnt].second;
				arr[i][j + 1] = v[cnt].first;
				j++;
				cnt++;
			}
			
		}

		for (int j = tempcol + 1; j < 101; j++)
		{
			if (arr[i][j] == 0)
			{
				break;
			}
			else
			{
				arr[i][j] = 0;
			}
		}
	}

	col = max(col, tempcol);
	
}
void C()
{
	time++;

	int temprow = 0;
	//<개수, 해당숫자>
	for (int i = 1; i <= col; i++)
	{
		vector<pair<int, int>> v;
		int start = 1;

		while (1)
		{
			if (arr[start][i] != 0)
			{
				v.push_back(make_pair(1, arr[start][i]));
				break;
			}
			else
			{
				start++;
			}
		}
		
		for (int j = start+1; j <= row; j++) //맨앞이 0이면 start+1부터 시작해서 1부터 못넣음
		{
			if (arr[j][i] == 0)
				continue;
			bool flag = false;
			for (int k = 0; k < v.size(); k++)
			{
				if (v[k].second == arr[j][i])
				{
					v[k].first++;
					flag = true;
					break;
				}
				
			}
			if (!flag)
			{
				v.push_back(make_pair(1, arr[j][i]));
			}
		}

		int s = v.size() * 2;
		temprow = max(temprow, s);
		sort(v.begin(), v.end());


		int cnt = 0;
		for (int j = 1; j <= temprow; j++)
		{
			if (cnt >= v.size())
			{
				arr[j][i] = 0;
			}
			else
			{
				arr[j][i] = v[cnt].second;
				arr[j+1][i] = v[cnt].first;
				j++;
				cnt++;
			}

		}

		for (int j = temprow + 1; j < 101; j++)
		{
			if (arr[j][i] == 0)
			{
				break;
			}
			else
			{
				arr[j][i] = 0;
			}
		}
	}

	row = max(row, temprow);

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> r >> c >> k;

	row = col = 3;

	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			cin >> arr[i][j];
		}
	}

	while (1)
	{
		if (arr[r][c] == k)
		{
			break;
		}

		if (time > 100)
		{
			cout << -1 << "\n";
			return 0;
		}

		if (row >= col)
		{
			R();
		}
		else
		{
			C();
		}
	}


	cout << time << "\n";
	return 0;
}