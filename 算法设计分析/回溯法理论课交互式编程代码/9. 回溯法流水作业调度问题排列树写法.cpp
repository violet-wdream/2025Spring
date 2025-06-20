#include <iostream>
#include <cmath>
#define MAXN 1001
#define MAXINT 2147483647

int n;
int a[MAXN], b[MAXN]; //��������
int f1, f2[MAXN];	//��ˮ����ҵ��ʱ��
int x[MAXN];		//��ʱ��
int bestx[MAXN];	//���Ž�
int bestf;	//���Ž�ĳɱ�

void swap(int& a, int& b) { int temp; temp = a; a = b; b = temp; }

void dfs(int i)			//�ӵ�i�㿪ʼ����
{
    if (i > n)				//����Ҷ���,����һ�ֵ��ȷ���
    {
        if (f2[n] < bestf)		//�ҵ����Ž�
        {
            bestf = f2[n];
            for (int j = 1; j <= n; j++)	//���ƽ�����
                bestx[j] = x[j];
        }
    }
    else
    {
        for (int j = i; j <= n; j++)		//û�е���Ҷ���,���ǿ��ܵ���ҵ
        {
            swap(x[i], x[j]);
            f1 += a[x[i]];		//ѡ����ҵx[i],��M1��ִ�����ʱ��
            f2[i] = std::max(f1, f2[i - 1]) + b[x[i]];
            if (f2[i] < bestf)		//��֦
                dfs(i + 1);
            f1 -= a[x[i]];		//����
            swap(x[i], x[j]);
        }
    }
}


int main()
{
    while (scanf("%d", &n), n != 0)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d %d", &a[i], &b[i]);
            x[i] = i;
        }
        f1 = 0; bestf = MAXINT;
        dfs(1);
        printf("Total time: %d\nTasks order: ", bestf);
        for (int i = 1; i <= n; i++) std::cout << bestx[i] << ' ';
        printf("\n");
    }
    return 0;
}