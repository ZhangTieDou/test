#include <stdio.h>

void func(int *a)
{
    static int b = 3;
    *a += b;
    b++;
    printf("b=%d\n",b);
}

int main()
{
    int k = 2;
    func(&k);
    printf("%d\n",k);
    func(&k);
    printf("%d\n",k);
	
	return 0;
}