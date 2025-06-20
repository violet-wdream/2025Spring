#include <iostream>
#define MAXN 20
#define MAXINT 2147483647

int n = 4;
int c[MAXN][MAXN] = { {0},{0,9,2,7,8},{0,6,4,3,7},
                   {0,5,8,1,8},{0,7,6,9,4} };
//�±�0��Ԫ�ز��ã�c[i][j]��ʾ��i����ִ�е�j������ĳɱ�

int x[MAXN];		//��ʱ��
int cost = 0;		//��ʱ��ĳɱ�
int bestx[MAXN];	//���Ž�
int mincost = MAXINT;	//���Ž�ĳɱ�

void swap(int& a, int& b) { int temp; temp = a; a = b; b = temp; }

void dfs(int i)			//�ý�ռ���Ϊ�������ķ������
{
    if (i > n)				//����Ҷ�ӽ��
    {
        cost = 0;  //��cost
        for (int j = 1; j <= n; j++) cost += c[j][x[j]];
        if (cost < mincost)		//�Ƚ������Ž�
        {
            mincost = cost;
            for (int j = 1; j <= n; j++)
                bestx[j] = x[j];
        }
    }
    else
    {
        for (int j = i; j <= n; j++)		//��̽��Աi��j��������
        {
            swap(x[i], x[j]);
            dfs(i + 1);
            swap(x[i], x[j]);  // ����
        }
    }
}

int main()
{
    for (int i = 1; i <= n; i++) x[i] = i;
    dfs(1);
    printf("Total cost: %d\nTasks order: ", mincost);
    for (int i = 1; i <= n; i++) std::cout << bestx[i] << ' ';
	return 0;
}