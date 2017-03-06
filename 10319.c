/*
 * 10319. Manhattan
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 0x80
#define MAXE (MAXV*MAXV)
#define RV(x) ((x)^1)
enum { D, T };

int m,n,routes,V,to[2][MAXE],next[2][MAXE],last[2][MAXE],
	preset[MAXV],ok,E[2],mark,seen[MAXV],yes;
unsigned char g[MAXV][MAXV],repr[MAXV],c[MAXV][MAXV],is_bad[MAXV],queue[MAXV*MAXV],*head,*tail,
			  q[MAXV][MAXV],*ptr[MAXV],scc[MAXV],queue[MAXV*MAXV],*head,*tail,*top,st[MAXV];

void adj( int x, int y ) {
	int i = E[D]++,
		j = E[T]++;
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

void handle( int x, int y, int p, int q ) {
	g[RV(x)][p] = g[RV(x)][q] = 1;
	adj(RV(x),p), adj(RV(x),q);
	g[RV(y)][p] = g[RV(y)][q] = 1;
	adj(RV(y),p), adj(RV(y),q);
	g[RV(p)][x] = g[RV(p)][y] = 1;
	adj(RV(p),x), adj(RV(p),y);
	g[RV(q)][x] = g[RV(q)][y] = 1;
	adj(RV(q),x), adj(RV(q),y);
}

void add_arcs( int i, int j, int k, int l ) {
	int t;
	if ( !ok ) return ;
	if ( i == k && j == l )
		return ;
	if ( i == k ) {
		if ( j < l ) {
			for ( t = 0; t < V; ++t )
				g[t][(i<<1)] = 1, adj(t,(i<<1));
		}
		else {
			for ( t = 0; t < V; ++t )
				g[t][RV(i<<1)] = 1, adj(t,RV(i<<1));
		}
		if ( ((j<l)&&(preset[i<<1]=1)==preset[RV(i<<1)])||\
			 ((j>l)&&(preset[RV(i<<1)]=1)==preset[i<<1]) ) {
			ok = 0;
			return ;
		}
		return ;
	}
	if ( j == l ) {
		if ( i < k ) {
			for ( t = 0; t < V; ++t )
				g[t][(j+m)<<1] = 1, adj(t,(j+m)<<1);
		}
		else {
			for ( t = 0; t < V; ++t )
				g[t][RV((j+m)<<1)] = 1, adj(t,RV((j+m)<<1));
		}
		if ( ((i<k)&&(preset[(j+m)<<1]=1)==preset[RV((j+m)<<1)])||\
			 ((i>k)&&(preset[RV((j+m)<<1)]=1)==preset[(j+m)<<1]) ) {
			ok = 0;
			return ;
		}
		return ;
	}
	assert( i != k && j != l );
	if ( i < k && j < l ) {
		handle((i<<1),(l+m)<<1,(k<<1),(j+m)<<1);
		return ;
	}
	if ( i < k && j > l ) {
		handle(RV(i<<1),(l+m)<<1,RV(k<<1),(j+m)<<1);
		return ;
	}
	if ( i > k && j < l ) {
		handle((i<<1),RV((l+m)<<1),(k<<1),RV((j+m)<<1));
		return ;
	}
	if ( i > k && j > l ) {
		handle(RV(i<<1),RV((l+m)<<1),RV(k<<1),RV((j+m)<<1));
		return ;
	}
	assert( 0 );
}

void dfs( int t, int x ) {
	int i,y;
	for(seen[x]=yes,i=last[t][x];i>=0;i=next[t][i])
		if(seen[y=to[t][i]]!=yes)dfs(t,y);
	t?(scc[*ptr[mark]++=x]=mark):(*++top=x);
}

int main() {
	int i,j,k,l,t,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 3 == scanf("%d %d %d",&m,&n,&routes); ) {
		V = 2*m+2*n, memset(g,0,sizeof(g)), E[D]=E[T]=0;
		for ( i = 0; i < V; ++i ) last[D][i] = last[T][i] = -1, preset[i] = 0;
		for ( ok = 1, t = 0; t < routes; ++t ) {
			assert( 4 == scanf("%d %d %d %d",&i,&j,&k,&l) );
			assert( 1 <= i && i <= m );
			assert( 1 <= j && j <= n );
			assert( 1 <= k && k <= m );
			assert( 1 <= l && l <= n );
			--i, --j, --k, --l;
			add_arcs(i,j,k,l);
		}
		if ( !ok ) goto NO;
		for ( k = 0; k < V; ++k )
			for ( i = 0; i < V; ++i )
				for ( j = 0; j < V; ++j )
					g[i][j]|=(g[i][k]&g[k][j]);
		for ( i = 0; i < V; ++i )
			if ( g[i][RV(i)] && g[RV(i)][i] ) 
				goto NO;
		for ( ++yes, top = st, i = 0; i < V; ++i )
			if ( seen[i] != yes )
				dfs(D,i);
		for ( ++yes, mark = 0; top > st; --top )
			if ( seen[*top] != yes )
				ptr[mark] = q[mark], dfs(T,*top), ++mark;
		for ( i = 0; i < mark; ++i )
			for ( j = 0; j < mark; ++j )
				c[i][j] = 0;
		for ( i = 0; i < V; ++i )
			for ( j = 0; j < V; ++j )
				if ( scc[i] != scc[j] && g[i][j] )
					c[scc[i]][scc[j]] = 1;
		for ( k = 0; k < mark; ++k )
			for ( i = 0; i < mark; ++i )
				for ( j = 0; j < mark; ++j )
					c[i][j]|=(c[i][k]&c[k][j]);
		memset(is_bad,0,sizeof(is_bad));
		for ( i = 0; i < V; ++i )
			is_bad[scc[i]] |= c[scc[i]][scc[RV(i)]];
		for ( head = tail = queue, i = 0; i < mark; ++i )
			if ( is_bad[i] )
				*tail++ = i;
		/*for ( k = 1; k; ) {*/
			head = tail = queue+(k=0);
			for ( i = 0; i < mark; ++i )
				if ( is_bad[i] ) *tail++ = i;
			for(;head < tail;)
				for ( i = *head++, j = 0; j < mark; ++j )
					if ( c[j][i] && !is_bad[j] )
						++k, is_bad[*tail++ = j] = 1;
		/*}*/
		for ( i = 0; i < V; ++i )
			if ( is_bad[scc[i]] && is_bad[scc[RV(i)]] )
				goto NO;
		puts("Yes"); continue ;
		NO: puts("No");
		continue ;
	}
	return 0;
}
