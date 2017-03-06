/*
 * 10625. GNU's Not Unix
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (126-33+1)
#define FG (fgets(buff,sizeof(buff),stdin))
typedef unsigned long long u64;

int ts,rules,times,present[256],yes,
	idx[256],n,qr;
char buff[0x400],*ptr,str[0x400],
	 vec[N],adj[256][256];
u64 M[N][N],alpha[N],ax[N][N],w;

void matrix_rep_sqr( int n, unsigned int m ) {
	int i,j,k;
	u64 A[N][N],s[N][N];
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			A[i][j] = M[i][j];
			if ( i == j )
				ax[i][j] = 1;
			else ax[i][j] = 0;
		}
	while ( m ) {
		if ( m & 1 ) {
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					for ( s[i][j] = 0, k = 0; k < n; ++k )
						s[i][j] += ax[i][k]*A[k][j];
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					ax[i][j] = s[i][j];
		}
		m >>= 1;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( s[i][j] = 0, k = 0; k < n; ++k )
					s[i][j] += A[i][k]*A[k][j];
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				A[i][j] = s[i][j];
	}
}

int main() {
	int i,j,k;
	char ch;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts); ts-- && ++yes; ) {
		sscanf(FG,"%d",&rules);
		for ( i = 0; i < rules; ++i )
			adj[i][0] = '\0';
		for ( j = 0; j < rules; ++j ) {
			FG;
			present[ch = 0[buff]] = yes;
			assert( 1[buff] == '-' );
			assert( 2[buff] == '>' );
			for ( ptr = adj[ch], i = 3; buff[i] && buff[i] != '\n' && 33 <= buff[i] && buff[i] <= 126; )
				present[*ptr++ = buff[i++]] = yes;
			*ptr = '\0';
		}
		for ( n = 0, ch = 33; ch <= 126; ++ch )
				if ( present[ch] == yes )
					vec[idx[ch] = n++] = ch;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				M[i][j] = 0;
		for ( j = 0; j < n; ++j ) {
			if ( adj[vec[j]][0] == '\0' ) {
				++M[j][j];
				continue ;
			}
			for ( ptr = adj[vec[j]]; *ptr; ++M[idx[*ptr++]][j] );
		}
		for ( sscanf(FG,"%d",&qr); qr--; ) {
			assert( 3 == sscanf(FG,"%s %1s %d",str,&ch,&times) );
			if ( present[ch] != yes ) {
				for ( w = 0, i = 0; str[i]; ++i )
					if ( str[i] == ch )
						++w;
				printf("%llu\n",w);
				continue ;
			}
			for ( i = 0; i < n; alpha[i++] = 0 );
			for ( ptr = str; *ptr; ++ptr )
				if ( present[*ptr] == yes )
					++alpha[idx[*ptr]];
			k = idx[ch];
			matrix_rep_sqr(n,times);
			for ( w = 0, j = 0; j < n; ++j )
				w += ax[k][j]*alpha[j];
			printf("%llu\n",w);
		}
	}
	return 0;
}

