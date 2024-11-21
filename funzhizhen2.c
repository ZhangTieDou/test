#include <stdio.h>
/*
	本程序演示了函数指针的相关操作
	1.函数指针的声明：
		1.将函数名用(*标识符)替换
		2.去掉形参名，剩余部分不动
	2.typedef简化以函数指针为参数的回调函数
	3.万能指针(void*)充当函数指针
	4.指针的类型：	 等效于变量的类型			去掉变量名后剩余部分
	5.指针所指的类型：指针所操作的数据类型		去掉变量名和*后剩余部分
*/

//int (*p1)(int, int)		//max的函数指针
int max(int a, int b)
{
	printf("max函数被调用\t" );
	return a > b ? a : b;
}

//int (*p2)(int, int)		//min的函数指针
int min(int a, int b)
{
	printf("min函数被调用\t");
	return a < b ? a : b;
}

//int (*p3)(int, int)		//sum的函数指针
int sum(int a, int b)
{
	printf("sum函数被调用\t");
	return a + b;
}

//以函数指针为参数的回调函数
//int (*ps)(int, int)		//pfun1 函数第一个参数的函数指针
//void (*pc)(int (*)(int, int), int , int )		//pfun1 函数的函数指针
void pfun1(int (*pf)(int, int), int a, int b)
{
	printf("以函数指针为参数的函数  %d\n", pf(a, b));
}

//通过typedef简化 pfun1 函数为 pfun2 函数
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
	printf("void* 操作函数指针\n");
}

int main()
{
	//int a = max(1, 2);	//max函数基本调用方法
	int (*p1)(int, int) = NULL;
	p1 = max;
	printf("max : %d\n", p1(1, 2));		//p1(1, 2)  函数指针第一钟调用方法

	//int b = min(1, 2);	//min函数基本调用方法
	int (*p2)(int, int) = NULL;
	p2 = min;
	printf("min : %d\n", (*p2)(1, 2));		//(*p2)(1, 2))  函数指针第二钟调用方法

	//int c = sum(1, 2);	//sum函数基本调用方法
	int (*p3)(int, int) = NULL;
	p3 = sum;
	printf("min : %d\n", (*p3)(1, 2));
	printf("\n");

	//通过三中不同的函数指针参数调用不同函数，实现不同功能
	void (*pc)(int (*)(int, int), int, int) = pfun1;
	pc(max, 1, 2);
	pc(min, 1, 2);
	pc(sum, 1, 2);
	printf("\n");

	//简化的pfun函数的调用方法
	PF pf = pfun2;
	printf("typedef简化的pfun函数的 max: %d\n", pf(max, 1, 2));
	printf("typedef简化的pfun函数的 min: %d\n", pf(min, 1, 2));
	printf("typedef简化的pfun函数的 sum: %d\n", pf(sum, 1, 2));
	printf("\n");

	//void* 操作函数指针
	//void mprint()的函数指针为：void (*p)()	类型为：void (*)()
	void* p = mprint;
	((void (*)())p)();		//void* 当做函数指针第一钟调用方法
	(*(void (*)())p)();		//void* 当做函数指针第二钟调用方法

	return 0;
} 