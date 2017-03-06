/*
 * 11754. Code Feat
 * TOPIC: chinese remainder theorem
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
typedef long long i64;

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	if ( !y ) { *a = 1, *d = x, *b = 0; }
	else ext_euclid(y,x%y,b,a,d), *b -= (*a)*(x/y);
}

i64 inv( i64 x, i64 p ) {
	i64 a,b,d,n;
	ext_euclid(x,p,&a,&b,&d);
	if ( a >= 0 ) return a%p;
	for ( n = -a/p; a+p*n < 0; ++n );
	return (a+p*n)%p;
}

int m,n,len[N],K;
i64 r[N][N],Q[N],c[N],ic[N],e[1<<23],R[N],T,*ptr;

i64 CRT() {
	i64 x = 0,i;
	for ( i = 0; i < m; ++i )
		if ( (x+=c[i]*ic[i]*R[i]) >= T )
			x %= T;
		else if ( x < 0 ) for ( ;x<0; x += T );
	return ((x%T)+T)%T;
}

void rec( int idx ) {
	int i,j;
	i64 x;
	if ( idx == m ) {
		x = CRT();
		assert( 0 <= x && x < T );
		/*
		for ( j = K-1; j >= 0 && x < e[j]; --j );
		if ( j >= 0 && x == e[j] ) return ;
		assert( j == -1 || x > e[j] );
		for ( i = K; i >= j+1; e[i] = e[i-1], --i );
		e[j+1] = x;
		if ( K < n ) ++K;
		*/
		*ptr++ = x;
		return ;
	}
	for ( j = 0; j < len[idx]; ++j ) 
		R[idx] = r[idx][j], rec(idx+1);
}

int cmp( const void *a, const void *b ) {
	i64 *x = (i64 *)a,
		*y = (i64 *)b;
	if ( *x == *y ) return 0;
	if ( *x < *y ) return -1;
	return 1;
}

int main() {
	int i,j,k,base,flag;
	i64 o,mn,ratio;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ;2==scanf("%d %d",&m,&n) && (m||n); putchar('\n') ) {
		for ( o=1LL, i=0; i<m; ++i ) 
			for ( scanf("%lld %d",Q+i,len+i), o*=len[i], j=0; j<len[i]; scanf("%lld",&r[i][j++]) );
		for ( i = 0; i < m; ++i )
			qsort(r[i],len[i],sizeof *r[i],cmp);
		if ( o < 100000 ) {
			for ( T = 1LL, i = 0; i < m; T *= Q[i++] );
			for ( i = 0; i < m; ic[i] = inv(c[i],Q[i]), ++i ) 
				for ( c[i] = 1LL, j = 0; j < m; ++j )
					if ( j != i ) c[i] *= Q[j];
			ptr = e, K = 0, rec(0), qsort(e,ptr-e,sizeof *e,cmp);
			for ( i = 0, ratio = 0; i < n; ++ratio ) 
				for ( j = 0; j < ptr-e && i < n; ++j ) 
					if ( mn = e[j]+ratio*T )
						printf("%lld\n",mn), ++i;
		}
		else {
			for ( base = 0, i = 1; i < m; ++i )
				if ( len[base]*Q[i] > len[i]*Q[base] )
					base = i;
			for ( i = 0, ratio = 0; i < n; ++ratio ) 
				for ( j = 0; j < len[base] && i < n; ++j ) {
					if ( !(mn=ratio*Q[base]+r[base][j]) )
						continue ;
					for ( k = 0; k < m; ++k ) {
						o = mn%Q[k];
						if ( !bsearch(&o,r[k],len[k],sizeof *r[k],cmp) ) break ;
					}
					if ( k == m ) 
						printf("%lld\n",mn), ++i;
				}
		}
	}
	return 0;
}

