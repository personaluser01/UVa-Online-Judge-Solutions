/*
 * 1229. Sub-dictionary
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x80
#define L 0x30
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define MAXV 0x400
#define M (1 << 19)
#define oo 0xfffffffful
enum{D,T};

int n,V,last[2][MAXV],to[2][M],next[2][M],E[2],st[MAXV],*top,seen[MAXV],yes,
	c[MAXV],scc,g[MAXV][MAXV],indeed,card[MAXV],z[MAXV];
char buff[1 << 21],*ptr;

void add_arcs( int x, int y ) {
	int i = E[D]++,
		j = E[T]++;
	assert( x != y );
	to[D][i] = y, next[D][i] = last[D][x], last[D][x] = i;
	to[T][j] = x, next[T][j] = last[T][y], last[T][y] = j;
}

typedef struct cell {
	struct cell *sib,*son;
	char ch;
	int idx;
} cell;

cell *init( char ch ) {
	cell *x = (cell *)malloc(sizeof *x);
	x->ch = ch, x->idx = -1;
	x->son = x->sib = NULL;
	return x;
}

int push( cell *root, char *s ) {
	cell *x,*y;
	for ( x = root; *s; ++s, x = y ) {
		/*assert( isalpha(*s) );*/
		for ( y = x->son; y && y->ch != *s; y = y->sib );
		if ( !y )
			y = init(*s), y->sib = x->son, x->son = y;
	}
	if ( x->idx == -1 )
		x->idx = V++;
	return x->idx;
}

void dfs( int x, int t ) {
	int i,y;
	for ( seen[x] = yes, i = last[t][x]; i >= 0; i = next[t][i] )
		if ( seen[y = to[t][i]] != yes )
			dfs(y,t);
	if ( t == D ) *++top = x;
	else c[x] = scc;
}

char word[MAXV][L];
int m;

void traverse( cell *x, int k ) {
	if ( !x ) return ;
	*ptr++ = x->ch;
	if ( x->idx >= 0 && c[x->idx] == k ) {
		*ptr = '\0';
		strcpy(word[m++],buff+1);
	}
	traverse(x->son,k), --ptr;
	traverse(x->sib,k);
}

int cmp( const void *x, const void *y ) {
	char *s = (char *)x,
		 *t = (char *)y;
	return strcmp(s,t);
}

void cleanup( cell *x ) {
	if ( !x ) return ;
	cleanup(x->son), cleanup(x->sib), free(x);
}

int main() {
	int i,j,k,l,t,x,y,w;
	char s[0x400];
	cell *root;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( FG && 1 == sscanf(buff,"%d",&n) && n > 0 ) {
		root = init('\0'), E[D] = E[T] = 0, V = 0;
		memset(last,-1,sizeof(last)),++indeed;
		for ( i = 0; i < n; ++i ) {
			FG, k = 0, sscanf(buff+k,"%s%n",s,&j), k += j;
			assert( strlen(s) <= 25 );
			for ( l = 0, x = push(root,s); 1 == sscanf(buff+k,"%s%n",s,&j); k += j, ++l ) {
				assert( strlen(s) <= 25 );
				y = push(root,s);
				if ( g[y][x] == indeed )
					continue ;
				g[y][x] = indeed;
				add_arcs(y,x);
			}
			seen[x] = indeed;
			assert( l >= 1 );
		}
		for ( i = 0; i < V; ++i ) {
			assert( seen[i] == indeed );
			seen[i] = 0;
		}
		for ( top = st, ++yes, i = 0; i < V; ++i )
			if ( seen[i] != yes ) dfs(i,D);
		for ( scc = 0, ++yes; top > st; )
			if ( seen[x = *top--] != yes )
				card[++scc]=0, dfs(x,T);
		for ( i = 0; i < V; ++card[c[i]], ++i );
		for ( ++indeed, x = 0;  x < V; ++x )
			for ( i = last[D][x]; i >= 0; i = next[D][i] )
				if ( c[x]!=c[y=to[D][i]] )
					g[c[x]][c[y]] = indeed;
		memset(z,0,sizeof(z));
		for ( i = 1; i <= scc; ++i )
			for ( j = 1; j <= scc; ++j )
				if ( i != j && g[i][j] == indeed )
					++z[j];
		for ( top = st, i = 1; i <= scc; ++i ) {
			assert( card[i] >= 1 );
			if ( (!z[i])||card[i]>=2 ) 
				if ( !(card[i]==1&&!z[i]) )
					*++top = i;
		}
		ptr = buff;
		for ( m = 0; top > st; traverse(root,*top--) );
		qsort(word,m,L,cmp);
		for ( i = 0; i < m-1; ++i )
			assert( strcmp(word[i],word[i+1]) < 0 );
		printf("%d\n",m);
		for ( i = 0; i < m-1; ++i )
			printf("%s ",word[i]);
		printf("%s\n",word[m-1]);
		cleanup(root);
	}
	return 0;
}

