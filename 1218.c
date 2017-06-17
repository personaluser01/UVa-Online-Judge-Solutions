/*
 * 1218. Perfect Service
 * TOPIC: dp on tree
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV (1<<14)
#define MAXE (MAXV<<1)
#define oo (1<<30)

int min( int x, int y ) {
	return x<y?x:y;
}

int n,to[MAXE],next[MAXE],last[MAXV],E,parent[MAXV],
	z[2][2][MAXV],c[MAXV],seen[MAXV],yes,is_leaf[MAXV],
	leaf_sons[MAXV],has_leaf_grandson[MAXV],son[MAXV],
	visited[2][2][MAXV];

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
}

void dfs( int x ) {
	int i,y,l = 0;
	assert( seen[x] != yes );
	leaf_sons[x] = has_leaf_grandson[x] = 0;
	for ( seen[x] = yes, i = last[x]; i >= 0; i = next[i] ) 
		if ( seen[y = to[i]] != yes ) {
			parent[y] = i, ++l, dfs(y);
			if ( is_leaf[y] ) {
				if ( ++leaf_sons[x] == 1 )
					son[x] = y;
			}
			if ( leaf_sons[y] )
				has_leaf_grandson[x] = 1;
		}
	is_leaf[x] = !l;
}

int calc_z( int k, int t, int x ) {
	int i,y,dw,j;
	if ( visited[k][t][x] == yes )
		return z[k][t][x];
	visited[k][t][x] = yes;
	if ( is_leaf[x] ) {
		if ( k == 0 && t == 0 )
			return z[k][t][x] = +oo;
		if ( k == 0 && t == 1 )
			return z[k][t][x] = 1;
		if ( k == 1 && t == 0 )
			return z[k][t][x] = 0;
		if ( k == 1 && t == 1 )
			return z[k][t][x] = 1;
		assert( 0 );
	}
	if ( k == 0 && t == 0 ) {
		if ( leaf_sons[x] >= 2 )
			return +oo;
		z[k][t][x] = 0;
		if ( leaf_sons[x] == 1 ) {
			for ( i = last[x]; i >= 0; i = next[i] )
				if ( parent[y = to[i]] == i ) {
					if ( son[x] == y )
						++z[k][t][x];
					else if ( calc_z(0,0,y) < +oo )
						z[k][t][x] += calc_z(0,0,y);
					else 
						return z[k][t][x] = +oo;
				}
		}
		else {
			assert( leaf_sons[x] == 0 ) ;
			for ( j = 0, dw = +oo, i = last[x]; i >= 0; i = next[i] )
				if ( parent[y = to[i]] == i ) 
					if ( calc_z(0,0,y) == +oo && ++j >= 2 )
						return z[k][t][x] = +oo;
			if ( j == 1 )  {
				for ( i = last[x]; i >= 0; i = next[i] )
					if ( parent[y = to[i]] == i ) {
						if ( calc_z(0,0,y) == +oo ) {
							dw = calc_z(0,1,y);
							if ( dw == +oo )
								return z[k][t][x] = +oo;
						}
						else z[k][t][x] += calc_z(0,0,y);
					}
			}
			else {
				assert( j == 0 );
				for ( i = last[x]; i >= 0; i = next[i] ) 
					if ( parent[y = to[i]] == i ) {
						assert( calc_z(0,1,y) < +oo );
						dw = min(dw,calc_z(0,1,y)-calc_z(0,0,y));
						z[k][t][x] += calc_z(0,0,y);
					}
			}
			assert( dw < +oo ) ;
			z[k][t][x] += dw;
		}
		return z[k][t][x];
	}
	if ( k == 0 && t == 1 ) {
		z[k][t][x] = 1;
		for ( i = last[x]; i >= 0; i = next[i] )
			if ( parent[y = to[i]] == i ) {
				dw = min(calc_z(1,1,y),calc_z(1,0,y));
				if ( dw == +oo ) return z[k][t][x] = +oo;
				z[k][t][x] += dw;
			}
		return z[k][t][x];
	}
	if ( k == 1 && t == 0 ) {
		z[k][t][x] = 0;
		for ( i = last[x]; i >= 0; i = next[i] )
			if ( parent[y = to[i]] == i ) {
				if ( calc_z(0,0,y) == +oo )
					return z[k][t][x] = +oo;
				z[k][t][x] += calc_z(0,0,y);
			}
		return z[k][t][x];
	}
	assert( k == 1 && t == 1 ) ;
	z[k][t][x] = 1;
	for ( i = last[x]; i >= 0; i = next[i] )
		if ( parent[y = to[i]] == i ) {
			dw = min(calc_z(1,0,y),calc_z(1,1,y));
			if ( dw == +oo ) 
				return z[k][t][x] = +oo;
			z[k][t][x] += dw;
		}
	return z[k][t][x];
}

int main() {
	int i,j,k;
	for ( ;1 == scanf("%d",&n) && n >= 0; scanf("%d",&k) ) {
		for ( E = 0, i = 0; i < n; last[i++] = -1 ) ;
		for ( k = 0; k < n-1; ++k ) 
			scanf("%d %d",&i,&j), --i, --j, add_arcs(i,j);
		for ( ++yes, parent[0] = -1, dfs(0), i = 0; i < n; ++i )
			z[0][0][i] = z[0][1][i] = z[1][0][i] = z[1][1][i] = +oo, c[i] = -1;
		printf("%d\n",min(calc_z(0,0,0),calc_z(0,1,0)));
	}
	return 0;
}

