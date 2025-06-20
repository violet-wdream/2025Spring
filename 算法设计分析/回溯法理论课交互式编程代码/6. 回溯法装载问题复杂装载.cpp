#include<iostream>
#include<algorithm>
#include <memory.h>
using namespace std;
#define MAXN 20

int w[] = { 20, 40, 40 }; //����װ�����������±�0��Ԫ�ؿ�ʼ
int n = 3, c1 = 50, c2 = 50;
int maxw = 0;		   //��ŵ�һ�Ҵ����Ž��������
int x[MAXN];		   //��ŵ�һ�Ҵ����Ž�����
bool op[MAXN];

void dfs(int i, int tw, int rw) //���һ�Ҵ��Ľ⣬�ȼ�������װ������
{
    if (i == n)				//�ҵ�һ��Ҷ�ӽ��
    {
        if (tw > maxw)
        {
            maxw = tw;			//�ҵ�һ�����������ĸ��Ž�,������
            for (int j = 0; j < n; j++)	//�������Ž�
                x[j] = op[j];
        }
    }
    else					//��δ�������м�װ��
    {
        if (tw + w[i] <= c1)			//���ӽ���֦
        {
            op[i] = true;			//ѡȡ��i����װ��
            dfs(i + 1, tw + w[i], rw - w[i]);
        }
        if (tw + rw - w[i] > maxw)		//�Һ��ӽ���֦
        {
            op[i] = false;			//��ѡȡ��i����װ��,����
            dfs(i + 1, tw, rw - w[i]);
        }
    }
}

int main()
{
    memset(op, 0, sizeof(op));

    int rw = 0;
    for (int i = 0; i < n; i++) rw += w[i];
    dfs(0, 0, rw);

    int sum = 0;
    for (int i = 0; i < n; i++) //�ۼƵ�һ���ִ�װ���ʣ��ļ�װ������
        if (x[i] == false) sum += w[i];
    if (sum <= c2)
    {
        printf("Find a solution. Load No.");
        for (int i = 0; i < n; i++)
            if (x[i]) cout << i + 1 << ' ';
        printf("onto Ship 1 and put the rest onto Ship 2.\n");
    }
    else
    {
        printf("No solution!\n");
    }
}
