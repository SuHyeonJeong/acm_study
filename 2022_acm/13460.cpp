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
    //문제
    //스타트링크에서 판매하는 어린이용 장난감 중에서 가장 인기가 많은 제품은 구슬 탈출이다.
    //구슬 탈출은 직사각형 보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음, 빨간 구슬을 구멍을 통해 빼내는 게임이다.

    //보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다.가장 바깥 행과 열은 모두 막혀져 있고, 보드에는 구멍이 하나 있다.
    //빨간 구슬과 파란 구슬의 크기는 보드에서 1×1크기의 칸을 가득 채우는 사이즈이고, 각각 하나씩 들어가 있다.게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다.이때, 파란 구슬이 구멍에 들어가면 안 된다.

    //이때, 구슬을 손으로 건드릴 수는 없고, 중력을 이용해서 이리 저리 굴려야 한다.왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.

    //각각의 동작에서 공은 동시에 움직인다.빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다.빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다.
    //빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다.또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다.기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.

    //보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.

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

            //빨간 공
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

            //파란 공
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

            //빨간 공과 파란 공이 겹칠 경우 (구멍에 들어가지 않을 때)
            if (nry == nby && nrx == nbx)
            {
                if (map[nry][nrx] != 'O')
                {
                    //두 공이 움직인 거리를 계산한다.
                    //더 많이 움직인 공이 더 뒤에 있던 공이니까 그 공을 온 방향으로 - 해줌
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

            //현재 공이 위치한 자리가 방문하지 않은 자리일 경우
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

    //입력
    //첫 번째 줄에는 보드의 세로, 가로 크기를 의미하는 두 정수 N, M(3 ≤ N, M ≤ 10)이 주어진다.
    //다음 N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열이 주어진다.이 문자열은 '.', '#', 'O', 'R', 'B' 로 이루어져 있다. 
    //'.'은 빈 칸을 의미하고, '#'은 공이 이동할 수 없는 장애물 또는 벽을 의미하며, 'O'는 구멍의 위치를 의미한다. 'R'은 빨간 구슬의 위치, 'B'는 파란 구슬의 위치이다.
    //입력되는 모든 보드의 가장자리에는 모두 '#'이 있다.구멍의 개수는 한 개 이며, 빨간 구슬과 파란 구슬은 항상 1개가 주어진다.

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



    //출력
    //최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력한다.만약, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 - 1을 출력한다.


    cout << BFS() << "\n";




    return 0;
}