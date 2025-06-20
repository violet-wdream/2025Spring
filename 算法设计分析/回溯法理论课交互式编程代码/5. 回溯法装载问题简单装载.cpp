#include<iostream>
#include<algorithm>
#include <memory.h>
using namespace std;
#define MAXN 20

int w[] = { 5,2,6,4,3 }; //����װ�����������±�0��Ԫ�ؿ�ʼ
int n = 5, W = 10;
int maxw = 0;		   //������Ž��������
int x[MAXN];		   //������Ž�����
bool op[MAXN];

void dfs(int i, int tw, int rw) //����װ������
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
        if (tw + w[i] <= W)			//���ӽ���֦
        {
            op[i] = 1;			//ѡȡ��i����װ��
            dfs(i + 1, tw + w[i], rw - w[i]);
        }
        if (tw + rw - w[i] > maxw)		//�Һ��ӽ���֦
        {
            op[i] = 0;			//��ѡȡ��i����װ��,����
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

    printf("Best weight: %d\nSelected objects: ", maxw);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}
