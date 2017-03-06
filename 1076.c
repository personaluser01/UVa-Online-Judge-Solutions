/*
 * 1076. Password Suspects
 * TOPIC: aho-corasick automaton
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define Q (1<<7)
#define MAXS (1<<21)
#define A 26
#define oo (BIT(62))
#define enc(x,k,v) ((k)|((v)<<5)|(((x)-c)<<15))
#define NDEBUG
typedef long long i64;

typedef struct cell {
	struct cell *son[A],*failure_link,*p;
	unsigned int mask;
	char ch;
	i64 z[26][BIT(10)];
} cell;

int Len,Ks,m,seen[MAXS],yes,r[MAXS];
char wrd[32][32],w[32][32],*ptr,o[32];
cell c[Q],*pool = c,*root,*sink,*q[Q],**head,**tail;
unsigned int que[2][BIT(21)],*H[2],*T[2];
i64 ans;

cell *init_cell( char ch, cell *p ) {
	cell *x = pool++;
	int i,u;
	for ( x->mask = 0, x->failure_link = NULL, x->ch = ch, x->p = p, i = 0; i < A; x->son[i++] = NULL );
	for ( i = 0; i <= Len; ++i )
		for ( u = 0; u < BIT(Ks); ++u )
			x->z[i][u] = 0;
	return x;
}

void push( cell *root, char *s, int idx ) {
	cell *x;
	int i;
	for ( x = root; *s; x = x->son[*s-'a'], ++s ) 
		if ( !x->son[*s-'a'] ) 
			x->son[*s-'a'] = init_cell(*s,x);
	x->mask |= BIT(idx);
}

int reachable( cell *x, int k, unsigned int v ) {
	int i;
	cell *y;
	if ( k == Len ) 
		return r[enc(x,k,v)] = (MASK(Ks)==v);
	if ( seen[enc(x,k,v)] == yes )
		return r[enc(x,k,v)];
	seen[enc(x,k,v)] = yes, r[enc(x,k,v)] = 0;
	for ( i = 0; i < A; ++i ) 
		if ( y=x->son[i] ) {
			r[enc(x,k,v)] |= reachable(y,k+1,v|y->mask);
		}
		else {
			for ( y = x->failure_link; y && !y->son[i]; y = y->failure_link );
			r[enc(x,k,v)] |= reachable(y->son[i],k+1,y->son[i]->mask|v);
		}
	return r[enc(x,k,v)];
}

void dfs( cell *x, int k, unsigned int v ) {
	int i;
	cell *y;
	assert( x && k <= Len );
	if ( !r[enc(x,k,v)] ) return ;
	if ( k == Len ) {
		if ( v == MASK(Ks) ) {
			assert( m < ans );
			*ptr = '\0', strcpy(w[m++],o);
		}
		return ;
	}
	assert( k < Len );
	for ( i = 0; i < A; ++i )
		if ( y = x->son[i] ) {
			*ptr++ = i+'a', dfs(y,k+1,y->mask|v), --ptr;
		}
		else {
			for ( y = x->failure_link; y && !y->son[i]; y = y->failure_link );
			assert( y );
			*ptr++ = i+'a', y = y->son[i], dfs(y,k+1,y->mask|v), --ptr;
		}
}

int main() {
	int i,j,k,cs = 0,t,l;
	cell *x,*y;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&Len,&Ks) && (Len||Ks) && printf("Case %d: ",++cs); ) {
		pool = c, sink = init_cell('\0',NULL), root = init_cell('$',sink);
		for ( root->mask = 0, i = 0; i < A; root->son[i++] = NULL );
		for ( sink->mask = 0, i = 0; i < A; sink->son[i++] = root );
		sink->failure_link = sink, root->failure_link = NULL;
		for ( i = 0; i < Ks; scanf("%s",wrd[i]), push(root,wrd[i],i), ++i );
		for ( root->failure_link = sink, head = tail = q, i = 0; i < A; ++i )
			if ( root->son[i] ) *tail++ = root->son[i];
		for ( ;head < tail; x->failure_link = y->son[x->ch-'a'] ) {
			for ( x = *head++, i = 0; i < A; ++i )
				if ( x->son[i] ) *tail++ = x->son[i];
			assert( x->p );
			for ( y = x->p->failure_link; y && !y->son[x->ch-'a']; y = y->failure_link );
			assert( y );
		}
		for ( head = tail = q, *tail++ = root; head < tail; x->mask |= x->failure_link->mask ) 
			for ( x = *head++, i = 0; i < A; ++i )
				if ( x->son[i] ) *tail++ = x->son[i];
		for(t=0,H[t]=T[t]=que[t],x=root,x->z[0][0]=1LL,*T[t]++=0|0|((x-c)<<15),l=0;l<=Len-1;++l) 
			for ( t ^= 1, H[t] = T[t] = que[t]; H[t^1] < T[t^1]; ) 
				for ( u=*H[t^1]++, x=c+(u>>15), k=(u&31), v=((u>>5)&1023), i = 0; i < A; ++i )
					if ( y = x->son[i] ) {
						if ( (y->z[l+1][y->mask|v] += x->z[l][v]) == x->z[l][v] )
							*T[t]++ = (l+1)|((y->mask|v)<<5)|((y-c)<<15);
					}
					else {
						for ( y = x->failure_link; y && !y->son[i]; y = y->failure_link );
						assert( y );
						y = y->son[i];
						if ( (y->z[l+1][y->mask|v] += x->z[l][v]) == x->z[l][v] )
							*T[t]++ = (l+1)|((y->mask|v)<<5)|((y-c)<<15);
					}
		for ( ans = 0, i = 0; i < pool-c; ++i )
			ans += c[i].z[Len][MASK(Ks)];
		printf("%lld suspects\n",ans);
		if ( ans > 42 ) continue ;
		if ( !ans ) continue ;
		++yes, reachable(root,0,0);
		m = 0, ptr = o, dfs(root,0,0);
		assert( m == ans );
		for ( j = 1; j; )
			for ( i = j = 0; i < m-1; ++i )
				if ( strcmp(w[i],w[i+1]) > 0 )
					++j, strcpy(o,w[i]), strcpy(w[i],w[i+1]), strcpy(w[i+1],o);
		for ( i = 0; i < m; printf("%s\n",w[i++]) );
	}
	return 0;
}

