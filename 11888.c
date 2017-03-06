/*
 * 11888.
 * TOPIC: kmp, pattern matching
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FG(buff) (ptr = fgets(buff,sizeof buff,stdin))
#define N (1<<21)

char buff[N],s[2][N],*ptr,c[N],t[N];
int m,n,pi[2][N],q[N],r[N];

void mp( char *s, int n, int *pi ) {
	int i,k = 0;
	for ( pi[0]=-1,pi[1]=0,i = 2; i <= n; pi[i++] = ++k )
		for ( k = pi[i-1]; k >= 0 && s[k+1] != s[i]; k = pi[k] );
}

int pal( char *s, int m ) {
	int i,j;
	for ( i = 1, j = m; i <= j; ++i, --j )
		if ( s[i] != s[j] )
			return 0;
	return 1;
}

int is_palin( char *a, char *b ) {
	int k = 0;
	while ( a <= b ) {
		if ( *a != *b )
			return 0;
		++a, --b, ++k;
	}
	return k;
}

int main() {
	int i,j,k,ts,alin;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( sscanf(FG(buff),"%d",&ts); ts--; ) {
		for ( FG(buff+1), n = 0; buff[n+1] && buff[n+1] != '\n'; ++n );
		if ( !(m = n) ) {
			puts("alindrome");
			continue ;
		}
		if ( m == 1 ) {
			puts("palindrome");
			continue ;
		}
		for ( i = 1; i <= m; s[0][i] = buff[i], ++i );
		for ( s[1][j=m+1] = s[0][m+1] = '#', i = m; i >= 1; s[0][++j] = buff[i--] );
		for ( n <<= 1, ++n, j = 1, i = m; i >= 1; s[1][j++] = buff[i--] );
		for ( i = 1; i <= m; s[1][++j] = buff[i++] );
		s[0][n+1] = s[1][n+1] = '\0';
		for ( i = 0; i <= 1; ++i ) mp(s[i],n,pi[i]);
		for ( mp(buff,m,q), i = 1; i <= m; ++i ) t[m-i+1] = buff[i];
		t[j = m+1] = '#';
		for ( i = 1; i <= m; ++i )
			t[++j] = buff[i];
		for ( i = 1; i <= m; ++i )
			t[++j] = buff[i];
		assert( j == m+m+m+1 );
		t[j+1] = '\0';
		/*puts(t+1);*/
		mp(t,m+m+m+1,r);
		for ( alin = 0, i = m+3; i+m-1 < m+m+m+1; ++i )
			if ( r[i+m-1] == m ) {
				if ( is_palin(t+m+2,t+i-1) && is_palin(t+i+m,t+m+m+m+1) ) {
					alin = 1;
					break ;
				}
			}
		if ( alin ) {
			puts("alindrome");
			continue ;
		}
		if ( pi[0][n] == m ) {
			puts("palindrome");
			continue ;
		}
		puts("simple");
		/*
		puts(s[0]+1);
		puts(s[1]+1);
		*/
	}
    return 0;
}


