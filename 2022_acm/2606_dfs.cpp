#include <iostream>
using namespace std;

int N, M;
const int MAX = 101;
int graph[MAX][MAX];
bool visit[MAX];
int cnt = 0;


void DFS(int idx)
{
	//���� ���̷����� �� ���̷����� ��Ʈ��ũ�� ���� ���ĵȴ�.�� ��ǻ�Ͱ� �� ���̷����� �ɸ��� �� ��ǻ�Ϳ� ��Ʈ��ũ �󿡼� ����Ǿ� �ִ� ��� ��ǻ�ʹ� �� ���̷����� �ɸ��� �ȴ�.

	//���� ��� 7���� ��ǻ�Ͱ� <�׸� 1>�� ���� ��Ʈ��ũ �󿡼� ����Ǿ� �ִٰ� ����. 
	//1�� ��ǻ�Ͱ� �� ���̷����� �ɸ��� �� ���̷����� 2���� 5�� ��ǻ�͸� ���� 3���� 6�� ��ǻ�ͱ��� ���ĵǾ� 2, 3, 5, 6 �� ���� ��ǻ�ʹ� �� ���̷����� �ɸ��� �ȴ�.
	//������ 4���� 7�� ��ǻ�ʹ� 1�� ��ǻ�Ϳ� ��Ʈ��ũ�󿡼� ����Ǿ� ���� �ʱ� ������ ������ ���� �ʴ´�.



	//��� �� 1�� ��ǻ�Ͱ� �� ���̷����� �ɷȴ�.��ǻ���� ���� ��Ʈ��ũ �󿡼� ���� ����Ǿ� �ִ� ������ �־��� ��, 
	//1�� ��ǻ�͸� ���� �� ���̷����� �ɸ��� �Ǵ� ��ǻ���� ���� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

	for (int i = 1; i <= N; i++)
	{
		if (graph[idx][i] && !visit[i])

		{
			visit[i] = true;
			DFS(i);
			cnt++;
		}
	}


}
int main()
{
	

	//�Է�
	//ù° �ٿ��� ��ǻ���� ���� �־�����.��ǻ���� ���� 100 �����̰� �� ��ǻ�Ϳ��� 1�� ���� ���ʴ�� ��ȣ�� �Ű�����.
	//��° �ٿ��� ��Ʈ��ũ �󿡼� ���� ����Ǿ� �ִ� ��ǻ�� ���� ���� �־�����.�̾ �� ����ŭ �� �ٿ� �� �־� ��Ʈ��ũ �󿡼� ���� ����Ǿ� �ִ� ��ǻ���� ��ȣ ���� �־�����.

	cin >> N >> M;

	for (int i = 1; i <= M; i++)
	{
		int y, x;
		cin >> y >> x;

		graph[y][x] = 1;
		graph[x][y] = 1;
	}

	visit[1] = true;

	DFS(1);

	cout << cnt << "\n";

	//���
	//1�� ��ǻ�Ͱ� �� ���̷����� �ɷ��� ��, 1�� ��ǻ�͸� ���� �� ���̷����� �ɸ��� �Ǵ� ��ǻ���� ���� ù° �ٿ� ����Ѵ�.
	return 0;
}