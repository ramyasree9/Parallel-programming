#include<iostream>
#include<cstring>
#include<cstdlib>
#include<list>
#include<vector>
#include<fstream>
#include<algorithm>
#define size 1872
using namespace std;
list <int> L[size];
 class coloring
        {
        public :
        int vertex_color[size],rand_no[size],i,index,count;
        vector<int> ind_set;
        bool marked[size],flag ;

        void init()
        {
                index = -1;
                count = 0;
		for(i=1; i<size ;i++)
		vertex_color[i]=-1;
        }
        void cal_set()
        {
        for( i=1 ; i<size ; i++)
        {
               rand_no[i] = rand();
//	         rand_no[i] = i;
        }

       	while(count< size-1)
        {
                flag = true;
                for( i=1 ; i<size ; i++)
                        marked[i]  = false;
   	            while(true)
                {
                        int ret =color();
                        count +=ret;
	//		cout<<count<<endl;
    	                if(!ret)
                        break;

                }
                if(!ind_set.empty())
                        index ++;
                while(!ind_set.empty())
                {
                        vertex_color[ind_set.back()] = index;
                        ind_set.pop_back();
                }

        }
        }
        int color()
        {
                bool max = true;
                int ret =0;
                for( int i=1 ; i< size ; i++ )
                {
                        if(vertex_color[i] == -1 && (marked[i]== false))
                        {
                                int start = rand_no[i];
                                max = true;
                                for(list<int>:: iterator it =L[i].begin(); it != L[i].end(); it++)
                                {
                                        if( vertex_color[*it]  == -1 && marked[*it] == false)
                                        {
                                                if(start < rand_no[*it])
                                                {
                                                        max =  false;
                                                        break;
                                                }
                                        }
                                }
                                if(max)
                                {
                                        ret++;
                                        marked[i]= true;
                                        ind_set.push_back(i);
                                        for(list<int >:: iterator it =L[i].begin() ; it!= L[i].end(); it ++)
                                        marked[*it]=true;
                                }

                        }
                }
                return ret;
	}
	void disp()
	{
		cout<<endl;
		for(i =1; i< size ; i++)
		{
			cout<< i <<" :"<<vertex_color[i]<<endl; 
		}
		cout<<index+1;
	}
};                                                                           
                                                                       
int main()
{
	ifstream fin ;
	int vertex[3] , i = 0 , j = 0;
	char * token;
	string line;
	char *temp;
	fin.open( "datasets/sup/sup_1871.txt" );
	while( fin )
	{
		getline( fin , line );
		temp = new char[50];
		strcpy(temp,line.c_str());
		token = new char[50];
		token	=	strtok(temp , " " ) ;
		i = 0;
		while(token != NULL)
		{
			vertex [ i ]	=	atoi(token);
			token	=	strtok( NULL , " " );
			i++ ;
		}
		for( i = 0 ; i < 3 ; i++ )
		{
			for( j = 0 ; j <3 ; j++ )
			{	
				 list <int>::iterator it;
				if( i != j )
				{
					 it = find( L[ vertex[i] ].begin() , L[ vertex[i] ].end(), vertex [j] );	
					if( it == L[ vertex [i] ].end() )
					{
						L[ vertex [ i ] ].push_back( vertex[ j ] );
					}
				}
			}
		}
	}
	ofstream fout ;
	fout.open("output.txt");
	for( i = 1 ; i < size ; i++ )
	{
		fout<<i<<" ";
		for( list<int> ::iterator it = L[i].begin(); it != L[i].end() ; it++ )
		fout<<(* it )<<" ";
		fout<<endl;
	}
	fin.close() ;
	fout.close() ;
	coloring c;
	c.init();
	c.cal_set();
	c.disp();
    	/*************************new*******************/
	}
