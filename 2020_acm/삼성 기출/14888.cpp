#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[101];
int cmd[4];
int ans1 = -1000000001; //�ִ�
int ans2 = 1000000001; //�ּڰ�

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
	//�Է�
	//ù° �ٿ� ���� ���� N(2 �� N �� 11)�� �־�����.��° �ٿ��� A1, A2, ..., AN�� �־�����. 
	//(1 �� Ai �� 100) ��° �ٿ��� ���� N - 1�� 4���� ������ �־����µ�, 
	//���ʴ�� ����(+)�� ����, ����(-)�� ����, ����(��)�� ����, ������(��)�� �����̴�.
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> cmd[i];
	}

	//���
	//ù° �ٿ� ���� �� �ִ� ���� ����� �ִ���, ��° �ٿ��� �ּڰ��� ����Ѵ�.
	//�ִ񰪰� �ּڰ��� �׻� - 10�ﺸ�� ũ�ų� ����, 10�ﺸ�� �۰ų� ���� ����� ������ �Է¸� �־�����.
	//����, �տ������� ������� ��, �߰��� ���Ǵ� ���� ����� �׻� - 10�ﺸ�� ũ�ų� ����, 
	//10�ﺸ�� �۰ų� ����.

	dfs(cmd[0], cmd[1], cmd[2], cmd[3], arr[0], 1);
	cout << ans1 << "\n";
	cout << ans2 << "\n";

	return 0;
}