/*
 * 1718. Tile Cutting
 * TOPIC: fft, number theory
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cfloat>
#define oo (1LL<<60)
#define Q (N>>1)
#define N (1<<20)
#define J complex<long double>(0.00,1.00)
#define tol 1e-10
typedef long long i64;
using namespace std;

int d[Q];
bool isprime[Q];
const long double pi = 2*acos(0.00);

struct vec {
	size_t n;
	complex<long double> *a;
	vec( size_t n ) {
		a = new complex<long double>[this->n = n];
		for ( int i = 0; i < (int)n; a[i++] = complex<long double>(0,0) );
	};
	vec() {
		a = NULL, n = 0;
	};
	~vec() {
		if ( n && a ) delete a;
	};
	void fft( int sign ) {
		complex<long double> c,e;
		int i,j,k;
		if ( this->n == 1 ) 
			return ;
		assert( n >= 2 );
		assert( !(n&(n-1)) );
		vec u(n/2),v(n/2);
		for ( i=0,j=0,k=0; i<n; u.a[j++]=a[i], v.a[k++]=a[i+1], i+=2 );
		assert( j == n/2 );
		assert( k == n/2 );
		u.fft(sign), v.fft(sign), e = exp(sign*2*pi/n*J), c = complex<long double>(1.00,0.00);
		for ( k = 0; k < n/2; ++k, c *= e ) {
			a[k]     = u.a[k] + c*v.a[k];
			a[k+n/2] = u.a[k] - c*v.a[k];
		}
	};
};

vec D(N),res(N);
i64 t[N<<1];
int pos[N<<1];

i64 nearest( long double x ) {
	i64 dx = (i64)(x+tol), ux = dx+1;
	return x-dx<ux-x?dx:ux;
}

i64 build_tree( int v, int i, int j ) {
	int k = (i+j)/2;
	if ( i == j ) {
		//return t[v] = (i64)(abs(res.a[pos[v]=i])+1e-6);
		return t[v] = nearest(abs(res.a[pos[v]=i]));
		//return t[v] = (i64)(res.a[pos[v]=i].real);
	}
	t[v] = max(build_tree(2*v,i,k),build_tree(2*v+1,k+1,j));
	if ( t[v] == t[v<<1] ) pos[v] = pos[v<<1];
	else pos[v] = pos[2*v+1];
	return t[v];
};

i64 query( int v, int i, int j, int qi, int qj, int &idx ) {
	int k = (i+j)/2,l,r;
	i64 L,R;
	if ( qi > j || qj < i ) 
		return -oo;
	if ( qi <= i && j <= qj ) {
		idx = pos[v];
		return t[v];
	}
	L = query(2*v,i,k,qi,qj,l);
	R = query(2*v+1,k+1,j,qi,qj,r);
	if ( L >= R ) {
		idx = l;
		return L;
	}
	idx = r;
	return R;
};

int main() {
	int i,j,k,l,ts,alo,ahi,o;
	i64 ans;
#ifndef ONLINE_JUDGE
	freopen("tiles.in","r",stdin);
#endif
	for ( isprime[2] = true, i = 3; i < Q; isprime[i] = true, i += 2 );
	for ( i = 3; i < Q; i += 2 )
		for ( j = i+i; j < Q && isprime[i]; isprime[j] = false, j += i );
	for ( i = 1; i < Q; d[i++] = 1 );
	for ( i = 2; i < Q; ++i )
		if ( isprime[i] )
			for ( d[i] = 2, j = i+i; j < Q; d[j] *= (l+1), j += i )
				for ( k=j, l=0; !(k%i); k/=i, ++l );
	for ( i = 0; i < Q; ++i )
		if ( d[i] > 0 )
			D.a[i] = complex<long double>((long double)d[i],0.00);
	for ( D.fft(1), i=0; i<N; res.a[i]=D.a[i]*D.a[i], ++i );
	for ( res.fft(-1), i=0; i<N; res.a[i++]/=N );
	for ( build_tree(1,0,N-1); 1 == scanf("%d",&ts); ) {
		for ( ;ts--; ) {
			scanf("%d %d",&alo,&ahi);
			if ( alo > ahi ) swap(alo,ahi);
			ans = query(1,0,N-1,alo,ahi,i);
			printf("%d %lld\n",i,ans);
		}
	}
	return 0;
};

