/*
 * 1419. Ugly Windows
 * TOPIC: bfs, cycles, trivial
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SH 7
#define enc(x,y) ((x)|((y)<<SH))
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define Q (BIT(20))
#define N BIT(SH)
#define oo 0xfffffffful
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

unsigned int q[Q],*head,*tail,d[Q],p[Q],e[Q],*top;
int m,n,seen[Q],yes,processed[26],A[N],B[N],C[N],D[N],suspect[26],
	dx[] = {-1,0,1,0},
	dy[] = {0,1,0,-1};
char g[N][N];

int bfs( unsigned int src ) {
	unsigned int u,v;
	int x,y,nx,ny,i,j,k,ch=g[src&MASK(SH)][src>>SH];
	for ( processed[ch-'A']=1, top=e, head=tail=q, p[src]=+oo, seen[*tail++=src]=++yes, d[src] = 0; head < tail; )
		for ( *++top = (u=*head++), x=(u&MASK(SH)),y=(u>>SH), i = 0; i < 4; ++i ) {
			nx=x+dx[i], ny=y+dy[i];
			if ( !vc(nx,ny) || g[nx][ny] != ch ) continue ;
			if ( seen[v=enc(nx,ny)] != yes ) 
				seen[*tail++=v] = yes, d[v]=d[p[v]=u]+1;
			else if ( v != p[u] )
				return 1;
		}
	return 0;
}

int inside( int i, int j ) {
	return A[j] < A[i] && C[i] < C[j] && B[j] < B[i] && D[i] < D[j];
}

int main() {
	int i,j,k,l,t,x,y,flag;
	unsigned int u;
#ifndef ONLINE_JUDGE
	freopen("b.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&m,&n) && (m||n); putchar('\n') ) {
		for ( i = 0; i < m; scanf("%s",g[i++]) );
		for ( k = 'A'; k <= 'Z'; ++k )
			for ( processed[k-'A'] = suspect[k-'A'] = 0, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					if ( g[i][j] == k && !processed[k-'A'] && bfs(enc(i,j)) ) {
						for ( t = k-'A', suspect[t] = 1,  A[t] = C[t] = i, B[t] = D[t] = j; top > e; ) {
							u = *top--, x = (u&MASK(SH)), y = (u>>SH);
							if ( x < A[t] || x == A[t] && y < B[t] )
								A[t] = x, B[t] = y;
							if ( x > C[t] || x == C[t] && y > D[t] )
								C[t] = x, D[t] = y;
						}
					}
		do { 
		for ( flag = 0, i = 0; i < 26 && !flag; ++i )
			for ( j = 0; j < 26 && !flag && suspect[i]; ++j )
				if ( i != j && suspect[j] ) 
					if ( inside(i,j) ) 
						suspect[j] = 0, flag = 1;
		} while ( flag );
		for ( i = 0; i < 26; ++i )
			if ( suspect[i] ) putchar(i+'A');
	}
	return 0;
}

