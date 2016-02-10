#include<iostream>
#include "tbb/task_scheduler_init.h"
#include<tbb/parallel_for.h>
#include<tbb/blocked_range.h>
#include<math.h>
using namespace std;
using namespace tbb;
class Hello
{
	private:
	char *str;
	public:
	Hello(char s[]) :str(s){ }
	void operator () (const blocked_range<int> &r) const
	{
		for(int i=r.begin();i!=r.end();i++)
		{
			cout<<str<<" "<<GetCurrentThreadId()<<" "<<i<<endl;
		}
	}
	
};
int main(int argc, char* argv[]) 
{

 int nthread; 
 if(argc!=3)
{
	cout<<"provide sufficient args <loop length> <no of threads>";
	exit(-1);
}
 nthread = strtol(argv[1], 0, 0);
 int num =atoi(argv[2]);
 task_scheduler_init init(num);
  
char a[]="hello";
parallel_for(blocked_range<int>(0,nthread,1000),Hello(a));
 

 if( nthread >= 1)
   init.terminate();

 return 0;             
}
