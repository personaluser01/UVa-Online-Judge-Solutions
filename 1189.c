/*
 * 1189. Find the Multiple
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x400
#define Q N
#define oo 0xfffffffful

int n;
char move[Q];
unsigned int d[N],*head,*tail,q[Q],parent[Q];

void dump( unsigned int r ) {
	if ( parent[r] != -1 )
		dump(parent[r]);
   	putchar(move[r]+'0');
}

int main() {
	unsigned int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( ;1==scanf("%d",&n) && n>0; ) {
		if ( n == 1 ) { puts("1"); continue ; }
		for ( head=tail=q, i = 0; i < n; ++i ) parent[i]=d[i]=+oo;
		d[*tail++=1%n] = 1, parent[1%n]=-1, move[1%n]=1;
		for (;head<tail;)
			for ( k=*head++, i=0; i<=1; ++i )
				if ( d[j=(10*k+i)%n] > d[k]+1 )
					d[*tail++=j]=d[parent[j]=k]+1,move[j]=i;
		dump(0), putchar('\n');
	}
	return 0;
}

