/*
 * 11741. Ignore the Blocks
 * TOPIC: matrix power, recurrence relations, bitmasks, dp, repeated squaring
 * status:
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define N 0x80
#define MOD 10000007LL
typedef long long i64;
using namespace std;
#define MAXR 4
#define M (1<<MAXR)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,i) (((u)>>(i))&1ULL)

int m,n,tiles;
vector<pair<int,int> > vec;

i64 f( i64 x, i64 y ) {
	i64 z;
	for ( y%=MOD, z = x+y; z<0; z+=MOD );
	return z%MOD;
}

struct matrix {
	i64 x[M][M];
	matrix() {
		for ( int i = 0; i < (1<<m); ++i )
			for ( int j = 0; j < (1<<m); this->x[i][j++] = 0 );
	};
	matrix( bool is_unit ) {
		for ( int i = 0; i < (1<<m); ++i )
			for ( int j = 0; j < (1<<m); ++j )
				this->x[i][j] = (is_unit&&i==j?1:0);
	};
	matrix *mult( matrix &other ) {
		matrix *r = new matrix(false);
		for ( int k = 0; k < (1<<m); ++k )
			for ( int i = 0; i < (1<<m); ++i )
				for ( int j = 0; j < (1<<m); ++j )
					r->x[i][j]=f(r->x[i][j],(this->x[i][k]*other.x[k][j])%MOD);
		return r;
	} ;
	void set_item( int r, int c, i64 val ) { this->x[r][c]=f(val,0); } ;
	i64 get_item( int r, int c ) const { return this->x[r][c]; } ;
	void init() {
		for ( int i = 0; i < (1<<m); ++i )
			for ( int j = 0; j < (1<<m); x[i][j++] = 0 );
	} ;
	void inc_item( int r, int c ) { x[r][c]=f(x[r][c],1); } ;
	void inc_item( int r, int c, i64 val ) { x[r][c]=f(x[r][c],val); } ;
	void operator *= ( const matrix &other ) {
		matrix res;
		for ( int k = 0; k < (1<<m); ++k )
			for ( int i = 0; i < (1<<m); ++i )
				for ( int j = 0; j < (1<<m); ++j ) 
					res.inc_item(i,j,((this->get_item(i,k))*(other.get_item(k,j)))%MOD);
		for ( int i = 0; i < (1<<m); ++i )
			for ( int j = 0; j < (1<<m); ++j )
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
	column_vector() { for ( int i = 0; i < (1<<m); x[i++] = 0 ); } ;
	void init() { for ( int i = 0; i < (1<<m); x[i++] = 0 ); } ;
} ;

column_vector operator * ( const matrix &A, const column_vector &v ) {
	column_vector r;
	for ( int i = 0; i < (1<<m); ++i )
		for ( int j = 0; j < (1<<m); ++j )
			r.x[i] = f(r.x[i],(A.x[i][j]*v.x[j])%MOD);
	return r;
} ;

matrix A;
bool is_good[MAXR+1][1<<MAXR];
column_vector v0,v1;

int main() {
	int i,j,k,ts,cs=0,t,prev_t;
	unsigned int u,v,base;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	for ( m = 1; m <= MAXR; ++m )
		for ( u = 0; u < (1<<m); ++u ) 
			for ( is_good[m][u] = true, i = 0; i < m && is_good[m][u]; i = k ) {
				for ( j = i; j < m && !TST(u,j); ++j );
				if ( j == m ) break ;
				for ( k = j+1; k < m && TST(u,k); ++k );
				if ( (k-j)&1 ) is_good[m][u] = false ;
			}
	for ( ;3==scanf("%d %d %d",&m,&n,&tiles) && (m||n||tiles) && printf("Case %d: ",++cs); ) {
		for ( vec.clear(), i = 0; i < tiles; ++i ) scanf("%d %d",&j,&k), vec.push_back(make_pair(k+1,j));
		sort(vec.begin(),vec.end()), A.init();
		for ( u = 0; u < (1<<m); (is_good[m][u]?A.inc_item(u,MASK(m)):(void)0), ++u ) 
			for ( v = u; v; v = (v-1)&u ) 
				if ( is_good[m][u&~v] )
					A.inc_item(u,MASK(m)&~v);
		for ( v0.init(), u = 0; u < (1<<m); ++u )
			if ( is_good[m][u] ) v0.x[u] = 1LL;
		for ( prev_t=1, i=0; i<(int)vec.size(); prev_t=t, i=j ) {
			for ( j=i+1; j<(int)vec.size() && vec[j].first==vec[i].first; ++j );
			for ( v=0, k=i; k<j; v|=BIT(vec[k].second), ++k );
			t = vec[i].first, v1 = (*(A.mypow(t-prev_t)))*v0;
			for ( v0.init(), u=0; u<(1<<m); ++u )
				if ( (u&v)==v )
					v0.x[u]=f(v0.x[u],v1.x[u&~v]);
		}
		v1=(*(A.mypow(n-prev_t)))*v0;
		printf("%lld\n",v1.x[MASK(m)]);
	}
	return 0;
}

