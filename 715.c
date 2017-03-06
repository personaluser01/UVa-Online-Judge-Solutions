/*
 * 715. Substitution Cupher
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
#define N 32
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define is_in_alphabet(x) ('a'<=(x) && (x)<'a'+A)

	char cur[0x800],prev[0x800];
int A,K,g[N][N],indeg[N],outdeg[N],cnt[N],q[N],*head,*tail,c[N*N],
	is[N*N],yes,m,ic[N*N],sure[N*N],f[N*N],
	in_message[N*N],in_words[N*N];
char buff[1 << 21],*ptr;

int main() {
	int i,j,k,ts,missing[N];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts); ts-- && 2 == sscanf(FG,"%d %d",&A,&K) && ++yes;) {
		memset(g,0,sizeof(g));
		for ( i = 0; i < K; ++i ) {
			for ( FG, j = 0; *ptr && *ptr != '\n'; ++ptr )
				if ( is_in_alphabet(*ptr) )
					is[(cur[j++] = *ptr)-'a'] = yes;
			cur[j] = '\0';
			if ( i ) {
				for ( k = 0; cur[k] && prev[k] && cur[k] == prev[k]; ++k );
				if ( prev[k] && cur[k] )
					g[prev[k]-'a'][cur[k]-'a'] = 1;
			}
			strcpy(prev,cur);
		}
		FG;
		for ( k = 0, i = 0; buff[i] && buff[i] != '\n'; ++i )  {
			if ( is_in_alphabet(buff[i]) && ++k && is[buff[i]-'a'] != yes )
				goto NO;
		}
		buff[i] = '\0';
		if ( !k ) {
			puts(buff);
			continue ;
		}
		memset(indeg,0,sizeof(indeg));
		memset(outdeg,0,sizeof(outdeg));
		for ( k = 0; k < A; ++k )
			for ( i = 0; i < A; ++i )
				for ( j = 0; j < A; ++j )
					if ( g[i][k] && g[k][j] )
						g[i][j] = 1;
		for ( i = 0; i < A; ++i )
			for ( j = 0; j < A; ++j )
				if ( g[j][i] )
					++indeg[i], ++outdeg[j];
		for ( k = 0; k < A; ++k ) c[k] = -1;
		for ( i = 0; i < A; ++i )
			if ( c[k = indeg[i]] == -1 )
				c[k]=i, f[i]=k, sure[i]=1;
			else c[k] = -2;
		/*
		m = ((A-1)*A)/2;
		for ( i = 0; i < A; ++i ) m -= indeg[i];
		for ( i = 0; i < A; ++i )
			for ( j = i+1; j < A; ++j )
				if ( !g[i][j] && !g[j][i] )
					--m;
		if ( m ) goto NO;
		*/
		for ( i = 0; buff[i] && buff[i] != '\n'; ++i )
			if ( is_in_alphabet(buff[i]) ) {
				if ( c[indeg[buff[i]-'a']] >= 0 )
					buff[i] = f[buff[i]-'a']+'a';
				else goto NO;
			}
		puts(buff); continue ;
		/*
		for ( i = 0; i < A; ++i )
			for ( j = i+1; j < A; ++j )
				if ( is[i+'a'] == yes && is[j+'a'] == yes && g[i][j] == g[j][i] ) 
					goto NO;
		for ( i = 0; i < A; ++i )
			if ( is[i+'a'] == yes && g[i][i] )
				goto NO;
		for ( i = 0; i < A; ++i ) cnt[i] = indeg[i];
		for ( head = tail = q, i = 0; i < A; ++i )
			if ( !cnt[i] ) *tail++ = i;
		assert( tail-q == 1 );
		for( k = 0; head < tail;)
			for ( c[i = *head++] = k++, j = 0; j < A; ++j )
				if ( g[i][j] && !--cnt[j] )
					*tail++ = j;
		for ( i = 0; buff[i] && buff[i] != '\n'; ++i )
			if ( is_in_alphabet(buff[i]) )
				buff[i] = c[buff[i]-'a']+'a';
		buff[i] = '\0', puts(buff); continue ;
		*/
		NO: puts("Message cannot be decrypted.");
	}
	return 0;
}

