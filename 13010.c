/*
 * 13010. Galactic Taxes
 * TOPIC: dijkstra, ternary search
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define oo DBL_MAX
#define tol 1e-12
#define N 0x400
#define MAXE (1<<19)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))

int to[MAXE],next[MAXE],last[N],n,E,V,heap[N<<1],pos[N],cnt,m;
double d[N],A[MAXE],B[MAXE];

void add_arcs( int x, int y, int a, int b ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, A[i] = a, B[i] = b;
	to[j] = x, next[j] = last[y], last[y] = j, A[j] = a, B[j] = b;
};

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt]=x]=cnt, ++cnt;
	for ( j=pos[x]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j=i );
};

int pop() {
	int i,j,x=*heap;
	if ( cnt+=(pos[x]=-1) )
		pos[*heap=heap[cnt]] = 0;
	for ( j=0; (i=j,j<<=1,++j)<cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j]]>d[heap[j+1]] ) ++j;
		if ( d[heap[i]]<=d[heap[j]] ) break ;
	}
	return x;
};

double dijkstra( const double T ) {
	int x,y,i,src=0,dst=n-1;
	for ( x=0; x<n; pos[x]=-1, d[x++]=+oo );
	for ( cnt=0, d[src] = 0, push(src); cnt; )
		for ( i=last[x=pop()]; i>=0; i=next[i] )
			if ( d[y=to[i]]>d[x]+A[i]*T+B[i] )
				d[y]=d[x]+A[i]*T+B[i], push(y);
	return d[dst];
};

int main() {
	int i,j,k,l;
	double a,b,na,nb;
#ifndef ONLINE_JUDGE
	freopen("13010.in","r",stdin);
#endif
	for(;2 == scanf("%d %d",&n,&m); printf("%.5lf\n",tol+dijkstra((a+b)/2)) ) {
		for(E=0,i=0;i<n;last[i++]=-1);
		for ( ;m-- && 4 == scanf("%d %d %d %d",&i,&j,&k,&l); add_arcs(--i,--j,k,l) );
		for ( a = 0, b = 24*60; fabs(b-a) >= tol; ) {
			na = (2*a+b)/3.00, nb = (2*b+a)/3.00;
			if ( dijkstra(na) < dijkstra(nb) ) 
				a = na;
			else b = nb;
		}
	}
	return 0;
};

