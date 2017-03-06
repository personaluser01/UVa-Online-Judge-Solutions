/*
 * 11402. Ahoy, Pirates!
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#define N (1 << 21)
#define M (1 << 11)
#include <float.h>
enum{Barbary,Bucc,Inv,NONE};

int min( int x, int y ) { return x < y ? x : y; }
int max( int x, int y ) { return x > y ? x : y; }

int ts,cs,m,n,B,block[M];
short s[N];
char last[M];

void Execute( int idx ) {
	int k;
	if (last[idx]==NONE)
		return ;
	if ( last[idx] == Inv ) {
		for ( k = idx*B; k < (idx+1)*B; s[k++] ^= 1 );
		last[idx]=NONE;
		return ;
	}
	for ( k = idx*B; k < (idx+1)*B; s[k++] = last[idx] );
	last[idx]=NONE;
}

void mutate( int i, int j, int t ) {
	int k,bi = i/B,
		  bj = j/B;
	for ( k = bi+1; k <= bj-1; ++k )
		block[k] = t*B, last[k] = t;
	Execute(bi), Execute(bj);
	if ( bi == bj ) {
		for ( k = bi*B+(i%B); k <= bj*B+(j%B); s[k++] = t );
		for ( block[bi]=0, k = bi*B; k < (bi+1)*B; block[bi]+=s[k++] );
		return ;
	}
	for ( k = bi*B+(i%B); k < (bi+1)*B; s[k++] = t );
	for ( k = bj*B; k <= bj*B+(j%B); s[k++] = t );
	for ( block[bi]=0, k = bi*B; k < (bi+1)*B; block[bi]+=s[k++] );
	for ( block[bj]=0, k = bj*B; k < (bj+1)*B; block[bj]+=s[k++] );
}

void inverse( int i, int j ) {
	int k,bi = i/B,bj = j/B;
	for ( k = bi+1; k <= bj-1; ++k ) {
		block[k] = B-block[k];
		if ( last[k] == NONE ) {
			last[k] = Inv;
			continue ;
		}
		if ( last[k] == Inv ) {
			last[k] = NONE;
			continue ;
		}
		last[k] ^= 1;
	}
	Execute(bi), Execute(bj);
	if ( bi == bj ) {
		for ( k = bi*B+(i%B); k <= bj*B+(j%B); s[k++] ^= 1 );
		for ( block[bi]=0, k = bi*B; k < (bi+1)*B; block[bi]+=s[k++] );
		return ;
	}
	for ( k = bi*B+(i%B); k < (bi+1)*B; s[k++] ^= 1 );
	for ( k = bj*B; k <= bj*B+(j%B); s[k++] ^= 1 );
	for ( block[bi]=0, k = bi*B; k < (bi+1)*B; block[bi]+=s[k++] );
	for ( block[bj]=0, k = bj*B; k < (bj+1)*B; block[bj]+=s[k++] );
}

int query( int i, int j ) {
	int k,ax = 0,
		bi = i/B,
		bj = j/B;
	for ( k = bi+1; k <= bj-1; ax += block[k++] );
	Execute(bi), Execute(bj);
	if ( bi == bj ) {
		for ( k = bi*B+(i%B); k <= bj*B+(j%B);ax += s[k++] );
		return ax;
	}
	for ( k = bi*B+(i%B); k < (bi+1)*B; ax += s[k++] );
	for ( k = bj*B; k <= bj*B+(j%B); ax += s[k++] );
	return ax;
}

int main() {
	int i,j,k,l,t,qr,nro;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(scanf("%d",&ts);ts-- && 1 == scanf("%d",&m);) {
		for ( n = 0, i = 0; i < m; ++i ) 
			for(scanf("%d %s",&k,tmp);k--;)
				for(j=0;tmp[j];s[n++]=tmp[j++]-'0');
		printf("Case %d:\n",++cs);
		for ( B = sqrt(n); n%B; s[n++] = 0 );
		for ( k = 0; k < n/B; ++k ) 
			for ( last[k]=NONE, block[k] = 0, i = B*k; i < (k+1)*B; block[k] += s[i++] );
		for ( nro = 0, scanf("%d",&qr); qr--; ) {
			scanf("%s %d %d",tmp,&i,&j);
			switch ( 0[tmp] ) {
				case 'F': mutate(i,j,1);
						  break ;
				case 'E': mutate(i,j,0);
						  break ;
				case 'I': inverse(i,j); 
						  break ;
				case 'S': printf("Q%d: %d\n",++nro,query(i,j));
						  break ;
				default:  assert(0);
						  break ;
			}
		}
	}
	return 0;
}

