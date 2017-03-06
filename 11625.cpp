/*
 * 11625. Nice Prefixes
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <cfloat>
#include <iostream>
#include <map>
#define MOD 1000000007ULL
#define L 64
#define Q (N*((N-1)/2))
#include <vector>
#include <set>
#define N 0x100
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
#define CLR(x,a) (memset((x),(a),sizeof(x)))

i64 n,K;

struct Matrix {
	i64 dat[N][N];
	Matrix() {
		CLR(dat,0);
		for ( int i = 0; i <= K; ++i )
			dat[i][i] = 1;
	}
};

const Matrix operator*( const Matrix &A, const Matrix &B ) {
	Matrix C;
	for ( int i = 0; i <= K; ++i )
		for ( int j = 0; j <= K; ++j ) {
			C.dat[i][j] = 0;
			for ( int k = 0; k <= K; ++k )
				C.dat[i][j] += A.dat[i][k]*B.dat[k][j], C.dat[i][j] %= MOD;
		}
	return C;
}

const Matrix expmod( Matrix X, u64 n ) {
	Matrix ret;
	for(;n; n >>= 1, X=X*X )
		if ( n & 1 )
			ret=ret*X;
	return ret;
}

i64 z[2][N];

int dodp( int S ) {
	int i,j,k,t,
		m0,m1,m2,
		n0,n1,n2;

	for ( t = i = 0; i < S; ++i, t ^= 1 ) {
		CLR(z[1-t],0);
		for ( m2 = 0; m2 <= K; ++m2 ) {
			m1 = (((i-2*m2)%K)+K)%K;
			m0 = K-m1-m2;
			if(m0<1||m0+m1+m2>K)
				continue ;
			n0 = m0-1, n1 = m1+1, n2 = m2;
			if ( !n0 ) n0 = m1+1, n1 = m2, n2 = 0;
			z[1-t][n2] += m0*z[t][m2], z[1-t][n2] %= MOD;
			if ( m1 >= 1 ) {
				n0 = m0, n1 = m1-1, n2 = m2+1;
				z[1-t][n2] += m1*z[t][m2], z[1-t][n2] %= MOD;
			}
		}
	}
	return S&1;
}


int main() {
	int i,j,k,l,ts;
	u64 ax;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%lld %lld",&n,&K);
		i64 q = n/(K),
			r = n%(K);
		Matrix X;
		for ( k = 0; k <= K; ++k ) {
			CLR(z,0), z[0][k] = 1;
			i = dodp(K);
			for ( j = 0; j <= K; ++j )
				X.dat[k][j] = z[i][j];
		}
		Matrix Y = expmod(X,q);
		CLR(z,0);
		for ( k = 0; k <= K; ++k ) z[0][k] = Y.dat[0][k];
		i = dodp(r);
		for ( ax = 0, k = 0; k <= K; ++k )
			ax += z[i][k], ax %= MOD;
		printf("%lld\n",ax);
	}
	return 0;
}
