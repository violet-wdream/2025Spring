#include<iostream>
#include <cmath>
#define MAXN 20

int q[MAXN], ret = 0;

void dispasolution(int n)
{
    printf("Solution #%d:\n", ++ret);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < q[i]; j++) printf(". ");
        printf("o ");
        for (int j = q[i] + 1; j <= n; j++) printf(". ");
        printf("\n");
    }
}

bool place(int i)	//���Ե�i�е�q[i]�����ܷ�ڷŻʺ�
{
    int j = 1;
    if (i == 1) return true;
    while (j < i)			//j=1��i-1���ѷ����˻ʺ����
    {
        if ((q[j] == q[i]) || (std::abs(q[j] - q[i]) == abs(j - i)))
            //�ûʺ��Ƿ�����ǰ�ʺ�ͬ�У�λ��(j,q[j])��(i,q[i])�Ƿ�ͬ�Խ���
            return false;
        j++;
    }
    return true;
}

void Queens(int n)	//���n�ʺ�����
{
    int i = 1;		//i��ʾ��ǰ��,Ҳ��ʾ���õ�i���ʺ�
    q[i] = 0;		//q[i]�ǵ�ǰ��,ÿ���¿��ǵĻʺ��ʼλ����Ϊ0��
    while (i >= 1)	//��δ���ݵ�ͷ��ѭ��
    {
        q[i]++;		//ԭλ�ú��ƶ�һ��
        while (q[i] <= n && !place(i))  //��̽һ��λ��(i,q[i])
            q[i]++;
        if (q[i] <= n)	//Ϊ��i���ʺ��ҵ���һ������λ��(i,q[i])
        {
            if (i == n)	//�����������лʺ�,���һ����
                dispasolution(n);
            else		//�ʺ�û�з�����
            {
                i++;	//ת����һ��,����ʼ��һ���»ʺ�ķ���
                q[i] = 0;	//ÿ���¿��ǵĻʺ��ʼλ����Ϊ0��
            }
        }
        else i--; 	//����i���ʺ��Ҳ������ʵ�λ��,����ݵ���һ���ʺ�
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    Queens(n);
    return 0;
}