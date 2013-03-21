#include <iostream>
using namespace std;

typedef struct
{
     int x,y;                   // vertex
     int w;                     // weight
}edge;

const int MAX=100;
int Father[MAX];
int Rank[MAX];

int Find_Set(int x){
     if(x!=Father[x])
          Father[x]=Find_Set(Father[x]);
     return Father[x];
}
void Union_Set(int x, int y){
     int xroot=Find_Set(x);
     int yroot=Find_Set(y);
     if(xroot==yroot)
          return;
     if(Rank[xroot]<Rank[yroot])
          Father[xroot]=yroot;
     else{
          if(Rank[xroot]==Rank[yroot])
               ++Rank[xroot];
          Father[yroot]=xroot;
     }
}

int cmp(const void* a, const void* b){
     return ((edge*)a)->w-((edge*)b)->w;
}

int main(int argc, char *argv[])
{
     edge e[MAX];
     int NumOfEdge, NumOfVertex,weight,sum=0;
     char cx,cy;
     cin>>NumOfVertex>>NumOfEdge;
     for (int i = 0; i<NumOfVertex; ++i){
          Father[i]=i;
          Rank[i]=0;
     }
     for (int i=0; i<NumOfEdge; ++i){
          cin>>cx>>cy>>weight;
          e[i].x=cx-'A';
          e[i].y=cy-'A';
          e[i].w=weight;
     }
     qsort(e, NumOfEdge, sizeof(edge), cmp);
     for (int i = 0; i<NumOfEdge; ++i){
          int x=Find_Set(e[i].x);
          int y=Find_Set(e[i].y);
          if(x!=y){
               Union_Set(x,y);
               sum+=e[i].w;
               cout<<(char)(e[i].x+'A')<<"-"<<(char)(e[i].y+'A')<<" "<<e[i].w<<endl;
          }
     }
     cout<<sum<<endl;
     return 0;
}
