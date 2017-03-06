/*
 * 11848. Cargo Trains
 * TOPIC: spfa, dijkstra
 * status: WA (unclear)
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#include <float.h>
#define MAXE (1<<20)
#define N 0x200
#define oo (DBL_MAX-0x400)
enum { companyA=0, companyB=1 };

int n,qr,heap[2*N],pos[N],cnt,E;
double tau,d[N],w[2][N][N];

double min( double x, double y ) { if ( x < y ) return x; return y; }

void add_arcs( int x, int y, double cc, int wh ) {
	w[wh][x][y]=min(w[wh][x][y],cc);
	w[wh][y][x]=min(w[wh][y][x],cc);
}

void push( int x ) {
	int i,j;
	if ( pos[x]<0 )
		pos[heap[cnt]=x]=cnt,++cnt;
	for ( j=pos[x]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( cnt+=(pos[x]=-1) )
		pos[*heap=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

double dijkstra() {
	int i,j,k,x,y;
	for ( x = 0; x < n; d[x++] = +oo, pos[x-1] = -1 );
	for ( cnt = 0, d[0] = 0, push(0); cnt; ) 
		for ( x = pop(), y = 0; y < n; ++y ) {
			if ( x == y || !(w[0][x][y]<+oo||w[1][x][y]<+oo) )
				continue ;
			if ( w[0][x][y]<+oo && w[1][x][y]<+oo ) {
				if ( d[y] > d[x] + tau*w[0][x][y] + (1-tau)*w[1][x][y] )
					d[y] = d[x] + tau*w[0][x][y] + (1-tau)*w[1][x][y], push(y);
				continue ;
			}
			for ( k = 0; k < 2; ++k )
				if ( w[k][x][y] < +oo )
					if ( d[y] > d[x]+w[k][x][y] )
						d[y] = d[x]+w[k][x][y], push(y);
		}
	assert( d[n-1] < +oo );
	return d[n-1];
}

int main() {
	int i,j,k,l,t;
	double cc;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;4==scanf("%d %d %d %d",&n,&l,&t,&qr)&&(n+1||l+1||t+1||qr+1);) {
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < 2; ++k )
					w[k][i][j] = +oo;
		for (;l--; scanf("%d %d %lf",&i,&j,&cc), add_arcs(i,j,cc,companyA) );
		for (;t--; scanf("%d %d %lf",&i,&j,&cc), add_arcs(i,j,cc,companyB) );
		for ( ;qr-- && 1 == scanf("%lf",&tau); ) 
			printf("%.lf\n",dijkstra());
	}
	return 0;
}

