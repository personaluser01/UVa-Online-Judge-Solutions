/*
 * 308. Tin Cutter
 * status: Accepted
 * KEYWORDS: DSU, Union find, coordinate compression, floodfill
 */
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define tol 1e-9
#define N 0x80
#include <set>
#include <algorithm>
#define Q 0x400
using namespace std;
enum { VERTICAL, HORISONTAL };
#define valid_cell(x,y) (0<=(x)&&(x)<=m[0]+4&&0<=(y)&&(y)<=m[1]+4)

int n,x[4][N],z[4][N],color,**g,m[2],
	dx[] = {-1,0,1,0},
	dy[] = {0,-1,0,1};
set<int> s[2];
set<pair<pair<int,int>,pair<int,int> > > forbid;

int f( int t, int x ) {
	int i = 1;
	t &= 1;
	for ( set<int>::iterator it = s[t].begin(); it != s[t].end(); ++it, ++i )
		if ( *it == x )
			return i;
	assert( 0 );
}

int type_of_cut( int i ) {
	if ( x[0][i] == x[2][i] )
		return VERTICAL;
	assert( x[1][i] == x[3][i] );
	return HORISONTAL;
}

void floodfill( int x, int y ) {
	int nx,ny,i;
	assert( g[x][y] == 0 );
	for ( g[x][y] = color, i = 0; i < 4; ++i ) {
		nx = x + dx[i], ny = y + dy[i];
		if ( !valid_cell(nx,ny) )
			continue ;
		if ( g[nx][ny] )
			continue ;
		if ( forbid.find(make_pair(make_pair(x,y),make_pair(nx,ny))) != forbid.end() )
			continue ;
		floodfill(nx,ny);
	}
}

int *rank,*parent,*is_dad;

int make_set( int i ) {
	rank[parent[i] = i] = 1;
}

int find_parent( int i ) {
	if ( parent[i] == i )
		return i;
	return parent[i] = find_parent(parent[i]);
}

void link( int i, int j ) {
	if ( rank[i] > rank[j] ) {
		parent[j] = i;
	}
	else {
		parent[i] = j;
		if ( rank[i] == rank[j] )
			++rank[j];
	}
}

void merge( int i, int j ) {
	link(find_parent(i),find_parent(j));
}

int main() {
	int i,j,k,t,sx[2],ti,tj,c[2];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n ) {
		for ( t = 0; t <= 1; s[t++].clear() );
		for ( i = 0; i < n; ++i ) {
			scanf("%d %d %d %d",x[0]+i,x[1]+i,x[2]+i,x[3]+i);
			if ( x[0][i] > x[2][i] )
				swap(x[0][i],x[2][i]), swap(x[1][i],x[3][i]);
			else if ( x[0][i] == x[2][i] && x[1][i] > x[3][i] )
				swap(x[0][i],x[2][i]), swap(x[1][i],x[3][i]);
		}
		for ( i = 0; i < n; ++i ) {
			for ( t = 0; t <= 1; ++t )
				for ( j = t; j < 4; j += 2 )
					s[t].insert(x[j][i]);
			for ( j = i+1; j < n; ++j ) {
				if ( x[2][j] < x[0][i] || x[2][i] < x[0][j] )
					continue ;
				if ( x[3][j] < x[1][i] || x[3][i] < x[1][j] )
					continue ;
				ti = type_of_cut(i), tj = type_of_cut(j);
				if ( ti == tj )
					continue ;
				if ( ti == VERTICAL ) {
					assert( tj == HORISONTAL );
					sx[0] = x[0][i], sx[1] = x[1][j];
				}
				else {
					assert( ti == HORISONTAL );
					assert( tj == VERTICAL );
					sx[0] = x[0][j], sx[1] = x[1][i];
				}
				for ( t = 0; t <= 1; ++t )
					s[t].insert(sx[t]);
			}
		}
		for ( t = 0; t <= 1; ++t )
			m[t] = s[t].size()+3;
		forbid.clear();
		for ( i = 0; i < n; ++i ) {
			for ( j = 0; j < 4; ++j )
				z[j][i] = f(j&1,x[j][i]);
			assert( x[0][i] == x[2][i] || x[1][i] == x[3][i] );
			assert( z[0][i] == z[2][i] || z[1][i] == z[3][i] );
			if ( z[0][i] == z[2][i] ) {
				c[0] = z[0][i], c[1] = z[1][i];
				for ( ;c[1] < z[3][i]; ++c[1] ) {
					forbid.insert(make_pair(make_pair(c[0]-1,c[1]),make_pair(c[0],c[1])));
					forbid.insert(make_pair(make_pair(c[0],c[1]),make_pair(c[0]-1,c[1])));
				}
			}
			else {
				assert( z[1][i] == z[3][i] );
				c[0] = z[0][i], c[1] = z[1][i];
				for ( ;c[0] < z[2][i]; ++c[0] ) {
					forbid.insert(make_pair(make_pair(c[0],c[1]),make_pair(c[0],c[1]-1)));
					forbid.insert(make_pair(make_pair(c[0],c[1]-1),make_pair(c[0],c[1])));
				}
			}
		}
		assert( g = (int **)malloc((m[0]+8)*sizeof *g) );
		for ( i = 0; i <= m[0]+4; ++i )
			assert( g[i] = (int *)malloc((m[1]+8)*sizeof *g[i]) );
		for ( i = 0; i <= m[0]+4; ++i )
			for ( j = 0; j <= m[1]+4; ++j )
				g[i][j] = 0;
		for ( color = 0, i = 0; i <= m[0]+2; ++i )
			for ( j = 0; j <= m[1]+2; ++j )
				if ( !g[i][j] && ++color )
					floodfill(i,j);
		rank   = (int *)calloc(color+1, sizeof *rank);
		parent = (int *)calloc(color+1, sizeof *parent);
		is_dad = (int *)calloc(color+1, sizeof *is_dad);
		for ( i = 1; i <= color; ++i )
			make_set(i);
		for ( i = 0; i <= m[0]+4; ++i )
			for ( j = 0; j <= m[1]+4; ++j ) {
				if ( g[i][j] == 1 ) 
					continue ;
				for ( k = 0; k < 4; ++k ) {
					int ni = i+dx[k],
						nj = j+dy[k];
					if ( !valid_cell(ni,nj) )
						continue ;
					if ( g[ni][nj] != 1 ) {
						if ( find_parent(g[ni][nj]) != find_parent(g[i][j]) )
							merge(g[ni][nj],g[i][j]);
					}
				}
			}
		for ( i = 0; i <= m[0]+4; ++i )
			for ( j = 0; j <= m[1]+4; ++j )
				if ( g[i][j] != 1 )
					is_dad[find_parent(g[i][j])] = 1;
		for ( k = 0, i = 1; i <= color; ++i )
			if ( is_dad[i] && ++k );
		printf("%d\n",k);
		free( rank ), free( parent ), free( is_dad );
		for ( i = 0; i <= m[0]+4; ++i )
			free( g[i] );
		free( g );
	}
	return 0;
}

