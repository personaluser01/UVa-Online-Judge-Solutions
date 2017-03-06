/*
 * 12547. RNA Secondary Structure
 * TOPIC: dp
 * status: in progress
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L (1<<21)
#define N (1<<12)
#define MAXK 21
#define oo 0xfffffffful

char s[L],id[256];
int n,c[N],freq[N],K;
unsigned int z[N][N][MAXK];

unsigned int calc_z( int i, int j, int k ) {
	int l,t;

	if ( z[i][j][k] < +oo )
		return z[i][j][k];

	assert( i <= j );

	if ( i >= j ) 
		return z[i][j][k] = 0;

	z[i][j][k] = calc_z(i+1,j-1,k);

	if ( (c[i]^1) == c[j] ) {
		if ( c[i] >= 2 ) {
			if ( k >= 1 && calc_z(i+1,j-1,k-1) < +oo )
				z[i][j][k] = 1+calc_z(i+1,j-1,k-1);
		}
		else 
			z[i][j][k] = 1+calc_z(i+1,j-1,k);
	}

	for ( t = i+1; t <= j-1; ++t )
		for ( l = 0; l <= k; ++l )
			if ( calc_z(i,t,l) < +oo && calc_z(t+1,j,k-l) < +oo )
				if ( z[i][j][k] == +oo || calc_z(i,t,l)+calc_z(t+1,j,k-l) > z[i][j][k] )
					z[i][j][k] = calc_z(i,t,l)+calc_z(t+1,j,k-l);
	return z[i][j][k];
}

int main() {
	int i,j,k,ts,cs = 0,ch;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	id['A'] = 0, id['U'] = 1, id['C'] = 2, id['G'] = 3;
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d: ",++cs);
		for ( n = 0, scanf("%s",s), i = 0; s[i]; a[n]=ch, freq[n++]=k, i = j ) 
			for ( k=0,ch=id[s[i]],j=i+1; s[j]&&'0'<=s[j]&&s[j]<='9'; k=10*k+(s[j++]-'0') );
		scanf("%d",&K);
		for ( i = 0; i <= n; ++i )
			for ( j = i; j <= n; ++j )
				for ( k = 0; k <= K; ++k )
					z[i][j][k] = +oo;
		printf("%u\n",calc_z(0,n-1,K));
	}
	return 0;
}

