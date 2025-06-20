#include<iostream>
#include<algorithm>
#include <memory.h>
using namespace std;
#define MAXN 100

// n����Ʒ,��������ΪW,w[]���4����Ʒ����,v[]���4����Ʒ��ֵ,�±��0��ʼ
int n, W, w[MAXN], v[MAXN];
// ��������op��¼��i����Ʒ�Ƿ�ѡȡ
bool op[MAXN];
//d[]����Ʒ�ݼ����򣬵����ı�w[]��v[]��˳��ֻ�Ǽ�¼�������±�
int d[MAXN];
float p[MAXN]; // p[]Ϊv[] / w[]

//�������ʾ
bool x[MAXN];			//������ս�
int maxv; 			//������Ž���ܼ�ֵ

int bound(int i, int tw, int tv)	//���Ͻ�
{
    i++;					//��i+1��ʼ
    while (i < n && tw + w[d[i]] <= W)	//�����Ϊi����Ʒ������������
    {
        tw += w[d[i]];
        tv += v[d[i]];
        i++;
    }
    if (i < n)
        return tv + (W - tw) * p[d[i]];	//���Ϊi����Ʒ������������
    else
        return tv;
}


void dfs(int i, int tw, int tv)
{
    if (i == n)				//�ҵ�һ��Ҷ�ӽ��
    {
        if (tw <= W && tv > maxv)		//�ҵ�һ�����������ĸ��Ž�,���� 
        {
            maxv = tv;
            for (int j = 0; j < n; j++)
                x[j] = op[j];
        }
    }
    else					//��δ����������Ʒ
    {
        if (tw + w[d[i]] <= W)   //���֦
        {
            op[d[i]] = true;				//ѡȡ��d[i]����Ʒ
            dfs(i + 1, tw + w[d[i]], tv + v[d[i]]);
        }

        if (bound(i, tw, tv) > maxv)   //�Ҽ�֦
        {
            op[d[i]] = false;				//��ѡȡ��d[i]����Ʒ,����
            dfs(i + 1, tw, tv);
        }

    }
}

int cmp(const int& a, const int& b)
{
    return p[a] > p[b];
}

int main()
{
    // ��������
    scanf("%d %d", &n, &W);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &w[i], &v[i]);
        p[i] = (float)v[i] / w[i];
        d[i] = i;
    }

    memset(op, 0, sizeof(op));
    sort(d, d + n, cmp);
    dfs(0, 0, 0);

    printf("Total value: %d\nSelected objects: ", maxv);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}
