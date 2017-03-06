/*
 * 547. DDF
 * status: Accepted
 */
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 8000
#include <vector>
using namespace std;
typedef long long i64;

i64 L,R,p[N],m,sf[N],n;
bool is[N];

void factorize( i64 n, vector<pair<i64,int> > &v ) {
	int i,j,k;
	pair<i64,int> r;
	v.clear();
	for ( i = 0; i < m; ++i )
		if ( !(n % p[i]) ) {
			for ( r.first = p[i], r.second = 0; !(n % p[i]); n /= p[i], ++r.second );
			v.push_back(r);
		}
}

i64 Pow( i64 x, int n ) {
	i64 ax = 1LL;
	while ( n ) {
		if ( n & 1 )
			ax *= x;
		x *= x, n >>= 1;
	}
	return ax;
}

int sumdigs( i64 n ) { return n<10?n:sumdigs(n/10)+(n%10); }

void rec( i64 ax, vector<pair<i64,int> > &v, int cur, vector<i64> &d ) {
	i64 a = 1LL;
	if ( cur == v.size() ) {
		d.push_back(ax);
		return ;
	}
	for ( int i = 0; i <= v[cur].second; ++i ) {
		rec(ax*a,v,cur+1,d);
		a *= v[cur].first;
	}
}

int Len[N];

int calc_Len( i64 n ) {
	if (Len[n]>=0)
		return Len[n];
	if ( n == sf[n] )
		return Len[n] = 1;
	return Len[n] = 1+calc_Len(sf[n]);
}

void display( i64 n ) {
	printf(" %lld",n);
	if ( n != sf[n] )
		display(sf[n]);
}

int main() {
	int i,j,k,l,t,cs = 0,w;
	vector<pair<i64,int> > v;
	i64 ax,nn;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 3; i < N; i += 2 ) is[i] = true;
	for ( i = 3; i < N; i += 2 )
		if ( is[i] )
			for ( j = i+i; j < N; j += i )
				is[j] = false;
	for ( m = 0, is[2] = true, i = 0; i < N; ++i )
		if ( is[i] )
			p[m++] = i;
	for ( sf[1] = 1, n = 2; n < N; ++n ) {
		factorize(n,v);
		vector<i64> d;
		d.clear(), rec(1LL,v,0,d);
		for ( sf[n] = 0, i = 0; i < (int)d.size(); ++i )
			sf[n] += sumdigs(d[i]);
	}
	memset(Len,-1,sizeof(Len));
	for ( Len[n = 1] = 1; ++n < N;)
		Len[n] = calc_Len(n);
	while ( 2 == scanf("%lld %lld",&L,&R) ) {
		printf("Input%d: %lld %lld\n",++cs,L,R);
		if ( L > R ) k = L, L = R, R = k;
		printf("Output%d:",cs);
		for ( w = -1, n = L; n <= R; ++n )
			if ( calc_Len(n) > w )
				w = calc_Len(n), nn = n;
		display(nn);
		putchar('\n');
	}
	return 0;
}

