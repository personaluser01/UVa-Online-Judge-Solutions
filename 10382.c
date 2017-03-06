/*
 * 10382. Watering Grass
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
typedef long long i64;
#define N 10100
#define tol 1e-9
#define S(x) ((x)*(x))

typedef struct {
	long double a,b;
} segment;

i64 n,L,W,x[N],r[N],m;
int id[N];
segment c[N];
long double a[N],b[N],A[N],B[N];

int cmp( const void *a, const void *b ) {
	segment *x = (segment *)a,
			*y = (segment *)b;
	if ( fabs(x->a-y->a) < tol ) {
		if ( fabs(x->b-y->b) < tol )
			return 0;
		return x->b < y->b ? 1 : -1;
	}
	return x->a < y->a ? -1 : 1;
}

int main() {
	int i,j,k,l,t;
	long double left,right,mx;
#ifndef ONLINE_JUDGE
	freopen("10382.in","r",stdin);
#endif
	while ( 3 == scanf("%lld %lld %lld",&n,&L,&W) ) {
		for(m=0;n--;scanf("%lld %lld",x+m,r+m),r[m]>W/2.00?++m:1);
		for(i=0;i<m;++i){
			c[i].a=x[i]-sqrt(S(r[i])-S(W/2.00));
			c[i].b=x[i]+sqrt(S(r[i])-S(W/2.00));
		}
		qsort(c,m,sizeof *c,cmp);
		for ( i = 0; i < m; ++i )
			a[i] = c[i].a, b[i] = c[i].b;
		for ( mx = -1024, i = 0; i < m; ++i )
			if ( a[i] <= 0 && b[i] >= 0 )
				if ( b[i] > mx )
					mx = b[j = i];
		if ( mx < 0 ) {
			nx: puts("-1");
			continue ;
		}
		for ( n = 1, k = 0, left = a[j], right = b[j], i = j+1; i < m && right < L; right = b[t], ++n, i = t+1 ) {
			for ( mx = -1024, l = i; l < m && a[l] <= right; ++l )
				if ( b[l] > mx )
					mx = b[t = l];
			if ( mx < 0 ) goto nx;
		}
		if ( right < L ) 
			goto nx;
		printf("%lld\n",n);
	}
	return 0;
}
