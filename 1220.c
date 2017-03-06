/*
 * 1220. Party at Hali-Bula
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
#define N 0x100
#define M (N*N)
#define oo 0xfffffffful

int n,V,E,last[N],next[M],to[M],is_unique[2][N],yes;

unsigned int max( unsigned int x, unsigned int y ) {
	return x < y ? y:x;
}

typedef struct cell {
	struct cell *son,*sib;
	char ch;
	int idx;
}cell;

cell *root;

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->son = x->sib = NULL, x->ch = ch, x->idx = -1;
	return x;
}

int push( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; ++s, x = y ) {
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			y = init(*s), y->sib = x->son, x->son = y;
	}
	return x->idx=(x->idx >= 0?x->idx:V++);
}

void add_arcs( int x, int y ) {
	int i = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
}

unsigned int z[2][N];

unsigned int calc_z( int t, int x ) {
	unsigned int w;
	int i;

	if ( z[t][x] < +oo )
		return z[t][x];
	is_unique[t][x] = yes;
	if ( !t ) {
		for ( z[t][x] = 0, i = last[x]; i >= 0; i = next[i] ) {
			z[t][x] += (w = max(calc_z(0,to[i]),calc_z(1,to[i])));
			if ( w == z[0][to[i]] && !is_unique[0][to[i]] )
				is_unique[t][x] = 0;
			if ( w == z[1][to[i]] && !is_unique[1][to[i]] )
				is_unique[t][x] = 0;
			if ( z[1][to[i]] == z[0][to[i]] )
				is_unique[t][x] = 0;
		}
	}
	else {
		for ( z[t][x] = 1, i = last[x]; i >= 0; i = next[i] ) {
			z[t][x] += calc_z(0,to[i]);
			if ( !is_unique[0][to[i]] )
				is_unique[t][x] = 0;
		}
	}
	return z[t][x];
}

int main() {
	int i,j,k,x,y;
	char tmp[0x400],a[0x400],b[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 && ++yes ) {
		for ( i = 0; i < n; ++i ) last[i] = -1;
		V = 0, root = init('\0'), scanf("%s",tmp), push(root,tmp);
		for ( E = 0, i = 0; i < n-1; ++i ) {
			scanf("%s %s",a,b);
			y = push(root,a), x = push(root,b);
			add_arcs(x,y);
		}
		memset(z,0xfful,sizeof(z));
		if ( calc_z(0,0) == calc_z(1,0) )
			printf("%u No\n",z[0][0]);
		else if ( z[0][0] > z[1][0] ) {
			printf("%u %s\n",z[0][0],is_unique[0][0]==yes?"Yes":"No");
		}
		else {
			printf("%u %s\n",z[1][0],is_unique[1][0]==yes?"Yes":"No");
		}
	}
	return 0;
}

