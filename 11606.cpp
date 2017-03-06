/*
 * 11606.Atoms
 * TOPIC: bfs, manhattan distance
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#define N 8
#include <map>
#include <queue>
#define BIT(k)   (1ULL<<(k))
#define MASK(k)  (BIT(k)-1ULL)
typedef unsigned long long u64;
using namespace std;

int ts,cs,n,g[N][N],shift[N][N],limit[N][N];
u64 mask[N][N];
bool ok;

bool is_corner( int x, int y ) { return x==0&&(y==0||y==n-1) || x==n-1&&(y==0||y==n-1); }
bool is_edge( int x, int y ) { return !is_corner(x,y) && (x==0||x==n-1||y==0||y==n-1); }
bool is_inner( int x, int y ) { return 1 <= x && x <= n-2 && 1 <= y && y <= n-2; }

typedef struct state {
	u64 u[2];
	state( u64 *u ) { this->u[0] = u[0]; this->u[1] = u[1]; }
	state() { this->u[0] = this->u[1] = 0; }
} state;

void next_pos( int t, state &s, int *x, int *y ) {
	int i,j,k,l,h[N][N],max_w=-(1<<29),w=(1<<29),ii,jj,a = 0,b = 0,best_i=-1,best_j=-1;
	pair<int,int> neg[N*N],pos[N*N];
	bool is_pos[N][N]={0},
		 is_neg[N][N]={0};
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) {
			h[i][j] = ((s.u[shift[i][j]>>6]>>(shift[i][j]&63))&mask[i][j]);
			if ( h[i][j] ) {
				if ( g[i][j] < 0 )
					is_neg[i][j] = true;
				else is_pos[i][j] = true;
			}
		}
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			if ( h[i][j] ) {
				if ( g[i][j] < 0 )
					neg[a++] = make_pair(i,j);
				else if ( g[i][j] > 0 )
					pos[b++] = make_pair(i,j);
			}
	if ( t > 0 ) {
		for ( ii = 0; ii < n; ++ii )
			for ( jj = 0; jj < n; ++jj )
				if ( !is_neg[ii][jj] && limit[ii][jj] >= h[ii][jj]+1 ) {
					for ( w = (1<<29), l = 0; l < a; ++l ) {
						i = neg[l].first, j = neg[l].second;
						if ( abs(i-ii)+abs(j-jj) < w )
							w = abs(i-ii)+abs(j-jj);
					}
					if ( w > max_w || (w == max_w && (ii<best_i || ii == best_i && jj < best_j)) ) 
						max_w = w, best_i = ii, best_j = jj;
				}
		*x = best_i, *y = best_j;
	}
	else {
		for ( ii = 0; ii < n; ++ii )
			for ( jj = 0; jj < n; ++jj )
				if ( !is_pos[ii][jj] && limit[ii][jj] >= h[ii][jj]+1 ) {
					for ( w = (1<<29), l = 0; l < b; ++l ) {
						i = pos[l].first, j = pos[l].second;
						if ( abs(i-ii)+abs(j-jj) < w )
							w = abs(i-ii)+abs(j-jj);
					}
					if ( w > max_w || (w == max_w && (ii<best_i || ii == best_i && jj < best_j)) ) 
						max_w = w, best_i = ii, best_j = jj;
				}
		*x = best_i, *y = best_j;
	}
}

int whose_turn( state &s ) {
	int i,j,k,t,a = 0, b = 0,h[N][N];
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			h[i][j] = ((s.u[shift[i][j]>>6]>>(shift[i][j]&63))&mask[i][j]);
	/*
	for ( i = 0; i < n; ++i, putchar('\n') )
		for ( j = 0; j < n; ++j )
			printf("%3d",h[i][j]);
	for ( i = 0; i < n; ++i, putchar('\n') )
		for ( j = 0; j < n; ++j )
			printf("%3d",g[i][j]);
			*/

	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			if ( h[i][j] ) {
				if ( g[i][j]<0 ) a += h[i][j];
				else if ( g[i][j] > 0 ) b += h[i][j];
			}
	if ( a == b )
		return  1;
	// assert( a+1 == b );
	return -1;
}

int signum( int x ) {
	if ( !x ) return 0;
	if ( x < 0 ) return -1;
	return 1;
}

queue<state> q;
state T;

bool is_target( state &s ) {
	int i,j,k = 0,h[N][N],t;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j ) 
			if ( h[i][j] = ((s.u[shift[i][j]>>6]>>(shift[i][j]&63))&mask[i][j]) )
				k += h[i][j], t = signum(g[i][j]);
	return k == 0||(k == 1 && t == 1);
}

bool bfs() {
	state s,t;
	int i,j,k,x,y,h[N][N];
	u64 l;
	for(;!q.empty();q.pop());
	if ( T.u[0] == 0 && T.u[1] == 0 )
		return true;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			if ( g[i][j] > 0 ) {
				s.u[0] = s.u[1] = 0;
				s.u[shift[i][j]>>6] |= (((u64)1)<<(shift[i][j]&63));
				q.push(s);
			}
	while ( !q.empty() ) {
		s = q.front(), q.pop();
		if ( s.u[0] == T.u[0] && s.u[1] == T.u[1] )
			return true;
	   	k = whose_turn(s), next_pos(k,s,&x,&y);
		if ( x == -1 ) 
			continue ;
		l = ((s.u[shift[x][y]>>6]>>(shift[x][y]&63))&mask[x][y]);
		if ( signum(g[x][y]) != signum(k) )
			continue ;
		++l;
		assert( limit[x][y] >= l );
		s.u[shift[x][y]>>6]&=~(mask[x][y]<<(shift[x][y]&63));
		s.u[shift[x][y]>>6]|=(l<<(shift[x][y]&63));
		q.push(s);
	}
	return false;
}

int main() {
	int i,j,k,l;
	state s;
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n) && printf("Case %d: ",++cs); ) {
		for ( ok = true, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) {
				scanf("%d",&g[i][j]);
				if ( is_corner(i,j) && abs(g[i][j]) >= 2 ) ok = false;
				if ( is_edge(i,j) && abs(g[i][j]) >= 3 ) ok = false;
				if ( is_inner(i,j) && abs(g[i][j]) >= 4 ) ok = false;
			}
		for ( k = l = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] > 0 ) k += abs(g[i][j]);
				else if ( g[i][j] < 0 ) l += abs(g[i][j]);
		if ( abs(l-k) >= 2 || !(k >= l) ) { 
			ok = false;
			goto next;
		}
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( is_corner(i,j) )
					limit[i][j] = 1;
				else if ( is_edge(i,j) )
					limit[i][j] = 2;
				else limit[i][j] = 3;
		for ( k = 0, i = 0; i < n && ok; ++i )
			for ( j = 0; j < n && ok; ++j ) 
				shift[i][j] = k, k += 2, mask[i][j] = MASK(2);
next:
		if ( !ok ) {
			puts("invalid");
			continue ;
		}
		for ( s.u[0] = s.u[1] = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				s.u[shift[i][j]>>6] |= (((u64)abs(g[i][j]))<<(shift[i][j]&63));
		T.u[0] = s.u[0], T.u[1] = s.u[1];
		if ( bfs() ) puts("valid");
		else { ok = false; goto next; }
	}
    return 0;
}

