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

void dfs(int i, int tw, int tv)
{

}

int main()
{
    // ��������
    scanf("%d %d", &n, &W);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &w[i], &v[i]);

    memset(op, 0, sizeof(op));
    dfs(0, 0, 0);

    printf("Total value: %d\nSelected objects: ", maxv);
    for (int i = 0; i < n; i++)
        if (x[i]) cout << i + 1 << ' ';
}