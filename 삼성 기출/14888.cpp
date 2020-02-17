#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[101];
int cmd[4];
int ans1 = -1000000001; //최댓값
int ans2 = 1000000001; //최솟값

void dfs(int plus, int minus, int multiply, int devide, int sum, int cnt)
{
	if (cnt == N)
	{
		ans1 = max(ans1, sum);
		ans2 = min(ans2, sum);
	}

	
	if (plus > 0)
	{
		dfs(plus-1, minus, multiply, devide, sum+arr[cnt], cnt+1);
	}
	if (minus > 0)
	{
		dfs(plus, minus - 1, multiply, devide, sum - arr[cnt], cnt + 1);
	}
	if (multiply > 0)
	{
		dfs(plus, minus, multiply - 1, devide, sum * arr[cnt], cnt + 1);

	}
	if (devide > 0)
	{
		dfs(plus, minus, multiply, devide - 1, sum / arr[cnt], cnt + 1);

	}

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//입력
	//첫째 줄에 수의 개수 N(2 ≤ N ≤ 11)가 주어진다.둘째 줄에는 A1, A2, ..., AN이 주어진다. 
	//(1 ≤ Ai ≤ 100) 셋째 줄에는 합이 N - 1인 4개의 정수가 주어지는데, 
	//차례대로 덧셈(+)의 개수, 뺄셈(-)의 개수, 곱셈(×)의 개수, 나눗셈(÷)의 개수이다.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> cmd[i];
	}

	//출력
	//첫째 줄에 만들 수 있는 식의 결과의 최댓값을, 둘째 줄에는 최솟값을 출력한다.
	//최댓값과 최솟값이 항상 - 10억보다 크거나 같고, 10억보다 작거나 같은 결과가 나오는 입력만 주어진다.
	//또한, 앞에서부터 계산했을 때, 중간에 계산되는 식의 결과도 항상 - 10억보다 크거나 같고, 
	//10억보다 작거나 같다.

	dfs(cmd[0], cmd[1], cmd[2], cmd[3], arr[0], 1);
	cout << ans1 << "\n";
	cout << ans2 << "\n";

	return 0;
}