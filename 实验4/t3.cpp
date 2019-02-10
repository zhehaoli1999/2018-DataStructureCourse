#include <cstdio>
#include <cstdlib>
#define MAX 2000000

int MGraph[10001][10001]={0};

int Dijkstra(int start,int final,int vexnum){   
    int i,j,min,min_vex;    
    int distance[10001]={0};      

	for (i = 1; i <= vexnum; i++) {
		if (MGraph[start][i] == 0) 
			distance[i] = MAX;    //此顶不可直接达，距离先设为无穷
		else distance[i] = MGraph[start][i];   //否则距离为边权
	}

	bool* visited= (bool*)malloc(sizeof(bool)*(vexnum+1));
	for (int k = 0; k <= vexnum; k++) visited[k] = false;

	distance[start] = 0;    //对起始顶标志0
    visited[start]=true;

	min_vex = start;
    for (i=2;i<=vexnum;i++){
        min= MAX;
		for (j = 1; j <= vexnum; j++) {
			if (!visited[j] && distance[j] < min ) {   //找到当前距离start顶最近的顶
			    min_vex = j;
				min = distance[j];
				
			}
		} 
		visited[min_vex] = true;
		if (min_vex == final) break;
		
		for (j = 1; j <= vexnum; j++) {
			if ((!visited[j]) && MGraph[min_vex][j] != 0) {
				if ((distance[min_vex] + MGraph[min_vex][j]) < distance[j])    //修改距离
					distance[j] = distance[min_vex] + MGraph[min_vex][j];    //
			}
		}
    }
    return distance[final];
}
int main(){
    int x,y,weight;
	int vexnum, edgenum;
    scanf("%d%d",&vexnum,&edgenum);
    for (int i=0;i<edgenum;++i)
    {
        scanf("%d%d%d",&x,&y,&weight);
        MGraph[x][y]=weight;
        MGraph[y][x]=weight;
    }
    scanf("%d%d",&x,&y);
    
    printf("%d",Dijkstra(x,y,vexnum));
}

