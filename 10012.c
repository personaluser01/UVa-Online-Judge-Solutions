/*
 * 10012. How Big Is It?
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define tol 1e-9
#define N 10
#define L(i) ((i)&((~(i))+1))
#define M(k) ((1UL<<((k)))-1UL)
#define SQ(k) ((k)*(k))
#define oo (DBL_MAX-100024)
long double min( long double x, long double y ) { return x < y ? x : y; }
long double max( long double x, long double y ) { return x > y ? x : y; }

int m,q[N],*ptr,n,ans[N];
char deg[1 << N],bts[1 << N];
long double r[N],x[N],total,w,ax[N],p;
unsigned int z[N][N],used;

int no_collision( long double xx, int i ) {
	int *qtr;
	if ( xx-r[i] < 0 ) return 0;
	for ( qtr = ptr-1; qtr >= q; --qtr ) 
		if ( *qtr != i && SQ(r[*qtr]+r[i]) > SQ(x[qtr-q]-xx)+SQ(r[*qtr]-r[i]) )
			return 0;
	return 1;
}

void rec( int k ) {
	unsigned int u,i;
	long double good,bad,t;
	assert( k );
	if ( k == n ) {
		for ( p = -oo, i = 0; i < n; ++i )
			p = max(p,x[i]+r[q[i]]);
		w = min(w,p);
		/*
		if (  fabs(w-x[n-1]-r[q[n-1]]) < tol ) {
			for ( i = 0; i < n; ++i )
				ans[i] = q[i], ax[i] = x[i];
		}
		*/
		return ;
	}
	assert( bts[(~used)&M(n)] == n-k );
	for ( u = (~used)&M(n); u; u &= ~(1UL<<i) ) {
		i = deg[L(u)], assert( !((used>>i)&1) );
		assert( (1 << i) == L(u) );
		i = deg[L(u)], used |= (1UL<<i), *ptr++ = i;
		bad = x[k-1], good = total;
		assert( bad < good );
		assert( no_collision(good,i) );
		assert( !no_collision(bad,i) );
		for (;fabs(good-bad)>tol;no_collision(t=(good+bad)/2,i)?(good=t):(bad=t));
		x[k] = good, assert( no_collision(x[k],i) ), rec(k+1);
		used &= ~(1UL<<i), --ptr;
	}
}

int main() {
	int i,j,k,ts;
	unsigned int u,v;
	long double rr[N];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 0; k < N; ++k ) deg[1 << k] = k;
	for ( u = 1; u < (1 << N); ++u )
		bts[u] = bts[u>>1]+(u&1);
	for ( scanf("%d",&ts); ts-- && scanf("%d",&m) == 1; printf("%.3Lf\n",w) ) {
		for ( n = m, total = 0, i = 0; i < m; scanf("%Lf",&r[i++]), total += 3*r[i-1] );
		for ( i = 0, n = 0; i < m; ++i )
			if ( fabs(r[i]) > tol )
				rr[n++] = r[i];
		for ( i = 0; i < n; ++i ) r[i] = rr[i];
		if ( !n ) {
			puts("0.000");
			continue ;
		}
		for ( w = +oo, used = 0, ptr = q, i = 0; i < n; ++i ) {
			used |= (1UL<<i), x[0] = r[*ptr++ = i], rec(1), used &= ~(1UL<<i), --ptr;
			assert( ptr == q );
		}
		/*
		for ( i = 0; i < n; ++i )
			printf("\\draw (%Lf,%Lf) circle [radius=%Lf];\\\n",ax[i],r[ans[i]],r[ans[i]]);
			*/
	}
	return 0;
}

