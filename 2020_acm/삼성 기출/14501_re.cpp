#include <iostream>
#include <algorithm>
using namespace std;
int N;
int T[16];
int P[16];
int answer;
int DFS(int idx)
{
	//또한, N+1일째에는 회사에 없기 때문에, 6, 7일에 있는 상담을 할 수 없다.
	if (T[idx] + idx > N + 1)
		return 0;

	int result = P[idx];
	int sum = 0;
	for (int i = idx + T[idx]; i <= N; i++)
	{
		sum = max(sum, DFS(i));
	}

	return result + sum;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//입력
	//첫째 줄에 N (1 ≤ N ≤ 15)이 주어진다.
	//둘째 줄부터 N개의 줄에 Ti와 Pi가 공백으로 구분되어서 주어지며, 1일부터 N일까지 순서대로 주어진다. (1 ≤ Ti ≤ 5, 1 ≤ Pi ≤ 1,000)
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> T[i] >> P[i];
	}


	for (int i = 1; i <= N; i++)
	{
		answer = max(answer, DFS(i));
	}

	//첫째 줄에 백준이가 얻을 수 있는 최대 이익을 출력한다.
	cout << answer;
	return 0;
}