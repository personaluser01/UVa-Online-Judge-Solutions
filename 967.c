/*
 * 967. Circular
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
#define N 1000100
typedef long long i64;

unsigned char a[N>>3];
#define SET(k) (a[(k)>>3] |= (1UL<<((k)&7)))
#define CLR(k) (a[(k)>>3] &= ~(1UL<<((k)&7)))
#define TST(k) (a[(k)>>3] & (1UL<<((k)&7)))
i64 p[N];
int pref[N];
char is[N];

void reverse( i64 *s, int i, int j ) {
	i64 k,t,l;
	for ( k = i, l = j; k < l; ++k, --l )
		t = s[k], s[k] = s[l], s[l] = t;
}

i64 Atoi( i64 *s, int n ) {
	i64 x = 0,i,j,k;
	for ( i = 0; i < n; ++i )
		x = 10*x+s[i];
	return x;
}

int f( i64 p ) {
	i64 s[0x20],i,j,k,n,t[0x20],x;
	for ( n = p, k = 0; n; s[k++] = n%10, n/=10 );
	reverse(s,0,k-1);
	for ( i = 1; i <= k-1; ++i ) {
		for ( j = 0; j < k; ++j ) t[j] = s[j];
		reverse(t,0,i-1), reverse(t,i,k-1), reverse(t,0,k-1);
		x = Atoi(t,k);
		if ( !TST(x) ) return 0;
	}
	return 1;
}

int main() {
	int i,j,k,l,t,low,high,mid,left,right,n;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = 3; i < N; i += 2 ) SET(i);
	for ( i = 3; i < N; i += 2 )
		for ( j = i+i; j < N && TST(i); j += i )
			CLR(j);
	for ( k = 0, SET(2), i = 0; i < N; ++i )
		if ( TST(i) ) p[++k] = i;
	for ( i = 1; i <= k; ++i )
		is[i] = f(p[i]);
	for ( i = 1; i <= k; ++i )
		pref[i] = pref[i-1] + ((int)is[i]);
	for ( n = k; 2 == scanf("%d %d",&i,&j); ) {
		for ( low = 0, high = n; low+1 != high; (p[mid=(low+high)/2]<i)?(low=mid):(high=mid) );
		left = high;
		assert( p[left]>=i );
		assert( p[left-1]<i );
		for ( low = 0, high = n; low+1 != high; (p[mid=(low+high)/2]>j)?(high=mid):(low=mid) );
		right = low;
		assert( p[right] <= j && p[right+1] > j );
		k = pref[right]-pref[left-1];
		if ( !k ) puts("No Circular Primes.");
		else if ( k == 1 ) puts("1 Circular Prime.");
		else printf("%d Circular Primes.\n",k);
	}
	return 0;
}
