/*
 * 10927. Bright Lights
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#define N 100100
#define tol 1e-11
typedef long double ld;
typedef long long i64;
typedef struct { ld ang; int x,y,z; i64 d; } cell;
#define pi (2*acos(0.00))

ld get_angle( ld a, ld b, ld c, ld d ) {
	ld L = sqrt((a*a+b*b)*(c*c+d*d)),
	   co = (a*c+b*d)/L,
	   si = (a*d-b*c)/L;
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}

int cmp( const void *A, const void *B ) {
	cell *a = (cell *)A,
		 *b = (cell *)B;
	if ( fabs(a->ang-b->ang) < tol ) {
		if ( a->d == b->d )
			return 0;
		return a->d < b->d ? -1 : 1;
	}
	return a->ang < b->ang ? -1 : 1;
}

int cmp_by_xy( const void *A, const void *B ) {
	cell *a = (cell *)A,
		 *b = (cell *)B;
	if ( a->x == b->x ) {
		if ( a->y == b->y )
			return 0;
		return a->y < b->y ? -1 : 1;
	}
	return a->x < b->x ? -1 : 1;
}


int larger_than( ld x, ld y ) { return fabs(x-y) >= tol && x > y; }

int n,ts,m;
cell c[N],a[N];
int idx[N];

int main() {
	int i,j,k,l,t,s,ix,iy,iz;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;1==scanf("%d",&n) && n;) {
		for ( i = 0; i < n; ++i ) {
			scanf("%d %d %d",&c[i].x,&c[i].y,&c[i].z);
			c[i].ang = get_angle(1,0,(ld)c[i].x,(ld)c[i].y);
			assert( -pi <= c[i].ang && c[i].ang <= pi );
			c[i].d = ((i64)c[i].x)*((i64)c[i].x)+((i64)c[i].y)*((i64)c[i].y);
		}
		qsort(c,n,sizeof *c,cmp);
		for ( m = 0, i = 0; i < n; i = j ) {
			for ( k = 0, j = i; j < n && fabs(c[j].ang-c[i].ang) < tol; idx[k++] = j++ );
			for ( l = 0; l < k-1; ++l )
				assert( larger_than(c[idx[l+1]].d,c[idx[l]].d) );
			for ( l = 0; l < k; l = t ) {
				for ( t = l+1; t < k && c[idx[t]].z>c[idx[t-1]].z; ++t );
				for ( s = t-1; t < k && c[idx[t]].z<=c[idx[s]].z; a[m++] = c[idx[t++]] );
			}
		}
		printf("Data set %d:\n",++ts);
		if ( !m ) {
			puts("All the lights are visible.");
			continue ;
		}
		qsort(a,m,sizeof *a,cmp_by_xy);
		puts("Some lights are not visible:");
		for ( i = 0; i < m; ++i ) 
			printf("x = %d, y = %d%c\n",a[i].x,a[i].y,i==m-1?'.':';');
	}
	return 0;
}

