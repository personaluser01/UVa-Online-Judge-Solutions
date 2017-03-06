/*
 * 1590. IP Networks
 * TOPIC: ad hoc, lcp, trie
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned long long u64;
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define N 0x400
enum { L, R };

int m,n;
u64 u[N],v[N],s,tmp,w,msk;
char buff[0x400],*ptr;

typedef struct cell {
	struct cell *son[2];
	int len;
} cell;

cell pool[1<<21],*qtr = pool;

void insert( cell *root, char *s ) {
	cell *x,*y;
	int i = 0;
	for ( x = root; x && *s; x = y, ++s, ++i ) 
		if ( !(y = x->son[*s-'0']) ) {
			x->son[*s-'0'] = y = qtr++, y->len = i+1;
			y->son[L] = y->son[R] = NULL;
		}
}

u64 enc( u64 a, u64 b, u64 c, u64 d ) {
	return d|(c<<8)|(b<<16)|(a<<24); 
}

int lcp( cell *root ) {
	cell *x;
	int i,k=0;
	for ( x = root; x && (!x->son[L] || !x->son[R]); ++k ) 
		if ( x->son[L] ) x = x->son[L];
		else x = x->son[R];
	return k;
}

u64 LCP( cell *root ) {
	cell *x;
	u64 res = 0;
	int i,k=0;
	for ( x = root; x && (!x->son[L] || !x->son[R]); ++k ) 
		if ( x->son[L] ) x = x->son[L];
		else x = x->son[R], res |= BIT(31-k);
	return res;
}



int main() {
	int i,j,k,l,t,good,bad,mid;
	u64 a,b;
	cell *root;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&m); ) {
		for ( i = 0; i < m; ++i ) {
			scanf("%d.%d.%d.%d",&j,&k,&l,&t);
			u[i] = enc(j,k,l,t);
		}
		for ( j = 1; j; )
			for ( i = j = 0; i < m-1; ++i )
				if ( u[i] > u[i+1] ) 
					++j, tmp = u[i], u[i] = u[i+1], u[i+1] = tmp;
		for ( k = i = 0; i < m; v[k++] = u[i], i = j )
			for ( j = i+1; j < m && u[i] == u[j]; ++j );
		for ( m=k, qtr=pool, root=qtr++, root->son[L]=root->son[R]=NULL,root->len=0, i=0; i<m; ++i ) {
			for ( ptr = buff, j = 31; j >= 0; --j )
				*ptr++ = ((v[i]>>j)&1ULL)+'0';
			*ptr = '\0', ptr = buff, insert(root,ptr);
		}
		n = lcp(root);
		w = LCP(root);
		for ( i = 3; i >= 0; --i )
			printf("%llu%c",(w>>(i*8))&0xffull,i==0?'\n':'.');
		for ( w = 0, k = 0, i = 31; i >= 0; --i, ++k )
			if ( k < n ) w |= BIT(i);
		for ( i = 3; i >= 0; --i )
			printf("%llu%c",(w>>(i*8))&0xff,i==0?'\n':'.');
	}
    return 0;
}

