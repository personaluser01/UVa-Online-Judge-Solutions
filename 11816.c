/*
 * 11816. HST
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
#define N 100100
typedef long long i64;

i64 Abs( i64 x ) { return x < 0 ? -x:x; }

int n,m;
i64 pstx[N],gstx[N],hstx[N];
i64 psty[N],gsty[N],hsty[N];
char name[32];

typedef struct cell {
	struct cell *sib,*son;
	char ch;
	int idx;
} cell;

cell *root;

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->ch = ch, x->idx = -1;
	x->son = x->sib = NULL;
	return x;
}

void push( cell *root, char *s, int idx ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y ) 
			y = init(*s), y->sib = x->son, x->son = y;
	}
	assert( x->idx == -1 );
	x->idx = idx;
}

int lookup( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; x = y, ++s ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y ) 
			return -1;
	}
	return x->idx;
}

/*
 * $d.c, p%
 */
i64 tax( i64 d, i64 c, i64 p ) {
	i64 t    = 100*d+c,
		quot = (p*t)/10000,
		rem  = (p*t)%10000;
	if ( rem >= 5000 )
		++quot;
	return quot;
}

void conv( char *s, i64 *d, i64 *c ) {
	int i,j,k;
	for ( i = 0; s[i] && s[i] != '.'; ++i );
	for ( j = 0; s[j] && s[j] != '%'; ++j );
	s[j] = '\0';
	if ( !s[i] ) { *d = atol(s), *c = 0; return ; }
	s[i] = '\0', *d = atol(s), *c = atol(s+i+1);
}

int main() {
	i64 i,j,k,l,t,ts,idx;
	i64 HST,GST,PST,diff;
	char tmp1,tmp2,tmp3,a[0x400],b[0x400],c[0x400];
	double amount;
#ifndef ONLINE_JUDGE
	/*freopen("in.txt","r",stdin);*/
#endif
	for ( scanf("%lld",&ts); ts--; ) {
		scanf("%d %d",&n,&m), root = init('\0');
		for ( i = 0; i < n; ++i ) {
			scanf("%s %s %s %s",name,a,b,c);
			conv(a,pstx+i,psty+i);
			conv(b,gstx+i,gsty+i);
			conv(c,hstx+i,hsty+i);
			for ( j = 0; name[j]; ++j ) name[j] = toupper(name[j]);
			push(root,name,i);
		}
		diff = 0;
		for ( i = 0; i < m; ++i ) {
			scanf("%s $%lf",name,&amount);
			k = 100*amount+.5;
			for ( j = 0; name[j]; ++j ) name[j] = toupper(name[j]);
			idx = lookup(root,name);
			assert( idx != -1 );
			PST = tax(k/100,k%100,pstx[idx]*100+psty[idx]);
			GST = tax(k/100,k%100,gstx[idx]*100+gsty[idx]);
			HST = tax(k/100,k%100,hstx[idx]*100+hsty[idx]);
			diff += HST-PST-GST;
		}
		if ( diff >= 0 ) 
			printf("%lld.%02lld\n",diff/100,diff%100);
		else 
			printf("-%lld.%02lld\n",Abs(diff)/100,Abs(diff)%100);
		/*printf("%.02lf\n",diff*.01);*/
	}
	return 0;
}

