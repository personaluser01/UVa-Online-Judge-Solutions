/*
 * 11688. Rotate to Root
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
#define oo 0xfffffffful
#define is_leaf(x) (!left[x]&&!right[x])
#define other_son(y,x) (left[y]==x?right[y]:left[y])
#define setmax(a,b) a = max(a,b)

unsigned int max( unsigned int x, unsigned int y ) { return x<y?y:x; }

int n,left[N],right[N],has_parent[N],yes,root,p[N];
unsigned int z[N],d[N];

unsigned int calc_z( int x ) {
	if ( z[x] < +oo )
		return z[x];
	if ( !x )
		return z[x] = 0;
	return z[x] = 1+max(calc_z(left[x]),calc_z(right[x]));
}

unsigned int f( int x, int lheight=0, int rheight=0, int ltopheight=0, int rtopheight=0 ) {
	if ( d[x] < +oo )
		return d[x];
	d[x] = 0;
	setmax(d[x],1+lheight);
	setmax(d[x],1+rheight);
	setmax(d[x],1+ltopheight+z[left[x]]);
	setmax(d[x],1+rtopheight+z[right[x]]);

	if ( left[x] ) {
	}
	if ( right[x] ) {
	}

}

int main() {
	int i,j,k,x,y;
	unsigned int l,r,h;
#ifndef ONLINE_JUDGE
	freopen("E.4.dat","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 && ++yes ) {
		for ( i = 1; i <= n; ++i ) {
			scanf("%d %d",left+i,right+i);
			has_parent[left[i]] = has_parent[right[i]] = yes;
			p[left[i]] = p[right[i]] = i;
		}
		for ( root = 0, i = 1; i <= n && !root; ++i )
			if ( has_parent[i] != yes )
				root = i;
		assert( root );
		memset(z,0xfful,sizeof(z));
		p[root] = 0, calc_z(root);
		memset(d,0xfful,sizeof(d));
		f(root);
	}
	return 0;
}

