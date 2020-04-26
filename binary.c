#include<stdio.h>
void binary_search(int [],int,int);
int main()
{
int arr[20],size,item;
printf("Enter Size Of Array");
scanf("%d",&size);
printf("Enter Array Elements");
for(int i=0;i<size;i++)
scanf("%d",&arr[i]);
printf("Enter element to be searched for");
scanf("%d",&item);
binary_search(arr,size,item);
return 0;
}
void binary_search(int Arr[20],int N,int ITEM)
{
int first,last,mid;
first=0;
last=N-1;
mid=(first+last)/2;
while(first<=last)
{
if(Arr[mid]<ITEM)
first=mid+1;
else if(Arr[mid]==ITEM)
  printf("Element found at%d",mid+1);
else
last=mid-1;
}
}
