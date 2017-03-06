/*
 * 12291. Polymino Composer
 * TOPIC: smart brute force, technique, accuratnost, bitmasks
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) (((u)>>(k))&1)
#define N 21
typedef unsigned long long u64;

u64 p[N],q[N],r[N];
int m,n,pm,pn,qm,qn;

void normalize( u64 *u, int *m, int *n ) {
	int i,j,k,l,t;
	u64 v[N] = {0};
	for ( k = -1, j = 0; j < *n && k == -1; ++j ) {
		for ( i = 0; i < *m && !TST(u[i],j); ++i );
		if ( i < *m ) k = j;
	}
	if ( k == -1 ) {
		*m = *n = 0;
		return ;
	}
	for ( i = 0; i < *m; u[i++] >>= k );
	for ( k = -1, j = (*n)-1; j >= 0 && k == -1; --j ) {
		for ( i = 0; i < *m && !TST(u[i],j); ++i );
		if ( i < *m ) k = j;
	}
	assert( k != -1 );
	for ( *n = k+1, i = 0; i < *m && !u[i]; ++i );
	assert( i < *m );
	if ( i > 0 ) {
		for ( l = 0; i < *m; v[l++] = u[i++] );
		for ( *m = l, i = 0; i < l;  u[i] = v[i], ++i );
	}
	for (;*m >= 1 && !(u[(*m)-1]); --(*m) );
}

int f( int x0, int y0, int x1, int y1 ) {
	int i,j,k,l,t;
	u64 u[N] = {0};
	assert( x0+qm <= pm );
	assert( x1+qm <= pm );
	memset(u,0,sizeof u);
	0&&printf("%d %d %d %d\n",x0,y0,x1,y1);
	for ( i = x0, l = 0; l < qm; u[i++] |= (q[l++]<<y0) );
	for ( i = x1, l = 0; l < qm; ) 
		if ( !(u[i]&(q[l]<<y1)) )
			u[i++] |= (q[l++]<<y1);
		else return 0;
	for ( i = 0; i < pm; ++i )
		if ( u[i] != p[i] )
			return 0;
	return 1;
}

int main() {
	int i,j,k,t,l,ok,cs = 0;
	char s[0x40];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %d",&n,&m) && (m||n) ) {
		memset(p,0,sizeof p), memset(q,0,sizeof q);
		for ( i = 0; i < n; ++i ) 
			for ( scanf("%s",s), j = 0; j < n; ++j )
				if ( s[j] == '*' )
					p[i] |= BIT(j);
		for ( i = 0; i < m; ++i ) 
			for ( scanf("%s",s), j = 0; j < m; ++j )
				if ( s[j] == '*' )
					q[i] |= BIT(j);
		pm = n, pn = n, qm = m, qn = m;
		normalize(p,&pm,&pn), normalize(q,&qm,&qn);
		for ( ok = 0, i = 0; i+qm <= pm && !ok; ++i )
			for ( j = 0; j+qn <= pn && !ok; ++j )
				if ( i == 0 || j == 0 )
					for ( k = 0; k+qm <= pm & !ok; ++k )
						for ( l = 0; l+qn <= pn && !ok; ++l )
							if ( k+qm == pm || l+qn == pn )
								ok |= f(i,j,k,l);
		puts(ok?"1":"0");
	}
	return 0;
}

