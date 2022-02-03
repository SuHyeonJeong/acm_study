#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct INFO
{
    int ry, rx, by, bx, cnt;
};

int N, M;
const int MAX = 11;

char map[MAX][MAX];
bool visit[MAX][MAX][MAX][MAX];


int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

queue<INFO> q;

INFO start;

int BFS()
{
    //����
    //��ŸƮ��ũ���� �Ǹ��ϴ� ��̿� �峭�� �߿��� ���� �αⰡ ���� ��ǰ�� ���� Ż���̴�.
    //���� Ż���� ���簢�� ���忡 ���� ������ �Ķ� ������ �ϳ��� ���� ����, ���� ������ ������ ���� ������ �����̴�.

    //������ ���� ũ��� N, ���� ũ��� M�̰�, ���ǻ� 1��1ũ���� ĭ���� �������� �ִ�.���� �ٱ� ��� ���� ��� ������ �ְ�, ���忡�� ������ �ϳ� �ִ�.
    //���� ������ �Ķ� ������ ũ��� ���忡�� 1��1ũ���� ĭ�� ���� ä��� �������̰�, ���� �ϳ��� �� �ִ�.������ ��ǥ�� ���� ������ ������ ���ؼ� ������ ���̴�.�̶�, �Ķ� ������ ���ۿ� ���� �� �ȴ�.

    //�̶�, ������ ������ �ǵ帱 ���� ����, �߷��� �̿��ؼ� �̸� ���� ������ �Ѵ�.�������� ����̱�, ���������� ����̱�, �������� ����̱�, �Ʒ������� ����̱�� ���� �� ���� ������ �����ϴ�.

    //������ ���ۿ��� ���� ���ÿ� �����δ�.���� ������ ���ۿ� ������ ����������, �Ķ� ������ ���ۿ� ������ �����̴�.���� ������ �Ķ� ������ ���ÿ� ���ۿ� ������ �����̴�.
    //���� ������ �Ķ� ������ ���ÿ� ���� ĭ�� ���� �� ����.��, ���� ������ �Ķ� ������ ũ��� �� ĭ�� ��� �����Ѵ�.����̴� ������ �׸��ϴ� ���� �� �̻� ������ �������� ���� �� �����̴�.

    //������ ���°� �־����� ��, �ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

    int ret = -1;

    while (!q.empty())
    {
        int ry = q.front().ry;
        int rx = q.front().rx;
        int by = q.front().by;
        int bx = q.front().bx;
        int cnt = q.front().cnt;

        q.pop();

        if (cnt > 10)
            break;

        if (map[ry][rx] == 'O' && map[by][bx] != 'O')
        {
            ret = cnt;
            break;
        }



        for (int dir = 0; dir < 4; dir++)
        {
            int nry = ry;
            int nrx = rx;
            int nby = by;
            int nbx = bx;

            //���� ��
            while (1)
            {
                if (map[nry][nrx] != '#' && map[nry][nrx] != 'O')
                {
                    nry += dy[dir];
                    nrx += dx[dir];
                }
                else
                {
                    if (map[nry][nrx] == '#')
                    {
                        nry -= dy[dir];
                        nrx -= dx[dir];
                    }
                    break;
                }


            }

            //�Ķ� ��
            while (1)
            {
                if (map[nby][nbx] != '#' && map[nby][nbx] != 'O')
                {
                    nby += dy[dir];
                    nbx += dx[dir];
                }
                else
                {
                    if (map[nby][nbx] == '#')
                    {
                        nby -= dy[dir];
                        nbx -= dx[dir];
                    }
                    break;
                }
            }

            //���� ���� �Ķ� ���� ��ĥ ��� (���ۿ� ���� ���� ��)
            if (nry == nby && nrx == nbx)
            {
                if (map[nry][nrx] != 'O')
                {
                    //�� ���� ������ �Ÿ��� ����Ѵ�.
                    //�� ���� ������ ���� �� �ڿ� �ִ� ���̴ϱ� �� ���� �� �������� - ����
                    int red_distance = abs(nry - ry) + abs(nrx - rx);
                    int blue_distance = abs(nby - by) + abs(nbx - bx);

                    if (red_distance > blue_distance)
                    {
                        nry -= dy[dir];
                        nrx -= dx[dir];
                    }
                    else
                    {
                        nby -= dy[dir];
                        nbx -= dx[dir];
                    }

                }

            }

            //���� ���� ��ġ�� �ڸ��� �湮���� ���� �ڸ��� ���
            if (visit[nry][nrx][nby][nbx] == 0)
            {
                visit[nry][nrx][nby][nbx] = 1;
                INFO next;
                next.ry = nry;
                next.rx = nrx;
                next.by = nby;
                next.bx = nbx;
                next.cnt = cnt + 1;
                q.push(next);
            }


        }


    }

    return ret;

}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //�Է�
    //ù ��° �ٿ��� ������ ����, ���� ũ�⸦ �ǹ��ϴ� �� ���� N, M(3 �� N, M �� 10)�� �־�����.
    //���� N���� �ٿ� ������ ����� ��Ÿ���� ���� M�� ���ڿ��� �־�����.�� ���ڿ��� '.', '#', 'O', 'R', 'B' �� �̷���� �ִ�. 
    //'.'�� �� ĭ�� �ǹ��ϰ�, '#'�� ���� �̵��� �� ���� ��ֹ� �Ǵ� ���� �ǹ��ϸ�, 'O'�� ������ ��ġ�� �ǹ��Ѵ�. 'R'�� ���� ������ ��ġ, 'B'�� �Ķ� ������ ��ġ�̴�.
    //�ԷµǴ� ��� ������ �����ڸ����� ��� '#'�� �ִ�.������ ������ �� �� �̸�, ���� ������ �Ķ� ������ �׻� 1���� �־�����.

    cin >> N >> M;

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < M; x++)
        {
            cin >> map[y][x];

            if (map[y][x] == 'R')
            {
                start.ry = y;
                start.rx = x;
            }

            if (map[y][x] == 'B')
            {
                start.by = y;
                start.bx = x;
            }
        }

    }


    start.cnt = 0;
    q.push(start);
    visit[start.ry][start.rx][start.by][start.bx] = 1;



    //���
    //�ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ����Ѵ�.����, 10�� ���Ϸ� �������� ���� ������ ������ ���� ���� �� ������ - 1�� ����Ѵ�.


    cout << BFS() << "\n";




    return 0;
}