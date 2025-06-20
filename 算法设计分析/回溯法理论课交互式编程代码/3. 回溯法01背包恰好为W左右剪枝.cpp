#include<iostream>
#include <memory.h>
using namespace std;
#define MAXN 100

// n����Ʒ,��������ΪW,w[]���4����Ʒ����,v[]���4����Ʒ��ֵ,�±��0��ʼ
int n, W, w[MAXN], v[MAXN];
// ��������op��¼��i����Ʒ�Ƿ�ѡȡ
bool op[MAXN];

//�������ʾ
bool x[MAXN];			//������ս�
int maxv; 			//������Ž���ܼ�ֵ

void dfs(int i, int tw, int tv, int rw)
{
    if (i == n)				//�ҵ�һ��Ҷ�ӽ��
    {
        if (tw == W && tv > maxv)		//�ҵ�һ�����������ĸ��Ž�,���� 
        {
            maxv = tv;
            for (int j = 0; j < n; j++)
                x[j] = op[j];
        }
    }
    else					//��δ����������Ʒ
    {
        if (tw + w[i] <= W)   //���֦
        {
            op[i] = true;				//ѡȡ��i����Ʒ
            dfs(i + 1, tw + w[i], tv + v[i], rw - w[i]);
        }

        if (tw + rw - w[i] >= W)   //�Ҽ�֦
        {
            op[i] = false;				//��ѡȡ��i����Ʒ,����
            dfs(i + 1, tw, tv, rw - w[i]);
        }

    }
}

int main()
{
    // ��������
    scanf("%d %d", &n, &W);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &w[i], &v[i]);

    memset(op, 0, sizeof(op));

    int rw = 0;
    for (int i = 0; i < n; i++) rw += w[i];

    dfs(0, 0, 0, rw);

    printf("Total value: %d\nSelected objects: ", maxv);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}
