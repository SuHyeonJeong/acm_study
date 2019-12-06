#include <iostream>
#include <algorithm>
using namespace std;
int N;
int T[16];
int P[16];
int answer;
int DFS(int idx)
{
	//����, N+1��°���� ȸ�翡 ���� ������, 6, 7�Ͽ� �ִ� ����� �� �� ����.
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
	//�Է�
	//ù° �ٿ� N (1 �� N �� 15)�� �־�����.
	//��° �ٺ��� N���� �ٿ� Ti�� Pi�� �������� ���еǾ �־�����, 1�Ϻ��� N�ϱ��� ������� �־�����. (1 �� Ti �� 5, 1 �� Pi �� 1,000)
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> T[i] >> P[i];
	}


	for (int i = 1; i <= N; i++)
	{
		answer = max(answer, DFS(i));
	}

	//ù° �ٿ� �����̰� ���� �� �ִ� �ִ� ������ ����Ѵ�.
	cout << answer;
	return 0;
}