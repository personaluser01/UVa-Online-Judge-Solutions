/*
 * 10716. Evil Straw Warts Live
 * TOPIC: greedy
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define N 0x80
#define A 26
#define oo (1<<29)

char buff[N],*ptr;
int n,c[A],ts;

int f( char *a, int n ) {
	int fst[A],last[A],i,j,k,w = +oo;
	char *b;
	if ( n <= 1 )
		return 0;
	assert( n >= 2 );
	for ( i = 0; i < A; ++i )
		fst[i]=+oo,last[i]=-oo;
	for ( i = 0; i < n; ++i )
		fst[a[i]-'a'] = min(fst[a[i]-'a'],i);
	for ( i = 0; i < n; ++i )
		last[a[i]-'a'] = max(last[a[i]-'a'],i);
	for ( i = 0; i < A; ++i )
		if ( fst[i] < +oo )
			if ( fst[i] != last[i] )
				if ( fst[i]+(n-last[i]-1) < w )
					w=fst[i]+(n-last[i]-1),j=i;
	b = (char *)malloc((n-1)*sizeof *b);
	for ( k = 0, i = 0; i < n; ++i )
		if ( i != fst[j] && i != last[j] ) b[k++] = a[i];
	assert( k == n-2 );
	k = w+f(b,k), free(b);
	return k;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts); ts-- && FG; ) {
		for ( n = 0; buff[n] && buff[n] != '\n'; ++n );
		for ( i = 0; i < A; c[i++] = 0 );
		for ( i = 0; i < n; ++c[buff[i++]-'a'] );
		for ( k = 0, i = 0; i < A; k += (c[i++]&1) );
		if ( k >= 2 ) {
			puts("Impossible");
			continue ;
		}
		assert( k == (n&1) );
		printf("%d\n",f(buff,n));
	}
    return 0;
}

