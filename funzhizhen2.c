#include <stdio.h>
/*
	��������ʾ�˺���ָ�����ز���
	1.����ָ���������
		1.����������(*��ʶ��)�滻
		2.ȥ���β�����ʣ�ಿ�ֲ���
	2.typedef���Ժ���ָ��Ϊ�����Ļص�����
	3.����ָ��(void*)�䵱����ָ��
	4.ָ������ͣ�	 ��Ч�ڱ���������			ȥ����������ʣ�ಿ��
	5.ָ����ָ�����ͣ�ָ������������������		ȥ����������*��ʣ�ಿ��
*/

//int (*p1)(int, int)		//max�ĺ���ָ��
int max(int a, int b)
{
	printf("max����������\t" );
	return a > b ? a : b;
}

//int (*p2)(int, int)		//min�ĺ���ָ��
int min(int a, int b)
{
	printf("min����������\t");
	return a < b ? a : b;
}

//int (*p3)(int, int)		//sum�ĺ���ָ��
int sum(int a, int b)
{
	printf("sum����������\t");
	return a + b;
}

//�Ժ���ָ��Ϊ�����Ļص�����
//int (*ps)(int, int)		//pfun1 ������һ�������ĺ���ָ��
//void (*pc)(int (*)(int, int), int , int )		//pfun1 �����ĺ���ָ��
void pfun1(int (*pf)(int, int), int a, int b)
{
	printf("�Ժ���ָ��Ϊ�����ĺ���  %d\n", pf(a, b));
}

//ͨ��typedef�� pfun1 ����Ϊ pfun2 ����
//typedef int (*PF)(int, int);
//int pfun2(PF pf, int a, int b)
//{
//	return pf(a, b);
//}

typedef int (*PP)(int, int);
typedef int (*PF)(PP, int, int);
int pfun2(PP pp, int a, int b)
{
	return pp(a, b);
}

void mprint()
{
	printf("void* ��������ָ��\n");
}

int main()
{
	//int a = max(1, 2);	//max�����������÷���
	int (*p1)(int, int) = NULL;
	p1 = max;
	printf("max : %d\n", p1(1, 2));		//p1(1, 2)  ����ָ���һ�ӵ��÷���

	//int b = min(1, 2);	//min�����������÷���
	int (*p2)(int, int) = NULL;
	p2 = min;
	printf("min : %d\n", (*p2)(1, 2));		//(*p2)(1, 2))  ����ָ��ڶ��ӵ��÷���

	//int c = sum(1, 2);	//sum�����������÷���
	int (*p3)(int, int) = NULL;
	p3 = sum;
	printf("min : %d\n", (*p3)(1, 2));
	printf("\n");

	//ͨ�����в�ͬ�ĺ���ָ��������ò�ͬ������ʵ�ֲ�ͬ����
	void (*pc)(int (*)(int, int), int, int) = pfun1;
	pc(max, 1, 2);
	pc(min, 1, 2);
	pc(sum, 1, 2);
	printf("\n");

	//�򻯵�pfun�����ĵ��÷���
	PF pf = pfun2;
	printf("typedef�򻯵�pfun������ max: %d\n", pf(max, 1, 2));
	printf("typedef�򻯵�pfun������ min: %d\n", pf(min, 1, 2));
	printf("typedef�򻯵�pfun������ sum: %d\n", pf(sum, 1, 2));
	printf("\n");

	//void* ��������ָ��
	//void mprint()�ĺ���ָ��Ϊ��void (*p)()	����Ϊ��void (*)()
	void* p = mprint;
	((void (*)())p)();		//void* ��������ָ���һ�ӵ��÷���
	(*(void (*)())p)();		//void* ��������ָ��ڶ��ӵ��÷���

	return 0;
} 