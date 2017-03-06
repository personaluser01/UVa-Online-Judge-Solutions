/*
 * 11411. MiniMice
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cmath>
#define N M
using namespace std;
typedef long long i64;
#define M 5000101
#define A(k) ((k)<0?-(k):(k))

int ts,m,n;
bool is[M];
unsigned short z[M];
short buck[0x200],s[0x200],*ptr,out[0x200],*qtr;
int g[0x100][0x100];

int main() {
	i64 i,j,k,l,t,a,b,ni,nj,w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 0; i < N; ++i ) z[i] = 1;
	for (is[2]=true,i=3;i<N;is[i]=true,i+=2);
	for ( i = 2; i < N; ++i )
		if ( is[i] && ++z[i] )
		for ( j = i+i; j < N; z[j] *= (l+1), j += i ) 
			for ( is[j] = false, t = j, l = 0; !(t % i); t /= i, ++l );
	for ( k = 0, i = 0; i < N; ++i )
		if ( z[i] > k )
			k = z[i];
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%lld %lld",&a,&b); ) {
		memset(buck,0,sizeof(buck));
		for(;a<=b;++buck[z[a++]], buck[z[a-1]] = min((short)2,buck[z[a-1]]) );
		for ( ptr = s, k = 0; k < 0x200; ++k ) 
			if ( buck[k] ) *ptr++ = k;
		if ( buck[0[s]] >= 2 )
			l = 2;
		else l = 1;

		for ( qtr = out, k = 0; k < ptr-s; ++k )
			for (;buck[s[k]]--; *qtr++ = s[k] );
		for ( i = j = 0[out], l = 1, w = 0; l < qtr-out;) {
			if ( l == qtr-out-1 ) {
				w = max(w,max(A(out[l]-i),A(out[l]-j)));
				break ;
			}
			ni = out[l], nj = out[l+1], l += 2;
			if ( max(A(ni-i),A(nj-j)) > max(A(nj-i),A(ni-j)) )
				swap(ni,nj);
			w = max(w,max(A(ni-i),A(nj-j)));
			i = ni, j = nj;
		}
		printf("%lld\n",w);
	}
	return 0;
}

