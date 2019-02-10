#include<cstdio>
#define MAX 2000000

int MGraph[10001][10001] = { 0 };

int Prim(int vexnum){
	int result = 0;         //最小生成树的长度 
	int i,n,min,min_vex,count;
	
	int mincost[10001] = { 0 }; 

    for (i=1;i<=vexnum;i++) mincost[i]=MAX;     //先将mincost全部赋最大值，便于找min值

    mincost[1]=0;   //mincost[1]就是起点 
    n=1;
  
    for(count=1;count<=vexnum-1;count++){   //count用于计数已经在生成树中的顶的数目 
        min_vex=0;
        min=MAX;
  
        for (i=2;i<=vexnum;i++){
            if (MGraph[n][i]!=0 && mincost[i]!=0 ){
           		 if (MGraph[n][i]<mincost[i]) 
					mincost[i]=MGraph[n][i];
			}
            if (mincost[i]<min && mincost[i]!=0) {
            	min_vex=i;
				min=mincost[i];
			}
        
		}
		n=min_vex;
        result+=mincost[min_vex];
        mincost[min_vex]=0;   
    }
    return result;
}

int main()
{
    int vexnum,edgenum,weight,x,y;
	scanf("%d%d",&vexnum,&edgenum);
	
    
    for (int i=0;i<edgenum;i++){
        scanf("%d%d%d",&x,&y,&weight);
        MGraph[x][y]=weight;
        MGraph[y][x]=weight;
    }

    printf("%d",Prim(vexnum));
}
