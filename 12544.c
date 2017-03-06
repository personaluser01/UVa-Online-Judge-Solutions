/*
 * 12544. Beehives
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXE (1<<21)
#define N 0x400
#define oo 0xfffffffful

int ts,cs,n,m,E,to[MAXE],last[N],next[MAXE],*head,*tail,q[N],seen[N],yes,p[N];
unsigned int d[N],w;

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
}

int main() {
	int i,j,k,x,y,src,ok;
#ifndef ONLINE_JUDGE
	freopen("beehives.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&n,&m);
		for ( E = 0, i = 0; i < n; last[i++] = -1 );
		for ( ;m-- && 2 == scanf("%d %d",&i,&j); add_arcs(i,j) );
		for ( w = +oo, src = 0; src < n; ++src ) 
			for ( head=tail=q, ok=seen[*tail++=src]=++yes, d[src]=0; head<tail && ok; )
				for ( i=last[x=*head++]; i>=0 && ok; i=next[i] )
					if ( seen[y=to[i]]!=yes || d[y]>d[x]+1 ) 
						seen[*tail++=y]=yes, d[y]=d[p[y]=x]+1;
					else if ( p[x] != y && w>d[y]+d[x]+1 && d[y]+d[x]+1 > 2 )
						w=d[y]+d[x]+1, ok=0;
		printf("Case %d: ",++cs);
		if ( w < +oo && w > 2 ) printf("%u\n",w);
		else puts("impossible");
	}
	return 0;
}

