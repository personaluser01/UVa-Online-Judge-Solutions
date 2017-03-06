/*
 * 10704. Traffic!
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#define N 6
enum { H, V };
enum { TWO, THREE };
#define W 4
using namespace std;
typedef unsigned long long u64;
#define MASK(k) ((1ULL<<(k))-1ULL)
#define vc(x,y) (0<=(x)&&(x)<N&&0<=(y)&&(y)<N)
#define Q (1 << 16)
#define oo 0xfffffffful

unsigned char type_of_block[0x400],
	 		  length[0x400];
int m,dx[] = {0,1},
	  dy[] = {1,0},
	  xx[N*N],yy[N*N];

typedef struct state { 
	u64 c[3]; 
	state( u64 a, u64 b, u64 d ) { 0[c] = a, 1[c] = b, 2[c] = d; }
} state;

bool operator<( const state &a, const state &b ) {
	for ( int i = 0; i < 3; ++i )
		if ( a.c[i] != b.c[i] )
			return a.c[i] < b.c[i];
	return false;
}

bool operator==( const state &a, const state &b ) {
	for ( int i = 0; i < 3; ++i )
		if ( a.c[i] != b.c[i] )
			return false;
	return true;
}

/*
bool operator>( const state &a, const state &b ) {
	for ( int i = 0; i < 3; ++i )
		if ( a.c[i] != b.c[i] )
			return a.c[i] > b.c[i];
	return false;
}
*/

int Access( state &s, int x, int y ) { 
	u64 k = x*N+y;
	assert( ((k*W)>>6) < 3 );
	return (s.c[(k*W)>>6] >> ((k*W)&63ULL)) & MASK(W);
}

void clear_cell( state &s, int x, int y ) {
	u64 k = x*N+y;
	s.c[(k*W)>>6] &= ~(MASK(W)<<((k*W)&63ULL));
}

void set_cell( state &s, int x, int y, u64 idx ) {
	u64 k = x*N+y;
	clear_cell(s,x,y), s.c[(k*W)>>6]|=(idx<<((k*W)&63ULL));
}

void display( state &s ) {
	int i,j;
	printf("m = %d\n",m);
	for ( i = 0; i < N; ++i ) {
		for ( j = 0; j < N; ++j )
			printf("%3d",Access(s,i,j));
		puts("");
	}
}

bool move_it( state &s, int idx, int units ) {
	int i,j,k = 0,ni,nj,nk,t,l;
	state *ss = new state(s),
		  *ns = new state(0,0,0);

	if ( !units ) return false;
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < N; ++j ) {
			if ( Access(*ss,i,j) == idx ) {
				if ( units > 0 ) {
					for ( l = 1; l <= units; ++l ) {
						ni = i+dx[type_of_block[idx]]*l;
						nj = j+dy[type_of_block[idx]]*l;
						if ( !vc(ni,nj) ) return false;
						if ( Access(*ss,ni,nj) != 0 && Access(*ss,ni,nj) != idx )
							return false;
					}
				}
				else {
					for ( l = -1; l >= units; --l ) {
						ni = i+dx[type_of_block[idx]]*l;
						nj = j+dy[type_of_block[idx]]*l;
						if ( !vc(ni,nj) ) return false;
						if ( Access(*ss,ni,nj) != 0 && Access(*ss,ni,nj) != idx )
							return false;
					}
				}
				ni = i+dx[type_of_block[idx]]*units;
				nj = j+dy[type_of_block[idx]]*units;
				set_cell(*ns,ni,nj,idx);
				assert( Access(*ns,ni,nj) == idx );
				clear_cell(*ss,i,j);
				assert( Access(*ss,i,j) == 0 );
			}
		}
	for ( i = 0; i < 3; ++i ) ss->c[i] |= ns->c[i];
	for ( i = 0; i < 3; ++i ) s.c[i] = ss->c[i];
	delete ss; delete ns;
	return true;
}


map<state,int> E;
map<int,state*> S;
map<state*,state*> P;
unsigned int d[Q];
queue<int> q;
int n,cs;

bool fin( state *s ) {
	int i,j;
	for ( i = 0; i < N; ++i )
			if ( Access(*s,i,N-1) == 1 )
				return true;
	return false;

}

void dump( state *s ) {
	if ( P[s] )
		dump(P[s]), display(*s);
}

unsigned int bfs( state &src ) {
	state *s;
	int units,i,j,k,x,y;
	unsigned int w = +oo;

	s = new state(src);
	E.clear(), S.clear(), n = 0, S[E[*s] = n++] = s;
	P.clear(), P[s] = NULL;
	for ( d[0] = 0, q.push(E[*s]); !q.empty() && w == +oo; ) {
		x = q.front(), q.pop();
		if ( fin(S[x]) ) {
			w = d[x];
			break ;
		}
		for ( k = 1; k <= m; ++k )
			for ( units = -4; units <= 4; ++units ) {
				s = new state(*S[x]);
				if ( (move_it(*s,k,units)) ) {
					if ( E.find(*s) == E.end() )  {
						if ( n == Q ) return +oo;
						d[E[*s]=n++]=+oo, S[E[*s]] = s;
					}
					if ( d[y = E[*s]] > d[x]+1 )
						d[y] = d[x]+1, q.push(y), P[s] = S[x];
				}
				else delete s;
			}
	}
	// if ( w < +oo ) dump(S[x]);
	for ( map<int,state *>::iterator it = S.begin(); it != S.end(); ++it )
		delete it->second;
	while ( !q.empty() ) q.pop();
	return !w?1:w;
}

int main() {
	int i,j,k,l,ts;
	state *s;

#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	for ( scanf("%d",&ts); ts--; ) {
		s = new state(0,0,0);
		m = 1, scanf("%d %d",xx+m,yy+m);
		type_of_block[m] = H, length[m] = 2;

		for ( scanf("%d",&k), i = 0; i < k ; ++i ) {
			++m, type_of_block[m] = V, length[m] = 2;
			scanf("%d %d",xx+m,yy+m);
		}
		for ( scanf("%d",&k), i = 0; i < k; ++i ) {
			++m, type_of_block[m] = V, length[m] = 3;
			scanf("%d %d",xx+m,yy+m);
		}
		for ( scanf("%d",&k), i = 0; i < k ; ++i ) {
			++m, type_of_block[m] = H, length[m] = 2;
			scanf("%d %d",xx+m,yy+m);
		}
		for ( scanf("%d",&k), i = 0; i < k; ++i ) {
			++m, type_of_block[m] = H, length[m] = 3;
			scanf("%d %d",xx+m,yy+m);
		}
		for ( k = 1; k <= m; ++k )
			for ( l = 0; l < length[k]; ++l ) {
				assert( Access(*s,xx[k],yy[k]) == 0 );
				set_cell(*s,xx[k],yy[k],k);
				assert( Access(*s,xx[k],yy[k]) == k );
				xx[k] += dx[type_of_block[k]], yy[k] += dy[type_of_block[k]];
			}
		/*
		display(*s);
		move_it(*s,6,1);
		display(*s);
		move_it(*s,2,-1);
		display(*s);
		move_it(*s,7,1);
		display(*s);
	move_it(*s,5,1);
		display(*s);
	move_it(*s,4,-1);
		display(*s);
	move_it(*s,9,-1);
		display(*s);
	move_it(*s,2,-1);
		display(*s);

		return 0;
		*/
		printf("The minimal number of moves to solve puzzle %d is %d.\n",++cs,bfs(*s));
		delete s;
	}
	return 0;
}

