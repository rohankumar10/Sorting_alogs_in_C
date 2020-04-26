#include<stdio.h>
void insertion_sort(int a[],int length);
void binary_search(int a[],int target,int length);
void insertion_sort(int a[], int length)
{
 int i,j;
 float temp;
 for(i=1;i<length;i++)
 {
  temp=a[i];
  j=i-1;
  while(a[j]>temp && j>=0)
  {
   a[j+1]=a[j];
   j=j-1;
  }
 a[j+1]=temp;
}
for(i=0;i<length;i++)
printf("%d",a[i]);
}
void binary_search(int a[],int target,int length)
{
int beg,end,mid;
beg=0;
end=length-1;
while(beg<=end)
{
mid=(beg+end)/2;
if(target==a[mid])
{
printf("Elememt found at %d",mid);
}
else if(target<a[mid])
{end=mid-1;}
else if(target>a[mid])
{beg=mid+1;}
}
}
int main()
{
int a[10],n,i;
printf("Enter array size");
scanf("%d",&n);
printf("Enter array elements");
for(i=0;i<n;i++)
scanf("%d",&a[i]);
insertion_sort(a,n);
int num;
printf("Enter element to be searched for");
scanf("%d",&num);
binary_search(a,num,n);
return 0;
}

