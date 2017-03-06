/*
 * 11091. How Many Knight Placing?
 * TOPIC: matrix power, repeated squaring, recurrence relations, bitmasks
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define  MOD 	 10007LL
#define  BIT(k)  (1ULL<<(k))
#define  MASK(k) (BIT(k)-1ULL)
#define  N		 72
using namespace std;
typedef long long i64;
typedef unsigned long long u64;

char bts[BIT(21)];
int m;
unsigned int mask[6],M[BIT(6)],e[BIT(12)];

i64 f( i64 x, i64 y ) {
	u64 z;
	for ( ;x<0; x += MOD );
	for ( ;y<0; y += MOD );
	x %= MOD, y %= MOD;
	z = (((u64)x)+((u64)y))%MOD;
	return z%MOD;
}

class matrix {
		public:
			i64 x[N][N];
		matrix() {
			for ( int i = 0; i < m; ++i )
				for ( int j = 0; j < m; x[i][j++] = 0 );
		} ;
		matrix( bool isunit ) {
			for ( int i = 0; i < m; ++i )
				for ( int j = 0; j < m; x[i][j]=(isunit&&i==j?1:0), ++j );
		} ;
		void init() {
			for ( int i = 0; i < m; ++i )
				for ( int j = 0; j < m; x[i][j++] = 0 );
		} ;
		void operator *= ( const matrix &b ) {
			matrix r;
			for ( int k = 0; k < m; ++k )
				for ( int i = 0; i < m; ++i )
					for ( int j = 0; j < m; ++j ) 
						r.x[i][j]=f(r.x[i][j],this->x[i][k]*b.x[k][j]);
			for ( int i = 0; i < m; ++i )
				for ( int j = 0; j < m; ++j )
					this->x[i][j] = r.x[i][j];
		} ;
		matrix *mypow( i64 n ) {
			matrix *ax = new matrix(true), X = *this;
			for (;n; n>>=1, X*=X )
				if ( n&1 ) *ax *= X;
			return ax;
		} ;
} ;

class vec {
	public:
		i64 x[N];
	vec() {
		for ( int i = 0; i < m; x[i++] = 0 );
	} ;
	void init() {
		for ( int i = 0; i < m; x[i++] = 0 );
	} ;
} ;

vec operator * (const matrix &A, const vec &v ) {
	vec r;
	for ( int i = 0; i < m; ++i )
		for ( int j = 0; j < m; ++j )
			r.x[i] = f(r.x[i],A.x[i][j]*v.x[j]);
	return r;
} ;

matrix A;
vec v0;
i64 ans,n;
unsigned int vx[BIT(12)];
int id[BIT(12)];

int main() {
	int i,j,k,ts;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( k = 0; k < BIT(21); bts[k]=bts[k>>1]+(k&1), ++k );
	mask[0] = BIT(2)|BIT(7);
	mask[1] = BIT(3)|BIT(6)|BIT(8);
	mask[2] = BIT(0)|BIT(4)|BIT(7)|BIT(9);
	mask[3] = BIT(1)|BIT(5)|BIT(8)|BIT(10);
	mask[4] = BIT(2)|BIT(9)|BIT(11);
	mask[5] = BIT(3)|BIT(10);
	for ( u = 0; u < BIT(12); id[u++] = -1 );
	for ( i = 0; i < 6; ++i )
		for ( j = i+1; j < 6; ++j )
			M[BIT(i)|BIT(j)] = mask[i]|mask[j];
	for ( u=0; u<BIT(6); ++u )
		if ( bts[u]==2 )
			for ( v=0; v<BIT(6); ++v )
				if ( bts[v]==2 ) 
					if ( !((M[u]&MASK(6))&v) )
						e[m]=(M[u]>>6)|M[v], id[vx[m]=u|(v<<6)]=m, ++m;
	for ( j = 0; j < m; ++j )
		for ( u=(MASK(6)&~e[j]), v=u; v; v=(v-1)&u )
			if ( bts[v] == 2 ) {
				i = id[(vx[j]>>6)|(v<<6)];
				assert( 0 <= i && i < m );
				++A.x[i][j];
			}
	for ( scanf("%d",&ts); ts-- && 1==scanf("%lld",&n); ) {
		for ( v0.init(), i = 0; i < m; v0.x[i++] = 1LL );
		if ( n == 1 ) { puts("15"); continue ; }
		vec res = (*(A.mypow(n-2)))*v0;
		for ( ans = 0, i = 0; i < m; )
			if ( (ans+=res.x[i++]) >= MOD )
				 ans -= MOD;
		printf("%lld\n",ans);
	}
	return 0;
} ;


