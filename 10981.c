/*
 * 10981. String Morphing
 * TOPIC: cyk, dp
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FG(buff) (ptr=fgets((buff),sizeof (buff),stdin))
#define N 0x80
#define A 3
#define L(k) ((k) & (~(k)+1ULL))
#define BIT(k) (1ULL<<(k))

int n,g[A][A] = {{1,1,0},{2,1,0},{0,2,2}};
char buff[0x400],*ptr,s[0x400],targ[0x20],who[1<<5];

int cyk( char *s, int n, char ch ) {
	int i,j,k,t;
	unsigned char z[N][N],u,v,a,b;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; z[i][j++] = 0 );
	for ( i = 0; i < n; ++i )
		z[i][i] |= BIT(s[i]-'a');
	for ( k = 2; k <= n; ++k )
		for ( i = 0; (j = i+k-1) < n; ++i )
			for ( t = i; t <= j-1; ++t )
				for ( u = z[i][t]; u && (a=who[L(u)]) >= 0; u &= ~L(u) )
					for ( v = z[t+1][j]; v && (b=who[L(v)]) >= 0; v &= ~L(v) )
						z[i][j] |= BIT(g[a][b]);
	return z[0][n-1]&BIT(ch-'a');
}

int f( char *s, int n ) {
	char *ns;
	int i,j,k;
	if ( n == 1 ) {
		if ( 0[s] == 0[targ] ) puts(s);
		return 0[s] == 0[targ];
	}
	assert( n >= 2 );
	ns = (char *)calloc(n,sizeof *ns);
	for ( i = 0; i < n-1; ++i ) {
		for ( k = 0, j = 0; j < i; ns[k++] = s[j++] );
		for ( ns[k++] = g[s[i]-'a'][s[i+1]-'a']+'a', j = i+2; j < n; ns[k++] = s[j++] );
		ns[k] = '\0';
		assert( k == n-1 );
		if ( cyk(ns,n-1,0[targ]) ) {
			printf("%s\n",s);
			assert( f(ns,n-1) );
			free(ns);
			return 1;
		}
	}
	free(ns);
	return 0;
}

int main() {
	int i,j,k,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("10981.in","r",stdin);
#endif
	for ( i = 0; i < 5; who[1<<i] = i, ++i );
	for ( sscanf(FG(buff),"%d",&ts); ts--; ) {
		for ( FG(s), n = 0; s[n] && s[n] != '\n'; ++n );
		s[n] = '\0', FG(targ);
		if ( !f(s,n) ) puts("None exist!");
		if ( ts ) putchar('\n');
	}
	return 0;
}

