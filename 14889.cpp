//�౸�� �ϱ� ���� ���� ����� �� N���̰� �ű��ϰԵ� N�� ¦���̴�.
//���� N / 2������ �̷���� ��ŸƮ ���� ��ũ ������ ������� ������ �Ѵ�.
//BOJ�� ��ϴ� ȸ�� ��� ������� ��ȣ�� 1���� N������ �����߰�, �Ʒ��� ���� �ɷ�ġ�� �����ߴ�.
//�ɷ�ġ Sij�� i�� ����� j�� ����� ���� ���� ������ ��, ���� �������� �ɷ�ġ�̴�.
//���� �ɷ�ġ�� ���� ���� ��� ���� �ɷ�ġ Sij�� ���̴�.
//Sij�� Sji�� �ٸ� ���� ������, i�� ����� j�� ����� ���� ���� ������ ��, ���� �������� �ɷ�ġ�� Sij�� Sji�̴�.
//N = 4�̰�, S�� �Ʒ��� ���� ��츦 ���캸��.
//	1	2	3	4
//1	 	1	2	3
//2	4	 	5	6
//3	7	1	 	2
//4	3	4	5
//���� ���, 1, 2���� ��ŸƮ ��, 3, 4���� ��ũ ���� ���� ��쿡 �� ���� �ɷ�ġ�� �Ʒ��� ����.
//��ŸƮ �� : S12 + S21 = 1 + 4 = 5
//��ũ �� : S34 + S43 = 2 + 5 = 7
//1, 3���� ��ŸƮ ��, 2, 4���� ��ũ ���� ���ϸ�, �� ���� �ɷ�ġ�� �Ʒ��� ����.
//��ŸƮ �� : S13 + S31 = 2 + 7 = 9
//��ũ �� : S24 + S42 = 6 + 4 = 10
//�౸�� ����ְ� �ϱ� ���ؼ� ��ŸƮ ���� �ɷ�ġ�� ��ũ ���� �ɷ�ġ�� ���̸� �ּҷ� �Ϸ��� �Ѵ�.���� ������ ���� ��쿡�� 1, 4���� ��ŸƮ ��, 2, 3�� ���� ��ũ ���� ���ϸ� ��ŸƮ ���� �ɷ�ġ�� 6, ��ũ ���� �ɷ�ġ�� 6�� �Ǿ ���̰� 0�� �ǰ� �� ���� �ּ��̴�.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int arr[21][21];
bool visit[21];
int answer = 999999999;
//cur_player�� ������ ��ŸƮ������ ���� cnt�� ���� ���
void DFS(int cur_player, int cnt)
{
	//���� N/2�� �� �̾����� ���� ��� 
	if (cnt == N / 2)
	{
		vector<int> link, start;

		//���� �������� start �ƴϸ� link��
		for (int i = 0; i < N; i++)
		{
			if (visit[i])
				start.push_back(i);
			else
				link.push_back(i);
		}

		int stat_start = 0, stat_link = 0;
		for (int i = 0; i < start.size(); i++)
		{
			for (int j = i + 1; j < start.size(); j++)
			{
				int start_x = start[i];
				int start_y = start[j];
				int link_x = link[i];
				int link_y = link[j];
				stat_start += arr[start_x][start_y] + arr[start_y][start_x];
				stat_link += arr[link_x][link_y] + arr[link_y][link_x];
			}
		}

		answer = min(answer, abs(stat_link - stat_start));
		return;
	}
	for (int i = cur_player + 1; i < N; i++)
	{
		if (!visit[i])
		{
			visit[i] = true;
			DFS(i, cnt + 1);
			visit[i] = false;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//�Է�
	//ù° �ٿ� N(4 �� N �� 20, N�� ¦��)�� �־�����.��° �ٺ��� N���� �ٿ� S�� �־�����.
	//�� ���� N���� ���� �̷���� �ְ�, i�� ���� j��° ���� Sij �̴�.
	//Sii�� �׻� 0�̰�, ������ Sij�� 1���� ũ�ų� ����, 100���� �۰ų� ���� �����̴�.
	
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> arr[i][j];
		}
	}

	DFS(0, 0);

	//���
	//ù° �ٿ� ��ŸƮ ���� ��ũ ���� �ɷ�ġ�� ������ �ּڰ��� ����Ѵ�.

	cout << answer << "\n";

	return 0;
}