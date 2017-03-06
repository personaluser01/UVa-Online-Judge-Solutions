/*
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8
#define xchg(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))

char s[N+N],inv_map[N];
int n,a[N+N],F[N+1],q[N+N];

int the_last( int *c, int n ) {
	int i;
	for ( i = 0; i < n-1; ++i )
		if ( c[i] < c[i+1] )
			return 0;
	return 1;
}

int pick_smallest( int x, int *c, int n ) {
	int i,ind,m = (1 << 29);
	for ( i = 0; i < n; ++i )
		if ( c[i] > x && c[i] < m )
			m = c[i], ind = i;
	return ind;
}

void reorder( int *c, int n ) {
	int i,j;
	for ( j = 1; j; )
		for ( j = 0, i = 0; i < n-1; ++i )
			if ( c[i] > c[i+1] )
				++j, xchg(c[i],c[i+1]);
}

void next_perm( int *c, int n ) {
	int i;
	if ( n == 1 ) return ;
	assert( n > 1 );
	if ( the_last(c+1,n-1) ) {
		i = pick_smallest(c[0],c+1,n-1)+1;
		xchg(c[0],c[i]);
		reorder(c+1,n-1);
	}
	else 
		next_perm(c+1,n-1);
}

void printout( int *c, int n ) {
	int i;
	for ( i = 0; i < n; putchar(inv_map[c[i++]]) );
	putchar('\n');
}

int main() {
	int i,j,k,tmp,o[N],ax;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	for ( F[0] = 1, n = 1; n <= N; F[n] = F[n-1]*n, ++n );
	while ( 1 == scanf("%s",s) ) {
		n = strlen(s);
		for ( i = 0; i < n; q[i] = s[i], ++i );
		reorder(q,n);
		for ( inv_map[a[0] = k = 0] = q[0], i = 1; i < n; ++i )
			if ( q[i] != q[i-1] ) {
				assert( q[i] > q[i-1] );
				inv_map[a[i] = ++k] = q[i];
			}
			else a[i] = a[i-1];
		for ( i = 0; i <= k; ++i )
			for ( o[i] = 0, j = 0; j < n; ++j )
				if ( a[j] == i && ++o[i] );
		printout(a,n);
		for ( ax = F[n], i = 0; i <= k; ++i )
			ax /= F[o[i]];
		for ( k = ax-1; k--; ) {
			next_perm(a,n);
			printout(a,n);
		}
	}
	return 0;
}

