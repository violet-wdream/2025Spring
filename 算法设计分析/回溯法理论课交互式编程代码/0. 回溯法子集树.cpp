// �Ӽ���
//int x[n];			   //x��Ž�������ȫ�ֱ���
//void backtrack(int i)		   //����Ӽ����ĵݹ���
//{
//    if (i > n)			   //������Ҷ�ӽ��,���һ�����н�
//        ������;
//    else
//    {
//        for (j = �½�; j <= �Ͻ�; j++)   //��jö��i���п��ܵ�ѡ��
//        {
//            x[i] = j;		   //����һ�����ܵĽ����
//            ��			   //��������
//                if (constraint(i) && bound(i))
//                    backtrack(i + 1);	   //����Լ���������޽纯��,������һ��
//        }
//    }
//}



// ���ݼ�
//#include<iostream>
//#include <memory.h>
//using namespace std;
//#define MAXN 20
//
//void dfs(int a[], int n, int i, bool x[])
////�����㷨�������x
//{
//    if (i >= n)
//    {
//        /*dispasolution(a, n, x);*/
//        for (int i = 0; i < n; i++)
//            if (x[i]) cout << a[i] << ' ';
//        cout << endl;
//    }
//
//    else
//    {
//        x[i] = false; dfs(a, n, i + 1, x);		//��ѡ��a[i]
//        x[i] = true; dfs(a, n, i + 1, x);		//ѡ��a[i]
//    }
//}
//
//int main()
//{
//    int n = 3;
//    int a[] = { 1,2,3 };
//    bool x[MAXN];
//    memset(x, 0, sizeof(x));
//    dfs(a, n, 0, x);
//    return 0;
//}

