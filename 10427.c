/*
 * 10427. Two Naughty Boys
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
typedef long long i64;
#define N 15

i64 n,pref[N],d[N];

int main() {
	i64 ax,i,j,k,t,r;
	char s[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( d[0] = ax = 1, i = 1; i < N; ++i )
		pref[i] = pref[i-1] + ax*i, d[i] = (ax *= 10);
	for ( i = 0; i < N; ++i ) pref[i] *= 9;
	for (;1 == scanf("%lld",&n); putchar('\n') ) {
		i = 0, j = N-1;
		assert( pref[i] < n );
		assert( pref[j] >= n );
		for(;i+1<j;pref[k=(i+j)/2]<n?(i=k):(j=k));
		n -= pref[i];
		assert( n );
		if ( n <= j*d[i] ) {
			k = (n-1)/j, r = ((n-1)%j);
			sprintf(s,"%0*lld",(int)i,k);
			putchar(r==0?'1':s[r-1]);
		}
		else{
			k = 1, t = 9;
			assert( j*d[i] < n );
			assert( t*j*d[i] >= n );
			for(;k+1<t;(r=(k+t)/2)*j*d[i]<n?(k=r):(t=r));
			n -= k*j*d[i];
			assert( n );
			k = (n-1)/j, r = ((n-1)%j);
			sprintf(s,"%0*lld",(int)i,k);
			putchar(r==0?t+'0':s[r-1]);
		}
	}
	return 0;
}
