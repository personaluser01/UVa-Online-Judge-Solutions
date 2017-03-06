/*
 * 10109. Solving Systems of Linear Equations
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 64
#define M 6
#define xchg(x,y) (((x) == (y))||((x)^=(y),(y)^=(x),(x)^=(y)))
typedef long long i64;

typedef struct fractio { int x[M],y[M]; } fractio;

void mult( fractio *a, fraction *b ) {
	i64 i,k;
	for ( i = 0; i < M; ++i ) {
		k = a->x[i], k *= b->x[i], a->x[i] = k % pr[i];
		k = a->y[i], k *= b->y[i], a->y[i] = k % pr[i];
	}
}

void add( fractio *a, fractio *b ) {
	i64 i,j,k,l,t,m[M],n[N];
	for ( i = 0; i < M; ++i ) 
		m[i] = a->x[i]*b->y[i];
	for ( i = 0; i < M; ++i ) 
		n[i] = a->y[i]*b->x[i];
	for ( i = 0; i < M; ++i ) {
		a->x[i] = (m[i] + n[i]) % pr[i];
		k = a->y[i], k *= b->y[i], a->y[i] = k % pr[i];
	}
}

void negate( fractio *a ) {
	i64 i;
	for ( i = 0; i < M; ++i )
		a->x[i] = -a->x[i]; 
}

void subtr( fractio *a, fractio *b ) {
	negate(b), add(a,b), negate(b);
}

void recipr( fractio *a ) {
	int i;
	for ( i = 0; i < M; ++i )
		xchg(a->x[i],a->y[i]);
}

void divide_fr( fractio *a, fractio *b ) {
	recipr(b), mult(a,b), recipr(b);
}

i64 pr[] = {1931LL, 3041LL, 8053LL, 11113LL, 8761LL, 2LL},
	without[2][M],matr[M][M];
int no_solution,inf_many,free_vars;

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	if ( !y ) { *a = 1, *d = x, *b = 0; return ; }
	ext_euclid(y,x%y,b,a,d), *b -= (*a)*(x/y);
	assert( (*a)*x + (*b)*y == *d );
}

i64 modinv( i64 x, i64 p ) {
	i64 a,b,d;
	ext_euclid(x,p,&a,&b,&d);
	for (;a < 0; a += p );
	return a % p;
}

i64 gcd( i64 x, i64 y ) {
	if ( !y ) return x;
	return gcd(y,x%y);
}

void repr( fractio *a ) {
	i64 Product = 1LL,i,j,k,m=0,n=0,d;
	for ( i = 0; i < M; Product *= pr[i++] );
	for ( i = 0; i < M; ++i )
		m += without[0][i]*a->x[i]*without[1][i];
	for ( i = 0; i < M; ++i )
		n += without[0][i]*a->y[i]*without[1][i];
	d = gcd(m,n), m /= d, n /= d;
	printf("%lld / %lld\n",m,n);
}

int m,n;
i64 A[N][N],B[N],x[N];

void read_frac( fractio *a ) {
	int ch,sign = 1;
	while ( (ch = getchar()) != EOF && ch != '-' && ch != '+' && !isdigit(ch) );
	assert( ch != EOF );
	if ( ch == '-' || ch == '+' ) {
		if ( ch == '-' ) sign = -1;
	}
	else {
		m = ch-'0';
	}
	while ( (ch = getchar()) 
}

int main() {
	int i,j,k,t,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < M; ++i )
		for ( j = 0; j < M; ++j )
			if ( i != j )
				mat[i][j] = modinv(pr[i],pr[j]);
	for ( i = 0; i < M; ++i )
		for ( without[0][i] = without[1][i] = 1, j = 0; j < M; ++j ) {
			if ( j != i ) {
				without[0][i] *= pr[j];
				without[1][i] *= mat[j][i];
			}
		}
	while ( 1 == scanf("%d",&ts) && ts ) {
		if ( cs++ ) putchar('\n');
		printf("Solution for Matrix System # %d\n",ts);
		scanf("%d %d",&n,&m);
		for ( i = 0; i < m; read_frac(&B[i++]) ) 
			for ( j = 0; j < n; read_frac(&A[i][j++]) );
	}
	return 0;
}

