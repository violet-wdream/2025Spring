// ������
//int x[n];			//x��Ž�����������ʼ��
//void backtrack(int i)		//����������ĵݹ���
//{
//    if (i > n)			//������Ҷ�ӽ��,���һ�����н�
//        ������;
//    else
//    {
//        for (j = i; j <= n; j++)	//��jö��i���п��ܵ�ѡ��
//        {
//            ��			//��i��Ľ��ѡ��x[j]�Ĳ���
//                swap(x[i], x[j]);	//Ϊ��֤������ÿ��Ԫ�ز�ͬ,ͨ��������ʵ��
//            if (constraint(i) && bound(i))
//                backtrack(i + 1);	//����Լ���������޽纯����������һ��
//            swap(x[i], x[j]);	//�ָ�״̬
//            ��			//��i��Ľ��ѡ��x[j]�Ļָ�����
//        }
//    }
//}




// ��ȫ����
//#include<iostream>
//#include <memory.h>
//using namespace std;
//#define MAXN 20
//
//void swap(int &a, int &b)
//{
//    int temp;
//    temp = a;
//    a = b;
//    b = temp;
//}
//
//void dfs(int a[], int n, int i)
////�����㷨�������x
//{
//    if (i >= n)
//    {
//        /*dispasolution(a, n, x);*/
//        for (int i = 0; i < n; i++)
//            cout << a[i] << ' ';
//        cout << endl;
//    }
//
//    else
//    {
//        for (int j = i; j < n; j++)
//        {
//            swap(a[i], a[j]);		//����a[i]��a[j]
//            dfs(a, n, i + 1);
//            swap(a[i], a[j]);		//����a[i]��a[j]���ָ�
//        }
//    }
//}
//
//int main()
//{
//    int n = 3;
//    int a[] = { 1,2,3 };
//    dfs(a, n, 0);
//    return 0;
//}

