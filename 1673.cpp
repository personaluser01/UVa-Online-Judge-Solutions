/*
 * 1673. str2int
 * TOPIC: dp on suffix automata
 * status: Accepted
 */
#include <set>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define M (10100)
#define N (1<<18)
#define A 10
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET(u,k) ((u) |= BIT(k))
#define TST(u,k) ((u) & BIT(k))
#define L(k) ((k)&((~(k))+1))
#define MOD (2012)
#define is_primary(x,y) ((x)->len+1==(y)->len)
using namespace std;

int which[1<<21];

typedef struct cell {
	unsigned int map;
	cell *slink,*son[A+1];
	int pos,len,dp,count,num,way;
	bool is_separator;
	cell() {};
} cell;
 
int m,n,str[N],idx[N],position[N],deg[N];
char tmp[N];
cell *ptr,pool[2*N],*root,*sink,*q[2*N],**head,**tail;

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->pos=pos,x->len=len,x->slink=NULL,x->is_separator=false,x->num=-1,x->count=x->dp=x->way=x->map=0;
	return x;
}

void add_son( cell *x, int ch, cell *y ) { 
	x->son[ch] = y, SET(x->map,ch);
}

cell *split( cell *x, int ch, int pos ) {
	unsigned int u;
	cell *z = init(x->len+1,pos), *y = x->son[ch];
	for(u=z->map=y->map;u;add_son(z,which[L(u)],y->son[which[L(u)]]),u&=~L(u));
	for(z->slink=y->slink,y->slink=z,add_son(x,ch,z),++z->count,x=x->slink;x&&TST(x->map,ch)&&x->son[ch]==y;add_son(x,ch,z),++z->count,x=x->slink);
	return z;
}

cell *update( int ch, int pos ) {
	cell *new_sink = init(sink->len+1,pos),*x,*y;
	new_sink->is_separator=(ch>=A);
	for(add_son(sink,ch,new_sink),++new_sink->count,x=sink->slink;x&&!TST(x->map,ch);add_son(x,ch,new_sink),++new_sink->count,x=x->slink);
	if ( !x ) {
		new_sink->slink = root;
		return new_sink;
	}
	if ( is_primary(x,x->son[ch]) )
		new_sink->slink = x->son[ch];
	else new_sink->slink = split(x,ch,pos);
	return new_sink;
}

void process( cell *x ) {
	int i,j,k,t,l,slen;
	if ( !x || x->num >= 0 )
		return ;
	slen = x->slink->len, i = (x->pos-x->len+1), j = (x->pos-slen);
	assert( x->len-slen == j-i+1 );
	process(x->slink);
	if ( x->is_separator ) {
		x->num = x->dp = 0;
		return ;
	}
	if ( idx[i] != idx[x->pos] ) {
		assert( idx[i] < idx[x->pos] );
		i = position[idx[x->pos]-1]+1;
	}
	for ( x->num = x->slink->num, l = 0, k = j, t = slen; k >= i; ++t, --k, ++l ) {
		/*if ( !(0 <= str[k] && str[k] < A) )
			printf("[%d,%d,%d] This %d\n",i,j,k,str[k]);*/
		assert( 0 <= str[k] && str[k] < A );
		x->num += deg[t]*str[k], x->num %= MOD;
	}
	for ( ;i <= j && str[i] == 0; ++i ) ;
	if ( i > j ) {
		x->dp = 0;
		return ;
	}
	assert( i <= j && idx[i] == idx[x->pos] && idx[j] == idx[i] );
	assert( idx[j] == idx[x->pos] );
	assert( x->pos-i+1 > slen );

	/*
	printf("Tail: ");
	for ( k = i; k <= j; ++k )
		putchar(str[k]+'0');
	printf(", Suffix link: ");
	for ( k = j+1; k <= x->pos; ++k )
		putchar(str[k]+'0');
	puts("");
	*/

	int cur = 0;
	for ( x->dp = 0, l = 0, k = j, t = slen; k >= i; ++t, --k, ++l ) {
		/*if ( !(0 <= str[k] && str[k] < A) )
			printf("[%d,%d,%d] This %d\n",i,j,k,str[k]);*/
		assert( 0 <= str[k] && str[k] < A );
		if ( str[k] == 0 ) { --l; continue ; }
		//x->num += deg[t]*str[k], x->num %= MOD
		//x->dp += (k-i+1)*deg[j-k+slen]*str[k], x->dp %= MOD;
		cur += deg[j-k+slen]*str[k];
		x->dp += cur, cur %= MOD, x->dp %= MOD;
	}
	x->dp += l*x->slink->num, x->dp %= MOD;
}

set<string> s;
int cn[N];
cell *order[N];

int main() {
	int i,j,k,l,t,digit,ans;
	unsigned int u;
	cell *x,*y;
	for ( deg[0] = 1, i = 1; i < N; ++i )
		deg[i] = ((deg[i-1]*10)%MOD);
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	for (;1==scanf("%d",&m);) {
		for ( s.clear(), n = 0, i = 0; i < m; str[n++] = A, ++i ) {
			for ( scanf("%s",tmp), j = 0; tmp[j]; str[n++] = tmp[j++]-'0' ) ;
			/*
			for ( l = 0; l < j; ++l ) {
				for ( k = l; k < j; ++k ) {
					int lim = l;
					for ( ;lim <= k && tmp[lim] == '0'; ++lim ) ;
					string tt = "";
					for ( t = lim; t <= k; ++t )
						tt += tmp[t];
					if ( tt != "" ) s.insert(tt);
				}
			}
			*/
		}
		/*
		ans = 0;
		for ( set<string> :: iterator it = s.begin(); it != s.end(); ++it ) {
			ans += (atol((*it).c_str())%MOD), ans %= MOD;
			printf("This %s\n",(*it).c_str());
		}
		printf("Brute Force: %d\n",ans);
		*/
		for ( j = 0, i = 0; i < n; ++i )
			if ( str[i] >= A ) 
				position[idx[i] = j++] = i;
			else idx[i] = j;
		assert( j == m ) ;
		for(ptr=pool,root=sink=init(0,-1),i=0;i<n;sink=update(str[i],i),++i);
		/*
		for ( root->num=root->dp=0, i = 1; i < ptr-pool; process(&pool[i++]) ) ;
		for ( ans = 0, i = 0; i < ptr-pool; ans += pool[i++].dp, ans %= MOD ) ;
		printf("%d\n",ans);
		*/
		memset(cn,0,sizeof cn);
		for ( i = 0; i < ptr-pool; ++i )
			++cn[pool[i].len];
		for ( i = 1; i <= n; ++i )
			cn[i] += cn[i-1];
		for ( i = 0; i < ptr-pool; ++i )
			order[--cn[pool[i].len]] = pool+i;
		for ( ans = 0, root->way = 1, i = 0; i < ptr-pool; ++i ) {
			for ( ans += order[i]->dp, ans %= MOD, u = order[i]->map, u &= ~BIT(A); u; u &= ~L(u) ) {
				j = which[L(u)];
				if ( i == 0 && j == 0 ) continue ;
				cell *zz = order[i]->son[j];
				zz->way+=order[i]->way,zz->way%=MOD,zz->dp+=(order[i]->dp*10+order[i]->way*j),zz->dp%=MOD;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

