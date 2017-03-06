/*
 * 1084. Deer-Proof Fence
 * TOPIC: bitmasks, dp
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cfloat>
#define DIM 	3
#define N 		10
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k)    ((k)&((~(k))+1ULL))
#define oo (DBL_MAX-0x400)
#define pi (2*acos(0.00))
using namespace std;

int n,cs;
char bts[BIT(N)],which[BIT(N)];
double margin,z[BIT(N)];
unsigned int way[BIT(N)];

struct cell {
	double x[DIM];
	cell() { for ( int i = 0; i < DIM; x[i++] = 0 ); };
};

cell c[N];

cell operator + ( const cell &a, const cell &b ) {
	cell r; for ( int i = 0; i < DIM; r.x[i] = a.x[i]+b.x[i], ++i );
	return r;
};

cell operator - ( const cell &a, const cell &b ) {
	cell r; for ( int i = 0; i < DIM; r.x[i] = a.x[i]-b.x[i], ++i );
	return r;
};

double operator , ( const cell &a, const cell &b ) {
	double s = 0;
	for ( int i = 0; i < DIM; s += a.x[i]*b.x[i], ++i );
	return s;
};

cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i ) 
		j = ((i+1)%DIM), k = ((j+1)%DIM), r.x[i] = a.x[j]*b.x[k]-a.x[k]*b.x[j];
	return r;
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( a.x[i] != b.x[i] )
			return a.x[i] < b.x[i];
	return false;
};

bool operator == ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( a.x[i] != b.x[i] )
			return false ;
	return true ;
};

bool ccw( const cell &a, const cell &b, const cell &c ) {
	return ((b-a)*(c-a)).x[DIM-1]>0;
};

vector<cell> monotone( const unsigned int u ) {
	cell r[N];
	vector<cell> vec(bts[u]+1);
	int v,i,j,k,m = 0,vsize = 0;
	for ( v=u; v && (i=which[L(v)])>=0; r[m++]=c[i], v&=~L(v) );
	assert( m == bts[u] );
	for ( sort(r,r+m), i = 0; i < m; vec[vsize++] = r[i++] ) 
		for(;vsize >= 2 && !ccw(vec[vsize-2],vec[vsize-1],r[i]); --vsize );
	for ( i = m-1, j = vsize+1; i >= 0; vec[vsize++] = r[i--] ) 
		for ( ;vsize >= j && !ccw(vec[vsize-2],vec[vsize-1],r[i]); --vsize );
	assert( vec[vsize-1] == vec[0] );
	vec.resize(--vsize);
	assert( vec.size() == vsize );
	return vec;
};

double compute_fence( const vector<cell> &vec ) {
	double s = 0;
	if ( !vec.size() ) return 0.00;
	if ( vec.size() == 1 ) 
		return 2*pi*margin;
	if ( vec.size() == 2 ) 
		return 2*pi*margin+2*sqrt((vec[0]-vec[1],vec[0]-vec[1]));
	assert( vec.size() >= 3 );
	for ( auto i = 0; i < vec.size(); s += sqrt((vec[i]-vec[(i+1)%vec.size()],vec[i]-vec[(i+1)%vec.size()])), ++i );
	return s+2*pi*margin;
};

double calc_z( const unsigned int u ) {
	unsigned int v;
	auto &val = z[u];
	if ( z[u] < +oo )
		return z[u];
	for ( val = compute_fence(monotone(u)), way[u]=0, v = (u-1)&u; v; v = (v-1)&u ) 
		if ( (val = min(val,calc_z(v)+calc_z(u&~v))) == calc_z(v)+calc_z(u&~v) )
			way[u] = v;
	return val;
};

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("1084.in","r",stdin);
#endif
	for ( i = 0; i < BIT(N); bts[i] = bts[i>>1]+(i&1), ++i );
	for ( i = 0; i < N; which[BIT(i)] = i, ++i );
	for (;1==scanf("%d",&n)&&n>0;) {
		for ( scanf("%lf",&margin), i = 0; i < n; scanf("%lf %lf",&c[i].x[0],&c[i].x[1]), ++i );
		for ( z[0] = 0, i = 1; i < BIT(n); z[i++] = +oo );
		printf("Case %d: length = %.2lf\n",++cs,calc_z(MASK(n)));
	}
	return 0;
};

