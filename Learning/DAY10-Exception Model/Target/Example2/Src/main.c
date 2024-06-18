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

 
    sum=add(a,b);
 

    prod=mul(a,b);
 
data=data+5;
  

	return 0;
}
