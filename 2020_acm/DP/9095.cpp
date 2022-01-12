#include <iostream>
#define MAX 11
using namespace std;
int arr[MAX] = { 0, 1, 2, 4, };
int dp(int n)
{
	if (arr[n])
		return arr[n];
	arr[n] = dp(n - 1) + dp(n - 2) + dp(n - 3);
	return arr[n];
}
int main()
{
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
	{
		int num;
		cin >> num;
		cout << dp(num) << "\n";
	}
	return 0;
}