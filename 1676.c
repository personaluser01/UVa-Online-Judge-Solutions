/*
 * 1676. GRE Words Revenge
 * TOPIC: Aho-Corasick, merging
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A 2
#define L(k) ((k) & ((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define LEN (1<<20)
#define Q (LEN)
#define MASK(k) (BIT(k)-1ULL)
#define THRESHOLD 4096
#define TST(u,k) (((u)>>(k))&1ULL)
#define MAXS (5000005)
#define MAXNODE 526288
#pragma comment( linker, "/STACK:1024000000,1024000000")
typedef long long i64;

char which[1<<21],buff[MAXS],str[MAXS],tmp[MAXS];
int cnt;

typedef struct cell {
	struct cell *son[A], *slink;
	unsigned char u;
	i64 val;
} cell;

cell pool_cache[MAXNODE],*ptr_cache,
	 pool_disc[MAXNODE],*ptr_disc;

cell *q[Q],**head,**tail,
	 *root_cache, *q0_cache,
	 *root_disc, *q0_disc;

int who( unsigned int u ) { return which[u]; }

cell *init( int t ) {
	cell *x = t?ptr_disc++:ptr_cache++;
	x->slink = NULL, x->u = 0, x->val = 0;
	if ( !t ) ++cnt;
	return x;
}

void push( cell *root, char *s, int t ) {
	cell *x;
	for ( x = root; *s; x=x->son[*s++-'0'] )
		if ( !(x->u&BIT(*s-'0')) )
			x->u|=BIT(*s-'0'), x->son[*s-'0']=init(t);
	x->u|=BIT(A);
}

int find( cell *root, char *s, int t ) {
	cell *x;
	for ( x = root; *s; x=x->son[*s++-'0'] )
		if ( !(x->u & BIT(*s-'0')) )
			x->u |= BIT(*s-'0'), x->son[*s-'0'] = init(t);
	return TST(x->u,A);
}

void myassert( int x ) {
	assert( x );
}

void build( cell *root, cell *q0 ) {
	cell *x,*y,*z;
	unsigned int u,ch;
	assert( root->slink == q0 );
	assert( q0->u == MASK(A) );
	for ( u = 0; u < A; ++u )
		assert( q0->son[u] == root );
	assert( !TST(q0->u,A) );
	assert( !TST(root->u,A) );
	root->slink = q0;
	for ( head=tail=q, *tail++=root; head<tail; )
		for (u=(((x=*head++)->u)&MASK(A)); u&&(ch=who(L(u)))>=0;\
			y->slink=z->son[ch],y->val=y->slink->val+(TST(y->u,A)?1:0),*tail++=y, u&=~L(u) ) {
			for ( y=x->son[ch], z=x->slink; z && !(z->u & BIT(ch)); z = z->slink ) ;
			assert( z );
		}
}

void decode( char *s, i64 L ) {
	int i,j,k,n = (int)strlen(s);
	if ( !n ) return ;
	L %= n;
	for (i = L, j = 0; i < n; i++, j++)
        tmp[j] = s[i];
    for (i = 0, j = n - L; i < L; i++, j++)
        tmp[j] = s[i];
    for (i = 0; i < n; i++)
        s[i] = tmp[i];
}

void init_ac( cell **r, cell **q, int t ) {
	int i;
	if ( t ) ptr_disc = pool_disc;
	else ptr_cache = pool_cache;
	if ( !t ) cnt = 0;
	*r = init(t), *q = init(t), (*r)->slink = (*q);
	for ( (*q)->u=MASK(A), i = 0; i < A; (*q)->son[i++] = (*r) ) ;
}

i64 query( cell *root, char *s ) {
	cell *x;
	i64 res = 0;
	assert( root->val == 0 );
	for ( x=root; *s; ) {
		assert( '0' <= *s && *s <= '1' );
		if ( !(x->u&BIT(*s-'0')) )
			for ( ;(x=x->slink) && !(x->u&BIT(*s-'0')); ) ;
		assert( x );
		x = x->son[*s++-'0'], res+=x->val;
	}
	return res;
}

void merge( cell *x, cell *y ) {
	int i;
	cell *u,*v;
	assert( x && y );
	for ( i = 0; i < A; ++i )
		if ( y->u & BIT(i) ) {
			v=y->son[i];
			if ( !(x->u&BIT(i)) )
				x->u |= BIT(i), x->son[i] = init(1);
			if ( TST(y->son[i]->u,A) ) x->son[i]->u |= BIT(A);
			merge(x->son[i],y->son[i]);
		}
}

int main() {
	int i,j,k,ts,qr,cache_built,disc_built,cs = 0;
	i64 L;
	for ( k = 0; k < 21; which[BIT(k)] = k, ++k ) ;
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case #%d:\n",++cs);
		init_ac(&root_cache,&q0_cache,0), init_ac(&root_disc,&q0_disc,1);
		for ( cache_built = disc_built = 0, L = 0, scanf("%d",&qr); qr--; ) {
			scanf("%s",str), decode(str+1,L);
			if ( 0[str] == '+' ) {
				if ( find(root_disc,str+1,1) || find(root_cache,str+1,0) ) continue ;
				push(root_cache,str+1,0), cache_built = 0;
				if ( cnt > THRESHOLD ) {
					merge(root_disc,root_cache), disc_built = 0;
					init_ac(&root_cache,&q0_cache,0), cache_built = 0;
				}
			}
			else {
				if ( !cache_built ) cache_built = 0, build(root_cache,q0_cache);
				if ( !disc_built ) disc_built = 0, build(root_disc,q0_disc);
				L = query(root_disc,str+1) + query(root_cache,str+1);
				printf("%lld\n",L);
			}
		}
	}
	return 0;
}

