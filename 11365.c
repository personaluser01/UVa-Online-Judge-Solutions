/*
 * 11365. Copying DNA
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
#define LEN 20
#define Q (1 << (LEN-1))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET(u,k) ((u)|=BIT(k))
#define CLR(u,k) ((u)&=~BIT(k))
#define TST(u,k) ((u)&BIT(k))
#define B(u,k,i) (((u)>>(2*(i)))&MASK(2*(k)))
#define ACCESS_SYMBOL(u,i) B(u,1,i)
#define L(u) ((u)&((~(u))+1UL))
typedef unsigned long long u64;

int ts,m,n;
char src[LEN+2],dst[LEN+2],who[1 << 21],
	 aid[4] = {'A','C','G','T'};
unsigned int q[Q],*head,*tail,*marker;
u64 source,target,cd[256],r_source,
	rev[LEN+2][LEN+2],R[LEN+2][LEN+2],
	block[LEN+2][LEN+2];
unsigned char seen[(Q>>3)+3],
			  patch[11][((1<<20)>>3)+8];
#define VISITED(u)  (TST(seen[(u)>>3],(u)&7))
#define SET_SEEN(u) (SET(seen[(u)>>3],(u)&7))

int show_string( u64 u, int len ) {
	int i;
	for ( i = 0; i < len; ++i )
		putchar(aid[ACCESS_SYMBOL(u,i)]);
	putchar('\n');
	return 1;
}

int matched( u64 slepok, int len ) {
	int i;
	for ( i = 0; i+len-1 < m; ++i )
		if ( slepok == B(source,len,i) )
			return 1;
	for ( i = 0; i+len-1 < m; ++i )
		if ( slepok == B(r_source,len,i) )
			return 1;
	return 0;
}

void ins( unsigned int v, unsigned int u ) {
	if ( !VISITED(v) )
		SET_SEEN(v), *tail++ = v;
}

void display( u64 u ) {
	int i,j,k,l;
	for ( ;u; u &= ~(MASK(l)<<i) ) {
		for ( l = 1, i = L(u), j = i<<1; u & j; j <<= 1, ++l );
		i = who[i], j = who[j];
		printf("[%d,%d] ",i,j-1);
	}
	puts("");
}

unsigned int copy_from_t( unsigned int u, int from, int to ) {
	int len = to-from+1,
		i,j,k,l,t;
	unsigned int v = u;
	assert( len >= 1 );
	assert( len <= n );
	for (;v; v &= ~(MASK(l)<<i) ) {
		for ( l = 1, i = L(v), j = i<<1; v & j; j <<= 1, ++l );
		i = who[i], j = who[j];
		for ( k = i; k+len-1 < j; ++k ) {
			if ( B(target,len,k) == B(target,len,from) )
				return u|(MASK(len)<<from);
		}
		for ( k = j-1; (k+1-len) >= i; --k ) {
			if ( R[len][k] == B(target,len,from) )
				return u|(MASK(len)<<from);
		}
	}
	return u;
}

void bfs() {
	unsigned int u,v,dist,c,b;
	u64 slepok,base;
	int i,j,k,l,t;

	memset(seen,0,sizeof(seen));
	head = tail = q, dist = 0;
	for ( SET_SEEN(0), *tail++ = 0, marker = tail; head < tail; ) {
		u=*head++;
		if ( head==marker+1 ) ++dist, marker = tail;
		if ( u == MASK(n) ) {
			printf("%u\n",dist);
			return ;
		}
		for ( base = (~u)&MASK(n); base; base &= ~(MASK(l)<<i) ) {
			for ( l = 1, i = L(base), j = (i<<1); base & j; j <<= 1, ++l );
			i = who[i], j = who[j];
			for ( k = i; k < j; ++k )
				for ( t = j-1; t >= k; --t ) {
					if ( VISITED(u|(MASK(t-k+1)<<k)) )
						continue ;
					slepok = B(target,t-k+1,k);
					if ( (t-k+1) <= 10 && TST(patch[t-k+1][slepok>>3],slepok&7)  )
						ins(u|(MASK(t-k+1)<<k),u);
					else if ( (t-k+1) <= m && matched(slepok,t-k+1) )
						ins(u|(MASK(t-k+1)<<k),u);
					else ins(copy_from_t(u,k,t),u);
				}
		}
	}
	puts("impossible");
}

int main() {
	int i,j,k,l,t,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	cd['A']=0,cd['C']=1,cd['G']=2,cd['T']=3;
	for ( i = 0; i < 21; ++i ) who[1 << i] = i;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%s %s",src,dst); bfs() ) {
		source = target = r_source = 0;
		m = strlen(src), n = strlen(dst);
		for ( i = 0; i < n; ++i ) dst[i] = toupper(dst[i]);
		for ( j = 0; j < m; ++j ) src[j] = toupper(src[j]);
		for ( i = 0; i < m; ++i )
			source |= (cd[src[i]] << (2*i));
		for ( i = 0, j = m-1; i < m; ++i, --j )
			r_source |= (cd[src[j]] << (2*i));
		for ( j = 0; j < n; ++j )
			target |= (cd[dst[j]] << (2*j));
		memset(patch,0,sizeof(patch));
		for ( k = 1; k <= m && k <= 10; ++k )
			for ( i = 0; (j = i+k-1) < m; ++i ) {
				block[k][i] = B(source,k,i), rev[k][i] = 0;
				for ( t = 0, l = j; l >= i; --l, ++t )
					rev[k][i] |= (ACCESS_SYMBOL(source,l)<<(2*t));
				assert( t == k );
				if ( k <= 10 ) {
					SET(patch[k][block[k][i]>>3],block[k][i]&7);
					SET(patch[k][rev[k][i]>>3],rev[k][i]&7);
				}
			}
		memset(R,0,sizeof(R));
		for ( k = 1; k <= n; ++k )
			for ( i = 0; (j = i+k-1) < n; ++i )
				for ( l = 0, t = j; t >= i; --t, ++l )
					R[k][j] |= (cd[dst[t]] << (2*l));
	}
	return 0;
}

