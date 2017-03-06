/*
 * 12424. Calculating Yuan Fen
 * TOPIC: ad hoc, simulation, easy, trivial, pointers, fast I/O
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x10
#define MAXW (10000+32)

char s[N],out[1<<21],*ptr = out,newline = '\n';
int n,m,r[MAXW],*qtr,p[2][1<<21],*head[2];
char *emoji = ":(";

int f( int ST ) {
	int i,j,k,t,*str,*etr,ch;
	for ( qtr = p[t=0], i = 0; i < n; ++i ) {
		for ( k = ST+(s[i]-'A'), str = qtr; k; *qtr++ = r[k], k /= 10 );
		for ( etr = qtr-1; str < etr; ch = *str, *str = *etr, *etr = ch, ++str, --etr );
	}
	for ( m = qtr-p[t], t = 0; m >= 3; --m ) {
		for ( t ^= 1, head[t]=p[t], head[t^1]=p[t^1], i = m-1; i--; *head[t]++=r[(*head[t^1])+*(head[t^1]+1)], ++head[t^1] );
		assert( head[t]-p[t] == m-1 );
		if ( m-1 == 3 ) {
			if ( p[t][0] == 1 && p[t][1] == 0 && p[t][2] == 0 )
				return 1;
			else return 0 ;
		}
	}
	return 0;
}

void wr( int k ) {
	if ( k ) wr(k/10), *ptr++ = r[k]+'0';
}

int main() {
	int i,j,k,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < MAXW; r[i] = i%10, ++i );
	while ( fgets(s,sizeof s,stdin) ) {
		for ( n = 0; s[n] && s[n] != '\n'; ++n );
		for ( k = 1; k <= 10000 && !f(k); ++k );
		if ( k > 10000 ) 
			*ptr++ = ':', *ptr++ = '(', *ptr++ = '\n';
		else wr(k), *ptr++ = '\n';
	}
	fwrite(out,sizeof *ptr,ptr-out,stdout);
	fflush(stdout);
	return 0;
}

