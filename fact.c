#include<stdio.h>
int main()
{
long first,second,third,n;
printf("enter the series");
scanf("%d",&n);
first=0;
second=1;
printf("%d%d",first,second);
int i;
for(i=2;i<n;i++)
{
third=first+second;
printf("%d",third);
first=second;
second=third;
}
return 0;
}
