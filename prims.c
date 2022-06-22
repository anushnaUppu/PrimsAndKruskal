#include <stdio.h>
#include <math.h>
#define MAX 50

typedef struct edge {
  int v1, v2, w;
} edge;

typedef struct edgeList {
  edge edges[MAX];
  int e;
} edgeList;

edgeList elist;
edgeList spanTree;
int n;

int main() {
    printf("Enter the number of nodes:");
    scanf("%d",&n);
    int e;
    int mat[n][n];
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            mat[i][j] = 0;
        }
    }
    printf("Enter number of edges:");
    scanf("%d",&e);
    elist.e = e;
    int x;
    int y;
    int w;
    printf("Enter each edge in the form of (v1 v2 weight)\n");
    for(int i = 0;i < e;i++) {
        scanf("%d %d %d",&x,&y,&w);
        mat[x][y] = w;
        mat[y][x] = w;
    }
    int minimumValue[n];
    int minimumVertexIndex[n];
    int visited[n];
    for(int i = 0;i < n;i++) {
        minimumValue[i] = INFINITY;
        minimumVertexIndex[i] = -1;
        visited[i] = 0;
    }
    int r = 0;
    for(int i = 0;i < n-1;i++) {
        visited[r] = 1;
        for(int j = 0;j < n;j++) {
            if(mat[r][j] > 0 && visited[j] == 0) {
                if(minimumValue[j] > mat[r][j]) {
                    minimumValue[j] = mat[r][j];
                    minimumVertexIndex[j] = r;
                }
            }
        }
        int minimumEdgeValue = INFINITY;
        for(int k = 0;k < n;k++) {
            if(visited[k] == 0 && minimumEdgeValue > minimumValue[k]) {
                r = k;
                minimumEdgeValue = minimumValue[k];
            }
        }
        spanTree.edges[i].v2 = r;
        spanTree.edges[i].v1 = minimumVertexIndex[r];
        spanTree.edges[i].w = minimumEdgeValue;
    }

    printf("Final Spanning tree is:\n");
    int total_cost = 0;
    for(int i = 0;i < n-1;i++) {
        printf("%d %d %d\n",spanTree.edges[i].v1,spanTree.edges[i].v2,spanTree.edges[i].w);
        total_cost += spanTree.edges[i].w;
    }
    printf("Cost for spanning tree = %d\n",total_cost);

    return 0;
}
