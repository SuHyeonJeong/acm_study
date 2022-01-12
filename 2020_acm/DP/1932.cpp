#include <iostream>
#include <algorithm>
using namespace std;
int arr[501][501];
int ans[501][501];
int answer = -1;
int dp(int y, int x)
{
	if (ans[y][x] != -1)
		return ans[y][x];

	if (x == 0)
	{
		ans[y][x] = arr[y][x] + dp(y-1,x);
	}
	else if (x == y)
	{
		ans[y][x] = arr[y][x] + dp(y - 1, x-1);
	}
	else
	{
		if(dp(y - 1, x - 1) > dp(y - 1, x))
			ans[y][x] = arr[y][x] + dp(y - 1, x - 1);
		else
			ans[y][x] = arr[y][x] + dp(y - 1, x);
	}

	return ans[y][x];
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			cin >> arr[i][j];
			ans[i][j] = -1;
		}
	}

	ans[0][0] = arr[0][0];
	for (int i = 0; i < n; i++)
	{
		answer = max(answer,dp(n - 1, i));
	}

	cout << answer << "\n";
	return 0;
}