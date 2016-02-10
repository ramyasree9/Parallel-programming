#include "proto.h"
#include<fstream>
#include <cstdlib>

using namespace std;

void ReadInput (char *filename) 
{

  int i, j;
  int npts, nedges, ntrs;
  ifstream fp;
  //FILE *fp; 
  //FILE *fq; 
  POINT *pt; 
  EDGE *edg; 
  TRIANGLE *tri; 

  //if ((fq = fopen ("mesh-triag.out", "w")) == NULL) 
  //PrintError ("Can't open input file");
  fp.open (filename);
  if (!fp) 
  {
    PrintError("Can't open input file");
    exit(-1);
  }

  fp >> npts;
  //fscanf (fp, "%d", &npts); 
  cout<< npts <<"\n";
  //f cout<<fq, "%d\n", npts);
  
  for (i=0; i< npts ; i++) 
  {
    pt = AllocateNewPoint (); 
    /*     cout<<pt->Id<<"\n"; */
    fp >> pt->x >>pt->y; 	
    //fscanf (fp, "%lf %lf", &(pt->x), &(pt->y));
    cout<<pt->x<<","<<pt->y<<"\n"; 
    //fprintf(fq, "%lf %lf \n ", (pt->x), (pt->y));
  }
  
   cout<<"Finished reading points \n";

  //fscanf (fp, "%d", &nedges); 
  fp >>nedges;
  cout<<nedges<<"\n"; 
  for (i=0; i<nedges; i++) 
  {
    edg = AllocateNewEdge (); 
    cout<<edg->Id<<"	";  

    for (j=0; j<2; j++) 
    { 
      //fscanf (fp, "%ld", &(edg->point[j]));
      fp >>edg->point[j];
      cout<<edg->point[j]<<"	";
    }
    cout<<"\n"; 
    for (j=0; j<2; j++) 
    {
      //fscanf (fp, "%ld", &(edg->triangle[j]));
      fp >>edg->triangle[j];
      cout<<edg->triangle[j]<<"	";
    }
    cout<<"\n";
    for (j=0; j<2; j++) 
    {
      //fscanf (fp, "%hd ", &(edg->orient[j]));
      fp >>edg->orient[j];
      cout<<edg->orient[j]<<"	";
    }
    cout<<"\n";
    //fscanf (fp, "%hd", &edg->isBoundary); 
    fp >>edg->isBoundary;
    cout<<edg->isBoundary<<"	";
    cout<<"\n";
  }

   cout<<"Finished reading edges \n";
  
  //fscanf (fp, "%d", &ntrs);
  fp >>ntrs; 
  cout<<ntrs<<"\n";
  //f cout<<fq, "%d\n", ntrs);
  for (i=0; i<ntrs; i++) 
  {
    tri = AllocateNewTriangle (); 
    cout<<tri->Id<<"	"; 
    for (j=0; j<3; j++) 
    { 
      //fscanf (fp, "%ld", &(tri->point[j]));
      fp >>tri->point[j]; 
      cout<<tri->point[j]<<"	"; 
    }
    cout<<"\n";
    //f cout<<fq,"%ld %ld %ld \n", tri->point[0]+1, tri->point[1]+1, tri->point[2]+1);
    for (j=0; j<3; j++) 
    {
      //fscanf (fp, "%ld", &(tri->edge[j]));
      fp >>tri->edge[j];  
      cout<<tri->edge[j]<<"	"; 
    }
    cout<<"\n";
  }
  
   cout<<"Finished reading triangles \n"; 
  
  //fclose (fq);  
 
  fp.close();
}
