#include <stdint.h>
#include <stdio.h>
int add(int a,int b);
int mul(int a,int b);
int data=10;
int add(int a,int b)
{
	int sum;
	sum=a+b;
	return sum;
}
int mul(int a,int b)
{
	int prod;
	prod=a*b;
	return prod;

}

int main(void)
{

	int a=20,b=20,sum,prod;

    printf("Add two numbers \n");
    fflush(stdout);

    sum=add(a,b);
    printf("Sum of two numbers %d \n",sum);
    fflush(stdout);

    printf("Multiply two numbers \n");
    fflush(stdout);

    prod=mul(a,b);
    printf("Prod of two numbers %d \n",prod);
data=data+5;
    fflush(stdout);

	return 0;
}
