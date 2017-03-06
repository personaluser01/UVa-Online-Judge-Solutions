/*
 * 1621. Brackets Sequence
 * TOPIC: dp, brackets
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SH 7
#define N (1<<SH)
#define oo 0xfffffffful
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define FG(buff) (ptr=fgets(buff+1,sizeof buff,stdin))
#define is_matching(x,y) ( (x)=='('&&(y)==')' || (x)=='['&&(y)==']' )
#define enc(t,x) ((t)|((x)<<2))

char s[N],*ptr,matching[256];
unsigned int z[N][N],way[N][N];
int n;

void dump( int i, int j ) {
	int r = (way[i][j]&3), t = (way[i][j]>>2);
	if ( i > j ) return ;
	if ( i == j ) {
		switch ( s[i] ) {
				case '(': putchar(s[i]), putchar(')'); return ;
				case '[': putchar(s[i]), putchar(']'); return ;
				case ')': putchar('('), putchar(s[i]); return ;
				case ']': putchar('['), putchar(s[i]); return ;
				default: assert(0);
		}
		return ;
	}
	if ( r == 1 ) {
		assert( t >= i && t <= j-1 );
		dump(i,t), dump(t+1,j);
		return ;
	}
	if ( r == 0 ) {
		putchar(s[i]), dump(i+1,j-1), putchar(s[j]);
		return ;
	}
	if ( r == 2 ) {
		putchar(s[i]), dump(i+1,j), putchar(matching[s[i]]);
		return ;
	}
	putchar(matching[s[j]]), dump(i,j-1), putchar(s[j]);
}

int main() {
	int i,j,k,t,ts;
#ifndef ONLINE_JUDGE
	freopen("c.txt","r",stdin);
#endif
	matching[matching['('] = ')'] = '(', matching[matching['['] = ']'] = '[';
	for ( sscanf(FG(s),"%d",&ts); ts-- && FG(s); ) {
		for ( FG(s), n = 1; s[n] && s[n] != '\n'; ++n );
		for ( --n, memset(z,0xff,sizeof z), i = 0; i <= n; z[i][i]=1UL, ++i ) 
			for ( j = 0; j < i; z[i][j++]=0 );
		for ( k = 2; k <= n; ++k )
			for ( i = 1; (j=i+k-1) <= n; ++i ) {
				assert( z[i][j] == +oo );
				if ( is_matching(s[i],s[j]) && z[i+1][j-1] < +oo )
					z[i][j] = z[i+1][j-1], way[i][j] = enc(0,0);
				for ( t = i; t <= j-1; ++t )
					if ( z[i][t] < +oo && z[t+1][j] < +oo && z[i][j] > z[i][t]+z[t+1][j] )
						z[i][j] = z[i][t]+z[t+1][j], way[i][j] = enc(1,t);
				if ( (s[i]=='('||s[i]=='[') && z[i+1][j] < +oo && 1+z[i+1][j] < z[i][j] )
					z[i][j] = 1+z[i+1][j-1], way[i][j] = enc(2,i);
				if ( (s[j]==')'||s[j]==']') && z[i][j-1] < +oo && 1+z[i][j-1] < z[i][j] )
					z[i][j] = 1+z[i][j-1], way[i][j] = enc(3,j);
				assert( z[i][j] < +oo );
			}
		dump(1,n), putchar('\n');
		if ( ts ) putchar('\n');
	}
	return 0;
}

