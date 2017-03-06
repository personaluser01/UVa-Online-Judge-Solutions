/*
 * 11627. Slalom
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
#define N 100100
#define M 1000001
#define IMP (puts("IMPOSSIBLE"))
typedef long long i64;
#define oo ((1LL << 31)-1LL)
#define P(i,t) (x[i]+t*W)
#define tol (1e-9)

int cmp( const void *a, const void *b ) {
	i64 *x = (i64 *)a,
		*y = (i64 *)b;
	if ( *x == *y ) return 0;
	return *x<*y?-1:1;
}

long double W,vh,x[N],y[N],l[N],r[N],TG;
int n;
i64 v[M],miv,mav;

long double min( long double x, long double y ) {
	return x < y ? x : y; 
}
long double max( long double x, long double y ) {
	return x < y ? y : x;
}

int is_possible( i64 velocity ) {
	int i,left,right;
	long double t,low,high,mid;

	TG = vh/velocity, l[n-1] = x[n-1], r[n-1] = x[n-1]+W;
	for ( i = n-2; i >= 0; --i ) {
		l[i] = max(l[i+1]-(y[i+1]-y[i])*TG,x[i]), r[i] = min(r[i+1]+(y[i+1]-y[i])*TG,x[i]+W);
		if ( l[i] > r[i] ) return 0;
	}
	return 1;
}

int main() {
	int i,j,k,ts,m;
	i64 good,bad,mid;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%Lf %Lf %d",&W,&vh,&n);
		for ( i = 0; i < n; ++i ) 
			scanf("%Lf %Lf",x+i,y+i);
		for ( miv = +oo, mav = -oo, scanf("%d",&m), i = 0; i < m; ++i ) {
			scanf("%lld",v+i);
			if ( v[i] < miv ) miv = v[i];
			if ( v[i] > mav ) mav = v[i];
		}
		if ( !is_possible(miv) ) { IMP; continue; }
		if (  is_possible(mav) ) { printf("%lld\n",mav); continue; }
		qsort(v,m,sizeof *v,cmp);
		assert( is_possible(v[good = 0]) );
		assert( !is_possible(v[bad = m-1]) );
		for (good=0,bad=m-1;good+1!=bad;is_possible(v[mid=(good+bad)/2])?(good=mid):(bad=mid));
		printf("%lld\n",v[good]);
	}
	return 0;
}
