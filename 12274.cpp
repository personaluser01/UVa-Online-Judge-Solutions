/*
 * 12274. Jumping Monkey
 * TOPIC: bfs, bitmasks
 * status: Accepted
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 21
#define N BIT(MAXN)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define oo 0xfffffffful
using namespace std;

int n,m,seen[N],yes;
unsigned int mask[MAXN],p[N],d[N];
char who[N],move[N];
queue<unsigned int> q;

void dump( unsigned int u ) { if ( p[u] != -1 ) dump(p[u]), printf(" %d",(int)move[u]); };

int main() {
	int i,j,k;
	bool ok;
	unsigned int u,v,w,nu;
	for ( i = 0; i < MAXN; who[BIT(i)] = i, ++i );
	for (;2==scanf("%d %d",&n,&m)&&(m||n);) {
		for ( i = 0; i < n; mask[i++] = 0 );
		for ( k = 0; k < m; ++k ) 
			scanf("%d %d",&i,&j),mask[i]|=BIT(j),mask[j]|=BIT(i);
		for ( seen[u=MASK(n)]=++yes, p[u]=-1, q.push(u), d[u]=0; !q.empty(); ) {
			for ( u=q.front(), q.pop(), w=u; w && (i=who[L(w)])>=0; w&=~L(w) ) {
				for ( nu=0, v=(u&~BIT(i)); v; v&=~L(v) ) 
					nu |= mask[who[L(v)]];
				if ( seen[nu]!=yes || d[nu]>d[u]+1 )
					seen[nu]=yes, d[nu]=d[u]+1, q.push(nu), move[nu]=i, p[nu]=u;
			}
		}
		if ( seen[0] == yes ) {
			printf("%u:",d[0]), dump(0), putchar('\n');
		}
		else puts("Impossible");
	}
	return 0;
};

