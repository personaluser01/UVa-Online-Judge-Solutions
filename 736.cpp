/*
 * 736. Lost in Space
 * TOPIC: trie, brute-force
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cctype>
#include <map>
#include <set>
#include <queue>
#define A 127
using namespace std;
#define N 0x80
#define MAXW (0x400)
#define vc(x,y) (0<=(x) && (x)<n && 0<=(y) && (y)<n)
#define FG(s) (fgets(s,sizeof s,stdin))
enum { NORTH, NE, E, SE, S, SW, W, NW };

char g[N][N],
	 dir[][3] = {"N","NE","E","SE","S","SW","W","NW"};
int n,len[MAXW],
	dx[] = {-1,-1,0,1,1,1,0,-1},
	dy[] = {0,1,1,1,0,-1,-1,-1};

struct occurrence {
	int x,y,direction,idx;
	occurrence( int x, int y, int t, int idx ) {
		this->x = x, this->y = y, this->direction = t, this->idx = idx;
	};
};

struct comparator {
	bool operator () ( const occurrence &a, const occurrence &b ) {
		if ( a.idx != b.idx )
			return a.idx < b.idx;
		if ( a.x == b.x ) {
			if ( a.y == b.y ) 
				return a.direction < b.direction;
			return a.y < b.y;
		}
		return a.x < b.x;
	}
};

bool isempty( char *s ) {
	for ( ;*s && *s != '\n'; ++s )
		if ( !isspace(*s) )
			return false ;
	return true ;
}

typedef struct cell {
	cell *slink;
	map<int,cell *> son;
	set<int> idx;
	cell() {
		son.clear(), idx.clear(), slink = NULL;
	};
	cell *operator () ( int ch ) {
		if ( son.count(ch) )
			return son[ch];
		return NULL;
	};
	void set_slink( cell *x ) {
		this->slink = x;
	};
	void merge( cell *x ) {
		for ( set<int> :: iterator it = x->idx.begin(); it != x->idx.end(); this->idx.insert(*it++) ) ;
	};
	void add_son( int ch ) {
		this->son[ch] = new cell();
	}
	void add_idx( int i ) {
		idx.insert(i);
	}
	void add_son( int ch, cell *y ) {
		son[ch] = y;
	}
} cell;

cell *root,*q0;
queue<cell *> q;
char buff[0x400],word[MAXW][N];
set<occurrence,comparator> s;

void push( char *s, int idx ) {
	cell *x,*y;
	for ( x = root; x && *s; x = (*x)(*s++) ) 
		if ( !(*x)(*s) )
			x->add_son(*s);
	x->add_idx(idx);
}

int main() {
	int i,j,k,t,cs=0,ts,ch,ci,cj,m;
	cell *x,*y,*z;
	for ( sscanf(FG(g[0]),"%d",&ts), FG(g[0]); ts--; ) {
		if ( ++cs > 1 ) putchar('\n');
		sscanf(FG(g[0]),"%d",&n);
		for ( i = 0; i < n; FG(g[i]), ++i ) ;
		q0 = new cell(), root = new cell();
		for ( ch = 0; ch < A; q0->add_son(ch,root), ++ch ) ;
		for ( k = 0; FG(buff) && !isempty(buff); ++k ) {
			for ( i = 0; buff[i] && buff[i] != '\n'; ++i ) ; buff[i] = '\0';
			strcpy(word[k],buff), push(word[k],k);
		}
		for ( m = k, root->slink = q0, q.push(root); !q.empty(); q.pop() ) 
			for ( map<int,cell *> :: iterator it = (x = q.front())->son.begin(); it != x->son.end(); y->slink = (*z)(ch), q.push(y), ++it ) 
				for ( y = it->second, ch = it->first, z = x->slink; !(*z)(ch); z = z->slink ) ;
		for ( s.clear(), i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( t = NORTH; t <= NW && !isspace(g[i][j]); ++t ) {
					for ( x = root, ci = i, cj = j; vc(ci,cj); ci += dx[t], cj += dy[t] ) {
						if ( isspace(ch = g[ci][cj]) ) continue ;
						if ( !(*x)(ch) ) break ;
						//for ( ;x && !(*x)(ch); x=x->slink ) ;
						for ( set<int> :: iterator it = (x=(*x)(ch))->idx.begin(); it != x->idx.end(); s.insert(occurrence(i,j,t,*it++)) ) ;
					}
				}
		t = -1;
		for ( set<occurrence,comparator> :: iterator it = s.begin(); it != s.end(); t = it->idx, ++it ) {
			if ( t != it->idx ) {
				assert( t < it->idx );
				for ( ;++t != it->idx; printf("\n%s\nnot found\n",word[t]) ) ;
				printf("\n%s\n",word[t]);
			}
			printf("(%d,%d) - %s\n",it->x+1,it->y+1,dir[it->direction]);
		}
		if ( !s.size() || t < m-1 ) 
			for ( ; ++t < m; printf("\n%s\nnot found\n",word[t]) ) ;
	}
	return 0;
}

