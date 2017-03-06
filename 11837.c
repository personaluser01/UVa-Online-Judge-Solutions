/*
 * 11837. Musical Plagiarism
 * TOPIC: kmp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CARD 12
#define N (1<<17)

int m,n,pi[N];
char c[256],x[N],y[N];

char conv( char *s ) {
	if ( !1[s] ) return c[0[s]];
	switch ( 1[s] ) {
		case '#': switch ( 0[s] ) {
						 case 'A': return 'b';
						 case 'B': return 'd';
						 case 'C': return 'e';
						 case 'D': return 'g';
						 case 'E': return 'i';
						 case 'F': return 'j';
						 case 'G': return 'l';
						 default: assert( 0 );
				  }
		default:  assert( 1[s] == 'b' );
				  switch ( 0[s] ) {
						case 'A': return 'l';
						case 'B': return 'b';
						case 'C': return 'c';
						case 'D': return 'e';
						case 'E': return 'g';
						case 'F': return 'h';
						case 'G': return 'j';
						default: assert( 0 );
				 }
	}
}

char next( char ch ) { return (((ch-'a')+1)%CARD)+'a'; }

int kmp() {
	int i,k;
	for ( pi[0] = -1, i = 1; i <= n; pi[i++] = 1+k ) 
		for ( k = pi[i-1]; k+1 && y[k+1] != y[i]; k = pi[k] );
	for ( k = 0, i = 1; i <= m && k < n; ++i, ++k ) 
		for (;k+1 && y[k+1] != x[i]; k = pi[k] );
	return k==n;
}

int main() {
	int i,j,k,found;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	c['A'] = 'a', c['B'] = 'c', c['C'] = 'd', c['D'] = 'f', c['E'] = 'h', c['F'] = 'i', c['G'] = 'k';
	for (;2 == scanf("%d %d",&m,&n) && (m||n); ) {
		for ( i = 1; i <= m; ++i ) 
			scanf("%s",tmp), x[i] = conv(tmp);
		for ( i = 1; i <= n; ++i )
			scanf("%s",tmp), y[i] = conv(tmp);
		x[m+1] = y[n+1] = '\0';
		for ( found = 0, k = 0; k < CARD && !(found|=kmp()); ++k ) 
			for ( i = 1; i <= n; ++i ) y[i] = next(y[i]);
		if ( found ) puts("S");
		else puts("N");
	}
	return 0;
}

