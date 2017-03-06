/*
 * 10268. 498'
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
#define N (1 << 20)

int x,c[N],n,t,ax,sig;

int lue( int *r ) {
	int sign = 1,ch,n = 0;
	while ( (ch = getchar()) != EOF && ch != '\n' && !(ch == '-'||isdigit(ch)) );
	if ( ch == '\n'||ch == EOF ) {
		if ( ch == EOF ) sig = 1;
		return 0;
	}
	if ( ch == '-' ) sign = -1, ch = getchar();
	for (;ch != '\n' && ch != EOF && isdigit(ch); n = 10*n+ch-'0', ch = getchar() );
	*r = n*sign;
	if ( ch == EOF ) sig = 1;
	if ( ch == '\n' ) return 0;
	return 1;
}

int main() {
	int i,j,k,cnt;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;!sig;) {
		lue(&x);
		if ( sig ) break;
		for ( n = 0; lue(c+n); ++n );
		for ( ++n, i = 0, j = n-1; i < j; ++i, --j )
			t = c[i], c[i] = c[j], c[j] = t;
		for ( i = 1; i < n; ++i ) c[i-1] = i*c[i];
		for ( ax = 0, i = n-2; i >= 0; ax *= x, ax += c[i--] );
		printf("%d\n",ax);
	}
	return 0;
}
