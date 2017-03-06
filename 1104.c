/*
 * 1104. Chips Challenge
 * TOPIC: mincost circulation
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 42
#define MAXV (1<<8)
#define MAXE (MAXV*MAXV)
#define W (1LL<<29)
#define oo (1LL<<62)
typedef long long i64;
i64 min( i64 x, i64 y ) { return x<y?x:y; }
i64 max( i64 x, i64 y ) { return x>y?x:y; }

i64 cost[MAXE],d[MAXV];
int A,B,m,V,E,n,next[MAXE],to[MAXE],last[MAXV],cap[MAXE],flow[MAXE],p[MAXV],src,ALREADY_PLACED,seen[MAXV],yes,
	e[MAXE],*ptr;
char g[N][N],c[N][N];

void add_arcs( int x, int y, int c, i64 w ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i, flow[i] = 0, cap[i] = c, cost[i] =  w;
	to[j] = x, next[j] = last[y], last[y] = j, flow[j] = 0, cap[j] = 0, cost[j] = -w;
}

int bellman_ford( int *t ) {
	int i,j,x,y;
	static int visited[MAXV] = {0}, indeed = 0;
	for ( visited[src] = ++indeed, p[src]=-1, d[src] = 0, i = 0; i < V-1; ++i )
		for ( j = 0; j < E; ++j )
			if ( visited[x=to[j^1]] == indeed && flow[j] < cap[j] && (visited[y=to[j]] != indeed || d[y=to[j]] > d[x]+cost[j]) )
				d[y] = d[x]+cost[p[y]=j], visited[y] = indeed;
	for ( j = 0; j < E; ++j )
		if ( d[x=to[j^1]] < +oo && flow[j] < cap[j] && (visited[y=to[j]] != indeed || d[y=to[j]] > d[x]+cost[j]) ) {
			p[*t = y] = j;
			return 1;
		}
	return 0;
}

i64 mincost_circulation() {
	int x,y,i,j,k,obligatory=0,T=0,row[N],col[N];
	i64 cc,df;
	for( memset(c,0,sizeof c); bellman_ford(&y);) {
		for(seen[y]=++yes,y=to[p[y]^1]; seen[y]!=yes; seen[y]=yes, y=to[p[y]^1] );
		/*printf("y = %d\n",y);*/
		for(df=max(n*n,0x400),x=y,i=p[y],y=to[i^1]; y!=x; df=min(df,cap[i]-flow[i]),i=p[y],y=to[i^1] );
		df = min(df,cap[i]-flow[i]);
		assert( df>0 );
		/*printf("df = %lld\n",df);*/
		for(cc=0,i=p[y],y=to[i^1];y!=x;/*printf("%d->%d, This %lld\n",to[i^1],to[i],cost[i]),*/ cc+=df*cost[i],flow[i]+=df,flow[i^1]-=df,i=p[y],y=to[i^1]);
		flow[i] += df, flow[i^1] -= df, cc += cost[i]*df;
		/*printf("cc = %lld\n",cc);*/
		assert( cc < 0 );
	}
	for ( i = 0; i < E; ++i )
		if ( flow[i] > 0 && (n<=to[i^1]&&to[i^1]<n+n) && (n+n<=to[i]&&to[i]<n+n+n) ) {
			assert( cap[i] == 1 ); assert( flow[i] == 1 );
			T += (c[x=to[i^1]-n][y=to[i]-n-n]=1);
			if ( g[x][y] == 'C' ) ++obligatory;
		}
	if ( obligatory!=ALREADY_PLACED ) return -W;
	for ( i = 0; i < n; ++i ) {
		for ( row[i]=0, j = 0; j < n; row[i] += c[i][j++] );
		if ( B*row[i] > T*A ) return -W;
	}
	for ( j = 0; j < n; ++j ) {
		for ( col[j]=0, i = 0; i < n; col[j] += c[i++][j] );
		if ( B*col[j] > T*A ) return -W;
	}
	for ( i = 0; i < n; ++i ) assert(col[i]==row[i]);
	return T;
}

int main() {
	int i,j,k,l,t,cs=0;
	i64 w;
#ifndef ONLINE_JUDGE
	freopen("1104.in","r",stdin);
#endif
	for(;3==scanf("%d %d %d",&n,&A,&B)&&(n||A||B)&&printf("Case %d: ",++cs);) {
		for ( ALREADY_PLACED=0,i=0; i<n; ++i )
			for ( scanf("%s",g[i]), j=0; j<n; ++j )
				if ( g[i][j]=='C' ) ++ALREADY_PLACED;
		for ( m=0,V = 2*n+2*n+1, src=V-1, E=0, i=0; i<V; last[i++]=-1 );
		for ( ptr=e, i = 0; i < n; add_arcs(i,i+n,m,0),*ptr++=E-2,++i );
		for ( j = n+n; j < n+n+n; add_arcs(j,j+n,m,0),*ptr++=E-2,++j );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] == 'C' )
					add_arcs(i+n,j+n+n,1,-W);
				else if ( g[i][j] != '/' )
					add_arcs(i+n,j+n+n,1,-1);
		for ( i = 0, j = n+n+n; j < n+n+n+n; add_arcs(j++,i++,W,0) );
		for ( i = 0; i < V-1; add_arcs(src,i++,W,0) );
		for ( w=mincost_circulation(), m=1; m<=n; w=max(w,mincost_circulation()), ++m ) 
			for ( i=0; i < ptr-e; ++i ) cap[e[i]] = m;
		if ( w == -W ) puts("impossible"); else printf("%lld\n",w-ALREADY_PLACED);
	}
	return 0;
}

