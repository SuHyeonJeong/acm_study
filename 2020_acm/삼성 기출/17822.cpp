#include <iostream>
#include <queue>
using namespace std;
int N, M, T;
int arr[51][51]; //겹쳐진 원판
int temp[51];
int cmd[51][3];
queue<pair<int, int>> q;
int main()
{
	ios_base::sync_with_stdio(false);

	cin.tie(0);

	cout.tie(0);
	//입력
	//첫째 줄에 N, M, T이 주어진다.
	//둘째 줄부터 N개의 줄에 원판에 적힌 수가 주어진다.i번째 줄의 j번째 수는(i, j)에 적힌 수를 의미한다.
	//다음 T개의 줄에 xi, di, ki가 주어진다.
	//제한
	//2 ≤ N, M ≤ 50
	//1 ≤ T ≤ 50
	//1 ≤ 원판에 적힌 수 ≤ 1, 000
	//2 ≤ xi ≤ N
	//0 ≤ di ≤ 1
	//1 ≤ ki < M
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
		//회전
		if(cmd[i][1])
			cmd[i][2] = M - cmd[i][2];
		//cmd[i][0]의 배수만 회전 -> 배수
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

		//인접한 같은 수 지우기
		//양 옆 검사
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

		//위아래 검사
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

		//인접한 수 없으면 평균 구해서 +1 or -1
		if (q.empty())
		{
			float sum = 0;
			float node = 0; //0이 아닌 수의 개수
			float avg; //평균값

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

		//지우기
		else
		{
			while (!q.empty())
			{
				arr[q.front().first][q.front().second] = 0;
				q.pop();
			}
			
		}

		

		
	}

	//출력
	//원판을 T번 회전시킨 후 원판에 적힌 수의 합을 출력한다.
	
	
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