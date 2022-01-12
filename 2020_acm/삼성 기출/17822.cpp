#include <iostream>
#include <queue>
using namespace std;
int N, M, T;
int arr[51][51]; //������ ����
int temp[51];
int cmd[51][3];
queue<pair<int, int>> q;
int main()
{
	ios_base::sync_with_stdio(false);

	cin.tie(0);

	cout.tie(0);
	//�Է�
	//ù° �ٿ� N, M, T�� �־�����.
	//��° �ٺ��� N���� �ٿ� ���ǿ� ���� ���� �־�����.i��° ���� j��° ����(i, j)�� ���� ���� �ǹ��Ѵ�.
	//���� T���� �ٿ� xi, di, ki�� �־�����.
	//����
	//2 �� N, M �� 50
	//1 �� T �� 50
	//1 �� ���ǿ� ���� �� �� 1, 000
	//2 �� xi �� N
	//0 �� di �� 1
	//1 �� ki < M
	cin >> N >> M >> T;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < T; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> cmd[i][j];
		}
	}

	bool flag = false;

	//cmd
	for (int i = 0; i < T; i++)
	{
		//ȸ��
		if(cmd[i][1])
			cmd[i][2] = M - cmd[i][2];
		//cmd[i][0]�� ����� ȸ�� -> ���
		for (int j = cmd[i][0]-1; j < N; j=j+cmd[i][0])
		{
			for (int k = 0; k < M; k++)
			{
				temp[(k + cmd[i][2]) % M] = arr[j][k];
			}

			for (int k = 0; k < M; k++)
			{
				arr[j][k] = temp[k];
			}
		}

		//������ ���� �� �����
		//�� �� �˻�
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				if (arr[j][k] && arr[j][k] == arr[j][(k + 1) % M])
				{
					q.push(make_pair(j, k));
					q.push(make_pair(j, (k + 1) % M));
				}
			}
		}

		//���Ʒ� �˻�
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				if (arr[j][k] && arr[j][k] == arr[j + 1][k])
				{
					q.push(make_pair(j, k));
					q.push(make_pair(j+1, k));
				}
			}
		}

		//������ �� ������ ��� ���ؼ� +1 or -1
		if (q.empty())
		{
			float sum = 0;
			float node = 0; //0�� �ƴ� ���� ����
			float avg; //��հ�

			for (int k = 0; k < N; k++)
			{
				for (int j = 0; j < M; j++)
				{
					sum += arr[k][j];
					if (arr[k][j] != 0)
						node++;
				}
			}

			avg = sum / node;
			for (int k = 0; k < N; k++)
			{
				for (int j = 0; j < M; j++)
				{
					if (arr[k][j] && arr[k][j] > avg)
						arr[k][j] -= 1;
					else if (arr[k][j] && arr[k][j] < avg)
						arr[k][j] += 1;
				}
			}
		}

		//�����
		else
		{
			while (!q.empty())
			{
				arr[q.front().first][q.front().second] = 0;
				q.pop();
			}
			
		}

		

		
	}

	//���
	//������ T�� ȸ����Ų �� ���ǿ� ���� ���� ���� ����Ѵ�.
	
	
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			sum += arr[i][j];
		}
	}

	cout << sum << "\n";
	return 0;
}