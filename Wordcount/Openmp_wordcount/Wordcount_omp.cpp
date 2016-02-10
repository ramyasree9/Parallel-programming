#include<stdlib.h>
#include<iostream>
#include<list>
#include<vector>
#include<iterator>
#include<fstream>
#include<cstring>
#include<omp.h>
#include<map>
#include<sys/time.h>
using namespace std;
map<string,int> m;
list<string> l;
void split(string s)
{	
	char *delim=",.\t\n ";
	const char *st=s.c_str();
	while(*st)
	{
		size_t tokenlen;
		st+=strspn(st,delim);
		tokenlen=strcspn(st,delim);
		if(tokenlen)
		{
			l.push_back(string(st,tokenlen));
		}
		st+=tokenlen;
	}
		
}
int main(int args,char *argv[])
{
	string s;
	if(args!=2)
	{
		cout<<"provide sufficient arguments <input file name>";
		exit(-1);
	}
	clock_t t1=clock();
	ifstream fin(argv[1]);
	while(fin)
	{
		getline(fin,s);
		split(s);
	}
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			for(list<string>::iterator it=l.begin();it!=l.end();it++)
			{
			#pragma omp task
			{
				map<string,int>::iterator temp=m.find(*it);
				if(temp!=m.end())
				(*temp).second=(*temp).second+1;
				else
				{
				m.insert(pair<string,int>(*it,1));
				}
			}
			}
		}
	}
	clock_t t2=clock();
	double time_taken=((double )t2-(double )t1)/1000000;
	cout<<"time taken in seconds  :"<<time_taken;
	for(map<string,int>::iterator it=m.begin();it!=m.end();it++)
	{
		cout<<(*it).first<<" :"<<(*it).second<<endl; 
	}
	return 0;
}

