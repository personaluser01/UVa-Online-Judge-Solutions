/*
 * 10923. Seven Seas
 * status: Accepted
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <cassert>
#include <set>
using namespace std;
typedef unsigned long long u64;
enum { SEA, ROCK, ME, ENEMY };
#define SET(u,k) ((u)|=BIT(k))
#define CLR(u,k) ((u)&=~BIT(k))
#define TST(u,k) ((u)&BIT(k))
#define MASK(k) (BIT(k)-1ull)
#define BIT(k) (1ull<<(k))
#define vc(x,y) (0<=(x)&&(x)<M&&0<=(y)&&(y)<N)
#include <queue>
#define M 9
#define N 8
#define Q (1 << 19)
// #define S(x) ((x)*(x))
#define S(x) (abs(x))

char g[256];

struct state {
	u64 u[3];
	state() { memset(u,0,sizeof(u)); }
	int get_item( int i, int j ) {
		u64 k = 2*(i*N+j);
		return (u[k>>6] >> (k&63ull)) & MASK(2);
	}
	void display() {
		int i,j;
		for ( i = 0; i < M; ++i ) {
			for ( j = 0; j < N; ++j )
				putchar(g[this->get_item(i,j)]);
			puts("");
		}
	}
	pair<int,int> my_pos() {
		int i,j;
		for ( i = 0; i < M; ++i )
			for ( j = 0; j < N; ++j )
			if ( this->get_item(i,j) == ME )
				return make_pair(i,j);
		assert( 0 );
	}
	void clear_cell( int x, int y ) {
		u64 k = 2*(x*N+y);
		u[k>>6] &= ~(MASK(2)<<(k&63ull));
	}
	void set_cell( int x, int y, int t ) {
		u64 k = 2*(x*N+y);
		this->clear_cell(x,y);
		u[k>>6] |= (((u64)t) << (k&63ull));
	}
	const state move_ships() {
		state s = *this;
		pair<int,int> p = this->my_pos();
		vector<pair<int,int> > q,qq;
		q.clear(), qq.clear();
		for ( int i = 0; i < M; ++i )
			for ( int j = 0; j < N; ++j )
				if ( this->get_item(i,j) == ENEMY )
					q.push_back(make_pair(i,j));
		for ( int i = 0; i < (int)q.size(); ++i )
			s.clear_cell(q[i].first,q[i].second);
		for ( int i = 0; i < (int)q.size(); ++i ) {
			int x = q[i].first,
				y = q[i].second,
				  nx,ny,k,t,bx,by,w = (1<<29);
			bx = x, by = y;
			for ( k = -1; k <= 1; ++k )
				for ( t = -1; t <= 1; ++t ) {
					if ( !k && !t ) continue ;
					// if ( abs(k) + abs(t) != 1 ) continue ;
					nx = x+k, ny = y+t;
					if ( !vc(nx,ny) ) continue ;
					if ( S(nx-p.first)+S(ny-p.second) < w )
						w = S(nx-p.first)+S(ny-p.second), bx = nx, by = ny;
				}
			qq.push_back(make_pair(bx,by));
		}
		for ( int i = 0; i < (int)qq.size(); ++i )
			if ( s.get_item(qq[i].first,qq[i].second) == ENEMY||s.get_item(qq[i].first,qq[i].second) == ROCK )
				s.set_cell(qq[i].first,qq[i].second,ROCK);
			else s.set_cell(qq[i].first,qq[i].second,ENEMY);
		return s;
	}
	bool no_enemy() {
		int i,j;
		for ( i = 0; i < M; ++i )
			for ( j = 0; j < N; ++j )
				if ( this->get_item(i,j) == ENEMY )
					return false;
		return true;
	}
	bool move_me( pair<int,int> from, pair<int,int> to ) {
		if ( this->get_item(to.first,to.second) != SEA )
			return false;
		this->clear_cell(from.first,from.second);
		this->set_cell(to.first,to.second,ME);
		return true;
	}
	bool i_am_eaten() {
		int i,j;
		for ( i = 0; i < M; ++i )
			for ( j = 0; j < N; ++j )
				if ( this->get_item(i,j) == ME )
					return false;
		return true;
	}
};

bool dfs( state &s, int cost ) {
	if ( cost >= 20 )
		return false;
	if ( s.i_am_eaten() )
		return false;
	if ( s.no_enemy() )
		return true;
	if ( cost & 1 ) {
		state t = s.move_ships();
		return dfs(t,cost+1);
	}
	pair<int,int> p = s.my_pos();
	int i,j;
	for ( i = -1; i <= 1; ++i ) {
		for ( j = -1; j <= 1; ++j ) {
			if ( !i && !j )
				continue ;
			int nx = p.first+i,
				ny = p.second+j;
			if ( !vc(nx,ny) )
				continue ;
			state t = s;
			if ( t.move_me(p,make_pair(nx,ny)) )
				if ( dfs(t,cost+1) )
					return true;
		}
	}
	return false;
}

int main() {
	int i,j,cs;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	g[SEA] = '.', g[ENEMY] = 'E', g[ME] = 'S', g[ROCK] = '#';
	for ( scanf("%d",&cs); cs--; ) {
		state s;
		for ( i = 0;i < M; ++i ) {
			scanf("%s",tmp);
			for ( j = 0; j < N; ++j )
				if ( tmp[j] == 'E'||tmp[j]=='e' )
					s.set_cell(i,j,ENEMY);
				else if ( tmp[j] == '.' )
					s.set_cell(i,j,SEA);
				else if ( tmp[j] == '#' )
					s.set_cell(i,j,ROCK);
				else s.set_cell(i,j,ME);
		}
		puts(dfs(s,0)?"I'm the king of the Seven Seas!":"Oh no! I'm a dead man!");
	}
	return 0;
}

