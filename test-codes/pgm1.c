#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ns 1000000
main()
{
double m[1000][1000],v[1000][1],r[1000][1],diff;
int i,j,k,mr,mc,vr;
printf("enter no of rows of matrix");
scanf("%d",&mr);
printf("enter no of columns of matrix");
scanf("%d",&mc);
printf("enter no of rows of vector");
scanf("%d",&vr);
if(mr<1)
{
printf("cant be negative");
exit(EXIT_FAILURE);
}
if(mc<1)
{
printf("cant be negative");
exit(EXIT_FAILURE);
}
if(vr<1)
{
printf("cant be negative");
exit(EXIT_FAILURE);
}
if(mc!=vr)
{
printf("cant be multiplied");
exit(EXIT_FAILURE);
}
for(i=0;i<mr;i++)
{
for(j=0;j<mc;j++)
{
m[i][j]=(i+1)*(j+1);
}
}
for(i=0;i<vr;i++)
{
r[i][0]=0.0;
v[i][0]=i+1;
}
time_t t1=time(NULL);
for(i=0;i<mr;i++)
{
for(j=0;j<mc;j++)
{
r[i][0]=r[i][0]+(m[i][j]*v[j][0]);
}
}
time_t t2=time(NULL);
double dif =difftime(t2,t1)*ns;
for(i=0;i<vr;i++)
{
printf("%f\n",r[i][0]);
}
printf("time taken in ns%f\n",dif);
}
