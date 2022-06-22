#include<stdio.h>
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
edgeList b;
int parent[MAX];
int size[MAX];

void merging(int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(elist.edges[l1].w <= elist.edges[l2].w)
         b.edges[i] = elist.edges[l1++];
      else
         b.edges[i] = elist.edges[l2++];
   }

   while(l1 <= mid)
      b.edges[i++] = elist.edges[l1++];

   while(l2 <= high)
      b.edges[i++] = elist.edges[l2++];

   for(i = low; i <= high; i++)
      elist.edges[i] = b.edges[i];
}

void sort(int low, int high) {
   int mid;

   if(low < high) {
      mid = (low + high) / 2;
      sort(low, mid);
      sort(mid+1, high);
      merging(low, mid, high);
   } else {
      return;
   }
}

int find(int x) {
    int y = x;
    while(parent[y] != y) {
        y = parent[y];
    }
  return y;
}

void union1(int c1, int c2) {

    if(size[c1] <= size[c2]) {
        parent[c1] = c2;
        size[c2] = size[c2] + size[c1];
    } else {
        parent[c2] = c1;
        size[c1] = size[c2] + size[c1];
    }
}

int main() {
    int n;
    printf("Enter the number of nodes:");
    scanf("%d",&n);
    printf("%d\n",n);
    int e;
    printf("Enter number of edges:");
    scanf("%d",&e);
    elist.e = e;
    int x;
    int y;
    int w;
    printf("Enter each edge in the form of (v1 v2 weight)");
    for(int i = 0;i < e;i++) {
        scanf("%d %d %d",&x,&y,&w);
        elist.edges[i].v1 = x;
        elist.edges[i].v2 = y;
        elist.edges[i].w = w;
    }

    sort(0,e-1);
    for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
    }
    for(int i = 0; i < elist.e; i++) {
        int c1 = find(elist.edges[i].v1);
        int c2 = find(elist.edges[i].v2);
        if(c1 != c2) {
            spanTree.edges[spanTree.e] = elist.edges[i];
            spanTree.e = spanTree.e + 1;
            union1(c1, c2);
        }
    }
    printf("Final Spanning tree is:\n");
    for(int i = 0;i < spanTree.e;i++) {
        printf("%d %d %d\n",spanTree.edges[i].v1,spanTree.edges[i].v2,spanTree.edges[i].w);
    }
    return 0;
}
