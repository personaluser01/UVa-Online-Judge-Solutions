/*
 * 10544. Numbering the Paths
 * TOPIC: dp, dag, recursion
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define L(k) (((~(k))+1UL)&(k))
#define N 26
typedef unsigned long long u64;
#define oo 0xffffffffffffffffull

int ts,cs,m,n;
char which[1<<21];
unsigned int adj[N];
u64 z[N][N];

int who( unsigned int u ) {
	if ( u >= BIT(20) )
		return 20+which[u>>20];
	return which[u];
}

u64 calc_z( int x, int y ) {
	int t;
	if ( !(adj[x]&BIT(y)) )
		return z[x][y]=0;
	if ( z[x][y]<+oo )
		return z[x][y];
	if ( !adj[y] ) 
		return z[x][y]=1ULL;
	for ( z[x][y]=0, t = 0; t < n; ++t ) 
		z[x][y] += calc_z(y,t);
	return z[x][y];
}

u64 f( int x, char *a ) {
	int t,y = *a-'A';
	u64 ans = 0;
	if ( !*a ) return 1ULL;
	for ( t = 0; t <= y-1; ++t )
		ans += calc_z(x,t);
	return ans+f(y,a+1);
}

int main() {
	int i,j,k,x,y,qr;
	unsigned int u,v;
	char tmp[0x10];
	u64 ax;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 21; ++i ) which[BIT(i)] = i;
	for ( scanf("%d",&ts); ts--; ) {
		for(memset(z,0xffull,sizeof z),scanf("%d %d",&n,&m),i=0;i<n;adj[i++]=0);
		for(k=0;k<m;++k) 
			scanf("%s",tmp),i=0[tmp]-'A',j=1[tmp]-'A',adj[i]|=BIT(j), 0&&printf("Adding route %c->%c\n",i+'A',j+'A');
		for(scanf("%d",&qr);qr--&&1==scanf("%s",tmp);printf("%s: %llu\n",tmp,f(0[tmp]-'A',tmp+1)));
	}
    return 0;
}


