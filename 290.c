/*
 * 290. Palindromes
 * status: Accepted
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L (1 << 21)

int value( char ch ) {
	if ( isdigit(ch) )
		return ch-'0';
	ch = toupper(ch);
	return ch-'A'+10;
}

char ival( int c ) {
	if ( c >= 10 )
		return 'A'+c-10;
	return c+'0';
}

char buff[L],x[L],y[L];

int legal( int B ) {
	int i;
	for ( i = 0; buff[i] && buff[i] != '\n'; ++i )
		if ( isalnum(buff[i]) )
			if ( value(buff[i]) >= B )
				return 0;
	return 1;
}

int ispalin( int n ) {
	int i,j;
	for ( i = 0, j = n-1; i < j; ++i, --j )
		if ( ival(x[i]) != ival(x[j]) )
			return 0;
	return 1;
}

int simulate( int B ) {
	int steps = 0,i,j,k,t = 0,n;

	for ( n = 0; buff[n] && buff[n] != '\n'; ++n )
		x[n] = value(buff[n]);
	for (;!ispalin(n); ++steps ) {
		for ( i = 0; i <= n+3; y[i++] = 0 );
		for ( i = 0; i < n; ++i )
			y[i] = x[i]+x[n-1-i];
		for ( i = 0; i < n+3; ++i ) 
			if ( y[i] >= B )
				y[i+1] += y[i]/B, y[i] %= B;
		for ( i = n+3; i >= 0 && !y[i]; --i );
		for ( n = i+1, i = 0; i < n; ++i )
			x[i] = y[i];
	}
	return steps;
}

int main() {
	int B,cs = 0,ok;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;fgets(buff,sizeof(buff),stdin); putchar('\n') ) {
		for ( ok = 1, cs = 0, B = 15; B >= 2; --B ) {
			if ( ++cs > 1 ) putchar(' ');
			if (!ok||!legal(B)) {
				ok=0;
				putchar('?');
				continue ;
			}
			printf("%d",simulate(B));
		}
	}
	return 0;
}
