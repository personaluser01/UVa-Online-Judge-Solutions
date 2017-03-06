/*
 * 12552. The Moon of Valencia
 * TOPIC: priority queue, A*
 * status: in progress
 */
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define tol 1e-13
#define N 0x60
#define oo (1L<<29)
#define S(k) ((k)*(k))
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define BIT(k) (1ULL<<(k))
#define L(k) ((k) & ((~(k))+1ULL))
typedef unsigned long long u64;
using namespace std;

map<string,int> s;
char buff[1<<16],*ptr;
string ID[N];

struct place {
	char a[0x200],b[0x200];
	long double x,y,w;
	int id;
	string name;
	place() {};
	void read() { 
		FG;
		assert( 5 == sscanf(ptr,"%Lf %Lf %Lf %s %[^\n]",&x,&y,&w,a,b) );
		int V = s.size();
		ID[id=s[string(a)]=V++]=string(a);
		name = string(b);
	};
};

place p[N];
int m,n,dst;
long double g[N][N],S,d[N];
const long double speed = 4.00/3600.00;

struct state {
	struct state *p;
	u64 visited;
	int x;
	long double w,t;
	bool cur_included;
	state() {p=NULL,visited=0;};
	state( state *P, int X, long double W ) { 
		p=P, x=X, w=W, cur_included=false, t=0, this->visited=(!p?0:p->visited)|BIT(x); 
	};
};

struct state_comparator {
	bool operator () ( state *a, state *b ) const {
		long double ha = a->w-g[a->x][dst]/60.00,
			 	    hb = b->w-g[b->x][dst]/60.00;
		return fabs(S-ha) > fabs(S-hb);
	};
};

struct cmpr {
	bool operator () ( state *a, state *b ) const {
		if ( fabs(a->w-b->w) < tol ) {
			if ( fabs(a->t-b->t) < tol ) {
				if ( a->x == b->x ) {
					if ( a->cur_included == b->cur_included ) {
						if ( a->visited==b->visited )
							return false ;
						return a->visited<b->visited;
					}
					return a->cur_included;
				}
				return a->x<b->x;
			}
			return a->t<b->t;
		}
		return a->w<b->w;
	};
};

priority_queue<state *,vector<state *>,state_comparator> pq;
set<state *,cmpr> ss;
state *tail;
char which[1<<20];
u64 MSK;

int who( u64 u ) {
	if ( u >= (1ULL<<60) )
		return 60+which[u>>60];
	if ( u >= (1ULL<<40) )
		return 40+which[u>>40];
	if ( u >= (1ULL<<20) )
		return 20+which[u>>20];
	return which[u];
}

bool a_star_search( int src, long double time_limit ) {
	state *u,*v;
	long double best = +oo;
	int y;
	u64 vv;

	for (;!pq.empty();pq.pop());
	for ( ss.clear(), ss.insert(u = new state(NULL,src,(long double)0.00)), pq.push(u); !pq.empty() && best >= 0.1; ) {
		u = pq.top(), pq.pop();
		if ( u->x == dst ) {
			if ( fabs(u->w-S) < best ) 
				best = fabs(u->w-S), tail = u;
			continue ;
		}
		if ( !u->cur_included && u->t+15*60 <= time_limit && g[u->x][dst] < +oo ) {
			v = new state(u,u->x,u->w+p[u->x].w), v->cur_included = true, v->t = u->t+15*60;
			if ( v->t+g[v->x][dst] <= time_limit && !ss.count(v) ) ss.insert(v), pq.push(v);
		}
		for ( vv = ((~(u->visited))&MSK); vv && (y=who(L(vv))) >= 0; vv &= ~L(vv) ) 
			if ( !(u->visited&BIT(y)) && g[y][dst] < +oo && y != u->x && g[u->x][y] < +oo && u->t+g[u->x][y] <= time_limit ) {
				v = new state(u,y,u->w-g[u->x][y]/60.00), v->t = u->t+g[u->x][y], v->visited |= BIT(y);
				if ( v->t+g[v->x][dst] <= time_limit && !ss.count(v) ) ss.insert(v), pq.push(v);
			}
	}
	return fabs(best)<0.1;
};

long double G( int h0, int m0, int h1, int m1 ) {
	if ( h0>h1 || h0==h1 && m0>m1 ) 
		return 24*60 - G(h1,m1,h0,m0);
	else {
		assert( h0 < h1 || h0==h1 && m0<=m1 );
		return 60*h1+m1 - 60*h0-m0;
	}
};

int out[1<<21],*qtr;

void dump( state *u ) {
	if ( u ) { 
		dump(u->p);
		*qtr++ = ((u->x)<<1)|(u->cur_included?1:0);
		/*
		if ( u->cur_included ) printf("  %s",ID[u->x].c_str());
		else printf(" !%s",ID[u->x].c_str());
		*/
	}
};

int main() {
	int i,j,k,h0,h1,m0,m1,src,cs;
	char tmp[0x400],p0[0x400],p1[0x400];
	string t0,t1;
	long double w;
#ifndef ONLINE_JUDGE
	freopen("moon01.in","r",stdin);
#endif
	for ( i = 0; i < 20; which[1<<i] = i, ++i );
	for ( FG; 3 == sscanf(buff,"%s %d %d",tmp,&n,&m) && 0 == strcmp(tmp,"MAP"); ) {
		printf("MAP %d\n",++cs);
		for ( s.clear(), MSK = 0, i = 0; i < n; MSK |= (1ULL<<i), p[i++].read() );
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; g[j][i] = g[i][j] = +oo, ++j );
		for ( k = 0; k < m; ++k ) {
			cin >> t0 >> t1;
			i=s[t0], j=s[t1], g[j][i]=g[i][j]=sqrt(S(p[i].x-p[j].x)+S(p[i].y-p[j].y));
		}
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( g[i][k] < +oo && g[k][j] < +oo )
						if ( g[i][j] > g[i][k]+g[k][j] )
							g[i][j] = g[i][k]+g[k][j];
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] < +oo )
					g[i][j] /= speed;
		scanf("%s\n",tmp);
		assert( 0 == strcmp("ARRIVALS",tmp) );
		for (;FG && 7==sscanf(buff,"%d:%d %s %d:%d %s %Lf",&h0,&m0,p0,&h1,&m1,p1,&S);) {
			src=s[string(p0)],dst=s[string(p1)];
			if ( !a_star_search(src,60*G(h0,m0,h1,m1)) ) {
				puts("Impossible!");
				continue ;
			}
			printf("PATH FOUND: %8.3Lf ",tail->w), tail->cur_included = true, qtr = out, dump(tail);
			for ( i=0; i<qtr-out; i=j ) {
				for ( j=i+1; j<qtr-out && (out[i]>>1)==(out[j]>>1); ++j );
				if ( out[j-1]&1 ) printf("  %s",ID[out[j-1]>>1].c_str());
				else printf(" !%s",ID[out[j-1]>>1].c_str());
			}
			putchar('\n');
		}
	}
	return 0;
}

