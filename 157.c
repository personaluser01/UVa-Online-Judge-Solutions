/*
 * 157. Route Finding
 * TOPIC: bfs
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  enc(x,y)  ((((unsigned int)(x)-'A'))|((((unsigned int)(y)-'a'))<<5))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned long long u64;
typedef long long i64;
#define oo 0xfffffffful
#define N 0x400
#define Q (N)
#define ROUTE(u) ((u)&MASK(5))
#define STATION(u) ((u)>>5)

unsigned int other_names[N][N],adj[N][N],*top,st[N],d[N],q[N],*head,*tail,p[N],*ptr[N],o[N][N];
int len[N],deg[N],rank[N],parent[N],n,m;

void link( int x, int y ) {
	if ( rank[x] > rank[y] ) {
		parent[y] = x;
	}
	else {
		parent[x] = y;
		if ( rank[x] == rank[y] ) ++rank[y];
	}
}
int find( int x ) {
	if ( parent[x] == x )
		return x;
	return parent[x] = find(parent[x]);
}
void merge( int x, int y ) { link(find(x),find(y)); }
void make_set( int x ) { rank[parent[x] = x] = 0; }

unsigned int
dijkstra( unsigned int src, unsigned int dst ) {
	unsigned int u,v,pu;
	int i,j,k,l,rt,station;
	for ( u = 0; u < N; d[u++] = +oo );
	for ( p[src] = +oo, head = tail = q, d[*tail++ = src] = 0; head < tail; ) {
		for ( u = *head++, rt = ROUTE(u), station = STATION(u), i = 0; i < deg[u]; ++i ) 
			if ( d[v=adj[u][i]] > d[u]+1 )
				d[*tail++=v]=d[p[v]=u]+1;
		for ( pu = find(u), l = 0; l < ptr[pu]-o[pu]; ++l ) {
			v = o[pu][l];
			if ( ROUTE(v) == rt ) continue;
			if ( d[v] > d[u]+3 )
				d[*tail++=v]=d[p[v]=u]+3;
		}
	}
	return d[dst];
}

void 
dump( const unsigned int src, unsigned int u ) {
	unsigned int v;
	int x,rt,px,prt;
	assert( u < +oo );
	if ( u == src ) {
		printf(" %c%c",(char)(ROUTE(u)+'A'),(char)(STATION(u)+'a'));
		return ;
	}
	dump(src,p[u]);
	x = STATION(u), rt = ROUTE(u);
	if ( ROUTE(p[u]) != rt ) 
		printf("=%c%c",rt+'A',x+'a');
	else 
		printf("%c",x+'a');
}

int main() {
	int i,j,k,l;
	unsigned int u,v;
	char tmp[0x400],road_name,rn,ch;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%s",tmp) && 0[tmp] != '#' ) {
		for ( sscanf(tmp,"%d",&m), i = 0; i < Q; ++i )
			deg[i] = len[i] = 0;
		for ( l = 0; l < m; ++l ) {
			for ( scanf("%s",tmp), road_name = 0[tmp], top = st, j = 2; tmp[j]; ) {
				if ( islower(tmp[j]) ) {
					*++top = u = enc(road_name,tmp[j]), ++j;
					continue ;
				}
				if ( tmp[j] == '=' ) {
					rn = tmp[++j];
					assert( isupper(rn) );
					ch = tmp[++j];
					assert( islower(ch) );
					v = enc(rn,ch);
					other_names[u][len[u]++] = v, other_names[v][len[v]++] = u, ++j;
				}
			}
			for ( k = 1; k <= top-st-1; ++k ) {
				u = st[k], v = st[k+1];
				adj[u][deg[u]++] = v, adj[v][deg[v]++] = u;
			}
		}
		for ( u = 0; u < N; ++u ) make_set(u);
		for ( u = 0; u < N; ++u )
			for ( i = 0; i < len[u]; ++i ) {
				if ( find(u) != find(other_names[u][i]) )
					merge(u,other_names[u][i]);
				for ( j = i+1; j < len[u]; ++j )
					if ( find(other_names[u][i]) != find(other_names[u][j]) )
						merge(other_names[u][i],other_names[u][j]);
			}
		for ( u = 0; u < N; ++u )
			ptr[u] = o[u];
		for ( u = 0; u < N; ++u )
			find(u);
		for ( u = 0; u < N; ++u )
			*ptr[find(u)]++ = u;
		while ( 1 == scanf("%s",tmp) && 0[tmp] != '#' ) {
			u = enc(0[tmp],1[tmp]), v = enc(2[tmp],3[tmp]);
			printf("%3u:",dijkstra(u,v));
			dump(u,v);
			putchar('\n');
		}
		break ;
	}
	return 0;
}


