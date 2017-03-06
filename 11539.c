/*
 * 11539. Another Word Game
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
#define N 10080
#define L 0x80
typedef long long i64;
#define M 4
#define MOD 20011

i64 p[M] = {1117, 1789, 3389, 4999};

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	(!y)?(*a=1,*b=0,*d=x):(ext_euclid(y,x%y,b,a,d),*b-=(*a)*(x/y));
}

i64 modinv( i64 p, i64 q ) {
	i64 a,b,d;
	ext_euclid(p,q,&a,&b,&d);
	for(;a<0;a+=q);
	a %= q;
	assert( (a*p) % q == 1 );
	return a%q;
}

int n,penalty,weight[N],len[N],m,
	last[M][MOD+1],next[M][N],idx[M][N];
char word[N][L],s[1 << 16],buff[1 << 16];
i64 hash[M][N],h[M][10100],deg[M][10100],ideg[M][10100],inv[M],z[10100];

int first_char( char *ptr ) {
	while ( *ptr && *ptr != '\n' && isspace(*ptr) ) ++ptr;
	return *ptr;
}

i64 subs( int i, int j, int k ) {
	i64 w;
	if ( i == 0 ) return h[k][j];
	for ( w = (h[k][j]-h[k][i-1]); w < 0; w += MOD );
	return (w*ideg[k][i]) % MOD;
}

int equal( int k, int i, int j ) {
	int l,t;
	if ( i < 0 ) return 0;
	assert( (j-i+1) == len[k] );
	for ( l = 0; l < M; ++l )
		if ( subs(i,j,l) != hash[l][k] ) 
			return 0;
	return strncmp(word[k],s+i,len[k]) == 0;
}

int main() {
	int i,j,k,l,t,ts,cs = 0;
	i64 w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( k = 0; k < M; ++k )
		for ( inv[k] = modinv(p[k],MOD), i = 1, deg[k][0] = ideg[k][0] = 1LL; i < 10100; ++i ) {
			deg[k][i]  =  deg[k][i-1]*p[k], deg[k][i] %= MOD;
			ideg[k][i] = ideg[k][i-1]*inv[k], ideg[k][i] %= MOD;
		}
	for ( scanf("%d\n",&ts); ts-- && printf("Case %d: ",++cs) && 2 == scanf("%d %d\n",&n,&penalty); ) {
		for ( i = 0; i <= MOD; ++i )
			for ( k = 0; k < M; ++k )
				last[k][i] = -1;
		for ( i = 0; i < n; ++i ) {
			/*fgets(buff,sizeof(buff),stdin);*/
			scanf("%s %d",word[i],&weight[i]);
			/*if ( isdigit(first_char(buff)) )
				sscanf(buff,"%d",&weight[i]), len[i] = 0;*/
			sscanf(buff,"%s %d",word[i],&weight[i]), len[i] = strlen(word[i]);
			for ( k = 0; k < M; ++k ) {
				for ( hash[k][i] = 0, j = 0; j < len[i]; ++j ) {
					w = word[i][j]-'a';
					hash[k][i] = (hash[k][i]+deg[k][j]*w)%MOD;
				}
				hash[k][i] %= MOD;
				next[k][i] = last[k][hash[k][i]], last[k][hash[k][i]] = i;
			}
		}
		/*
		fgets(s,sizeof(s),stdin);
		for ( m = 0; s[m] && s[m] != '\n'; ++m );
		s[m] = '\0';
		*/
		scanf("%s",s); m = strlen(s);
		if ( !m ) {
			puts("0");
			continue ;
		}
		for ( k = 0; k < M; ++k ) {
			for ( h[k][0] = s[0]-'a', j = 1; j < m; ++j ) {
				w = s[j]-'a';
				h[k][j] = (h[k][j-1]+w*deg[k][j]) % MOD;
			}
		}
		z[0] = -penalty;
		for ( i = 0; i < n; ++i )
			if ( len[i] == 1 && equal(i,0,0) ) 
				if ( z[0] < weight[i] )
					z[0] = weight[i];
		for ( i = 1; i < m; ++i ) {
			for ( z[i] = z[i-1]-penalty, l = 1; l <= 100 && i-l+1 >= 0; ++l ) {
				t = 2;
				w = subs(i-l+1,i,t);
				assert( 0 <= w && w <= MOD );
				for ( k = last[t][w]; k >= 0; k = next[t][k] )
					if ( len[k] == l && equal(k,i-l+1,i) ) {
						if ( i-l < 0 ) {
							if ( z[i] < weight[k] )
								z[i] = weight[k];
							continue ;
						}
						if ( z[i] < z[i-l]+weight[k] )
							z[i] = z[i-l]+weight[k];
					}
			}
		}
		printf("%lld\n",z[m-1]);
	}
	return 0;
}

