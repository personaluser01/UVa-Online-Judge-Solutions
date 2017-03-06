/*
 * 12273. Palindromic DNA
 * TOPIC: 2-sat, very neat, scc, strongly connected components
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<14)
#define MAXN (N<<2)
#define MAXE (1<<21)
enum { D, T };

char str[N];
int n,m,V,E[2],to[2][MAXE],next[2][MAXE],last[2][MAXN],pos[N],scc[MAXN],mark,numv,
	visited[2][MAXN],yes[2],st[MAXN],*top,is[MAXN],indeed;

void add_arcs( int x, int y ) {
	int i = E[D]++, j = E[T]++;
	is[x] = is[y] = indeed;
	assert( x < numv );
	assert( y < numv );
	to[D][i]=y, next[D][i]=last[D][x], last[D][x]=i;
	to[T][j]=x, next[T][j]=last[T][y], last[T][y]=j;
}

void set( int i, int val ) {
	int must = (2*i)|val;
	add_arcs(must^1,must);
}

void add_or( int i, int v1, int j, int v2 ) {
	add_arcs((2*i)|(v1^1),(2*j)|v2);
	add_arcs((2*j)|(v2^1),(2*i)|v1);
}

void add_equal(int i,int j) {
	add_or(i,1,j,0);
	add_or(i,0,j,1);
}

void add_distinct(int i,int j) {
	add_or(i,0,j,0);
	add_or(i,1,j,1);
}

void dfs( int x, const int t, int w ) {
	int i,y;
	for ( visited[t][x]=yes[t], i=last[t][x]; i>=0; i=next[t][i] )
		if ( visited[t][y=to[t][i]]!=yes[t] )
			dfs(y,t,w+2);
	if ( t==T ) *++top=x;
	else scc[x] = mark;
}

char _next[256];
const char *alph = "AGTC";

int main() {
	int i,j,k,l,t,u,v,ok,cs = 0,a,b,rev;
#ifndef ONLINE_JUDGE
	//freopen("in.txt","r",stdin);
	freopen("12273.in","r",stdin);
#endif
	for ( i = 0; i < 4; ++i )
		_next[alph[i]] = alph[(i+1)&3];
	for (;2==scanf("%d %d",&n,&m) && (m||n);) {
		numv = 4*n;
		for ( E[D]=E[T]=0, i = 0; i < numv; ++i )
			last[D][i] = last[T][i] = -1;
		/*memset(visited,0,sizeof visited), yes[D] = yes[T] = 0;*/
		for ( indeed += scanf("%s",str), l=0; l<m; ++l ) {
			assert( 1==scanf("%d:",&t) );
			for ( j=0; j<t && 1==scanf("%d",&pos[j++]););
			assert( j == t );
			for ( i=0,j=t-1; i<j; ++i,--j ) {
				a = pos[i], b = pos[j];
				if ( str[pos[i]] == str[pos[j]] ) {
					add_equal(a,b);
					add_equal(a+n,b+n);
				}
				else if ( str[pos[i]]=='A'&&str[pos[j]]=='G' ||\
						  str[pos[i]]=='G'&&str[pos[j]]=='T' ||\
						  str[pos[i]]=='T'&&str[pos[j]]=='C' ||\
						  str[pos[i]]=='C'&&str[pos[j]]=='A' ) {
					add_distinct(a,b);
					if ( str[b]!=_next[str[a]]) rev = 1; else rev = 0;
					add_or(a,1,b+n,rev);
					add_or(b,1,a+n,rev^1);
				}
				else if ( str[pos[i]]=='G'&&str[pos[j]]=='A' ||\
						  str[pos[i]]=='A'&&str[pos[j]]=='C' ||\
						  str[pos[i]]=='C'&&str[pos[j]]=='T' ||\
						  str[pos[i]]=='T'&&str[pos[j]]=='G' ) {
					add_distinct(a,b);
					if ( str[b]!=_next[str[a]]) rev = 1; 
					else { assert( _next[str[a]] == str[b] ); rev = 0; }
					add_or(a,1,b+n,rev);
					add_or(b,1,a+n,rev^1);
				}
				else {
					assert( str[pos[i]]=='A'&&str[pos[j]]=='T'||\
							str[pos[i]]=='G'&&str[pos[j]]=='C'||\
							str[pos[i]]=='T'&&str[pos[j]]=='A'||\
							str[pos[i]]=='C'&&str[pos[j]]=='G' );
					set(a,1), set(b,1);
					add_distinct(a+n,b+n);
				}
			}
		}
		for ( i = 0; i < n-1; ++i )
			add_or(i,0,i+1,0);
		for ( top = st, ++yes[T], mark = 0, i = 0; i < numv; ++i )
			if ( visited[T][i] != yes[T] )
				dfs(i,T,0);
		for ( ++yes[D]; top > st; ) 
			if ( visited[D][k = *top--] != yes[D] ) 
				++mark, dfs(k,D,0);
		for ( ok = 1, i = 0; ok && i < numv; i += 2 )
			if ( scc[i] == scc[i^1] ) 
				ok = 0;
		puts(ok?"YES":"NO");
	}
	return 0;
}

