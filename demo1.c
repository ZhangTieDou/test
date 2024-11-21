#include <stdio.h>

int main()
{
	int arr[5] = { 1,2,3,4,5 };
	int a = *(*(&arr + 1) - 1);

	printf("%d\n\n", a);
	
	printf("%p\n\n", &arr);
	printf("%p\n", &arr[4] + 1);
	printf("%p\n", *(&arr + 1));
	printf("%p\n", &arr+1);
	
	return 0;
}