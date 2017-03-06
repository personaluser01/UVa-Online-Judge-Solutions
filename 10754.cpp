/*
 * 10754. Fantastic Sequence
 * TOPIC: repeated squaring, matrix power, linear recurrence, linear transformation, very neat
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define M 0x20
using namespace std;
#define N 0x30
typedef long long i64;
typedef unsigned long long u64;

i64 MOD,K;

i64 f( i64 x, i64 y ) {
	u64 z;
	for ( ;x<0; x += MOD );
	for ( ;y<0; y += MOD );
	x %= MOD, y %= MOD;
	z = (((u64)x)+((u64)y))%MOD;
	return z%MOD;
}

i64 mu( i64 x, i64 y ) {
	for (;x < 0; x += MOD );
	for (;y < 0; y += MOD );
	x %= MOD, y %= MOD;
	return (((u64)x)*((u64)y))%MOD;
}

struct matrix {
	i64 x[M][M];
	matrix() {
		for ( int i = 0; i < K+1; ++i )
			for ( int j = 0; j < K+1; this->x[i][j++] = 0 );
	};
	matrix( bool is_unit ) {
		for ( int i = 0; i < K+1; ++i )
			for ( int j = 0; j < K+1; ++j )
				this->x[i][j] = (is_unit&&i==j?1:0);
	};
	matrix *mult( matrix &other ) {
		matrix *r = new matrix(false);
		for ( int k = 0; k < K+1; ++k )
			for ( int i = 0; i < K+1; ++i )
				for ( int j = 0; j < K+1; ++j )
					r->x[i][j]=f(r->x[i][j],mu(this->x[i][k],other.x[k][j]));
		return r;
	} ;
	void set_item( int r, int c, i64 val ) { this->x[r][c]=f(val,0); } ;
	i64 get_item( int r, int c ) const { return this->x[r][c]; } ;
	void init() {
		for ( int i = 0; i < K+1; ++i )
			for ( int j = 0; j < K+1; x[i][j++] = 0 );
	} ;
	void inc_item( int r, int c ) { x[r][c]=f(x[r][c],1); } ;
	void inc_item( int r, int c, i64 val ) { x[r][c]=f(x[r][c],val); } ;
	void operator *= ( const matrix &other ) {
		matrix res;
		for ( int k = 0; k < K+1; ++k )
			for ( int i = 0; i < K+1; ++i )
				for ( int j = 0; j < K+1; ++j ) 
					res.inc_item(i,j,((this->get_item(i,k))*(other.get_item(k,j)))%MOD);
		for ( int i = 0; i < K+1; ++i )
			for ( int j = 0; j < K+1; ++j )
				this->set_item(i,j,res.get_item(i,j));
	}
	matrix *mypow( i64 n ) {
		matrix *ax = new matrix(true), X = *this;
		for (;n; n >>= 1, X *= X )
			if ( n&1 ) *ax *= X;
		return ax;
	} ;
} ;

struct column_vector {
	i64 x[M];
	column_vector() { for ( int i = 0; i < K+1; x[i++] = 0 ); } ;
	void init() { for ( int i = 0; i < K+1; x[i++] = 0 ); } ;
} ;

column_vector operator * ( const matrix &A, const column_vector &v ) {
	column_vector r;
	for ( int i = 0; i < K+1; ++i )
		for ( int j = 0; j < K+1; ++j )
			r.x[i] = f(r.x[i],(A.x[i][j]*v.x[j])%MOD);
	return r;
} ;

i64 n,c[N],a[0x400];
matrix A;
column_vector v0,v;

int main() {
	int i,j,k,l,t,ts,cs,m;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %lld %lld",&k,&MOD,&n);
		for ( K=k, i = 1; i <= K+1; ++i )
			scanf("%lld",&c[i]), c[i]=f(c[i],0);
		for ( i = 0; i < K; scanf("%lld",&a[i]), a[i]=f(a[i],0), ++i );
		if ( K == 0 ) {
			printf("%lld\n",c[K+1]);
			goto next;
		}
		if ( n < K ) { printf("%lld\n",a[n]); goto next; }
		if ( n <= K+K+K+K+K ) {
			for ( t = K; t <= n; ++t ) {
				for ( a[t]=0, i = 1; i <= k; ++i )
					a[t] = f(a[t],mu(c[i],a[t-i]));
				a[t] = f(a[t],c[K+1]);
			}
			printf("%lld\n",a[n]);
			goto next;
		}
		for ( A.init(), v0.init(), v0.x[K]=1LL, i = 0; i < K; v0.x[i] = a[K-i-1], ++i );
		for ( j = 0, l = 1; l <= K+1; A.set_item(0,j++,c[l++]) );
		A.set_item(0,j,0);
		for ( i = 1, j = 0; i <= K-1; A.set_item(i++,j++,1LL) );
		A.set_item(K,K,1LL);
		v = (*(A.mypow(n-K+1)))*v0;
		printf("%lld\n",v.x[0]);
		next: if ( ts ) putchar('\n');
	  	continue ;
	}
	return 0;
}

