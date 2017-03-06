/*
 * 11809. Floating-Point Numbers
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
#define tol 1e-9
typedef long long i64;

char s[0x400],a[0x400],b[0x400];
int m,e,d2,d5,D2,D5;
i64 A,B,C,E;

i64 Pow( i64 x, int n ) {
	i64 ax = 1;
	while ( n ) {
		if ( n & 1 )
			ax *= x;
		x *= x, n >>= 1;
	}
	return ax;
}

int maxdeg( i64 x, i64 p ) {
	int i = 0;
	for(;x&&(x%p)==0;++i,x/=p);
	return i;
}

i64 divi( i64 x, i64 p, int k ) {
	assert( k >= 0 );
	while ( k-- > 0 ) x /= p;
	return x;
}

i64 P( int n ) {
	return (1LL<<n);
}

int main() {
	int i,j,k,l,t,delta,mm,ee;
	i64 x;
	double LHS,RHS,w,FA;
	char ch;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%s",s) && strcmp("0e0",s) ) {
		w = DBL_MAX-1024;
		sscanf(s,"%[0-9.]%[e]%[0-9]",a,&ch,b);
		B = atol(b);
		for ( k = 0; a[k] != '.'; ++k );
		a[k] = '\0', A = atol(a), C = atol(a+k+1);
		for ( x = 0, i = k+1; a[i]; ++i )
			A = 10LL*A + (i64)(a[i]-'0'), x = 10LL*x+(i64)(a[i]-'0');
		d2 = maxdeg(A,2), d5 = maxdeg(A,5);
		assert( x == C );
			a[k] = '.', FA = (double)atof(a);
			for ( m = 0; m <= 9; ++m )
				for ( e = 1; e <= 30; ++e ){
					LHS = (P(e)-m-2)*log(2.0)-B*log(10.0);
					RHS = log(FA)-log(P(m+1)-1);
					if ( fabs(LHS-RHS)<w )
						w = fabs(LHS-RHS), mm = m, ee = e;
				}
		printf("%d %d\n",mm,ee);
out: continue ;
	}
	return 0;
}
