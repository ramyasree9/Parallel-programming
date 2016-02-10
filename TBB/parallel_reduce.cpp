#include<iostream>
#include<tbb/task_scheduler_init.h>
#include<tbb/blocked_range.h>
#include<tbb/parallel_reduce.h>
using namespace tbb;
using namespace std;
class Body
{
	private :
	int sum;
	public:
	Body(int sum)
	{
	this->sum=sum;
	}
	Body(Body &a,split)
	{
	sum=a.sum;
	}
	void operator()(const blocked_range<int *> &r)
	{
	int temp=0;
	for(int *a=r.begin();a!=r.end();a++)
	{
	temp+=*a;
	}
	sum=temp;
	}
	void join(Body &a)
	{
	sum+=a.sum;
	}
	int givesum()
	{
	return sum;
	}
};
int main()
{	
	Body b(0);
	int a[]={1,2,3,4,5};
	task_scheduler_init init;
	parallel_reduce(blocked_range<int *>(a,a+5,10),b);
	cout<<b.givesum();
	return 0;
}
