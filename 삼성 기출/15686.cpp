#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>
using namespace std;
//ũ�Ⱑ N��N�� ���ð� �ִ�.���ô� 1��1ũ���� ĭ���� �������� �ִ�.
int N, M;
int map[51][51];
bool check[13];
vector <pair<int, int>> house; //�� �� ��ǥ
vector <pair<int, int>> chicken; //�� ġŲ�� ��ǥ

int answer = INT_MAX;
void DFS(int idx, int cnt)
{
	if (idx > chicken.size())
		return;

	if (cnt == M)
	{
		int sum = 0;
		for (int i = 0; i < house.size(); i++)
		{
			int dist = INT_MAX;
			for (int j = 0; j < chicken.size(); j++)
			{
				if (check[j])
				{
					int d = abs(house[i].first - chicken[j].first) + abs(house[i].second - chicken[j].second);
					dist = min(dist, d);
				}
			}
			sum += dist;
		}
		answer = min(answer, sum);
		return;
	}


	//����Ž��
	for (int i = idx; i < chicken.size(); i++)
	{
		if (!check[i])
		{
			check[i] = true;
			DFS(i, cnt + 1);
			check[i] = false;
		}

	}
	
}
//������ �� ĭ�� �� ĭ, ġŲ��, �� �� �ϳ��̴�.
//0�� �� ĭ, 1�� ��, 2�� ġŲ���̴�.
//������ ĭ��(r, c)�� ���� ���·� ��Ÿ����, r�� c�� �Ǵ� ���������� r��° ĭ, ���ʿ������� c��° ĭ�� �ǹ��Ѵ�.
//r�� c�� 1���� �����Ѵ�.
//�� ���ÿ� ��� ������� ġŲ�� �ſ� �����Ѵ�.����, ������� "ġŲ �Ÿ�"��� ���� �ַ� ����Ѵ�.
//ġŲ �Ÿ��� ���� ���� ����� ġŲ�� ������ �Ÿ��̴�.
//��, ġŲ �Ÿ��� ���� �������� ��������, ������ ���� ġŲ �Ÿ��� ������ �ִ�.
//������ ġŲ �Ÿ��� ��� ���� ġŲ �Ÿ��� ���̴�.
//������ �� ĭ(r1, c1)��(r2, c2) ������ �Ÿ��� | r1 - r2 | +| c1 - c2 | �� ���Ѵ�.
//�� ���ÿ� �ִ� ġŲ���� ��� ���� �����������̴�.���������� ���翡���� ������ ������Ű�� ���� �Ϻ� ġŲ���� �����Ű���� �Ѵ�.
//���� ���� ���� �� ���ÿ��� ���� ������ ���� �� �� �ִ�  ġŲ���� ������ �ִ� M����� ����� �˾Ƴ�����.
//���ÿ� �ִ� ġŲ�� �߿��� �ִ� M���� ����, ������ ġŲ���� ��� ������Ѿ� �Ѵ�.
//��� ����, ������ ġŲ �Ÿ��� ���� �۰� ���� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

//���
//ù° �ٿ� �����Ű�� ���� ġŲ���� �ִ� M���� ����� ��, ������ ġŲ �Ÿ��� �ּڰ��� ����Ѵ�.
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//ù° �ٿ� N(2 �� N �� 50)�� M(1 �� M �� 13)�� �־�����.
	cin >> N >> M;

	//��° �ٺ��� N���� �ٿ��� ������ ������ �־�����.
	//������ ������ 0, 1, 2�� �̷���� �ְ�, 0�� �� ĭ, 1�� ��, 2�� ġŲ���� �ǹ��Ѵ�.
	//���� ������ 2N���� ���� ������, ��� 1���� �����Ѵ�.ġŲ���� ������ M���� ũ�ų� ����, 13���� �۰ų� ����.
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 1)
			{
				house.push_back(make_pair(i, j));
			}
			else if (map[i][j] == 2)
			{
				chicken.push_back(make_pair(i, j));
			}
		}
	}

	DFS(0, 0);
	cout << answer << "\n";

	return 0;
}