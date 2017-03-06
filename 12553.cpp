/*
 * 12553. Countdown
 * TOPIC: bfs
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define N 6
typedef long long i64;

struct cell {
	int m;
	i64 c[N],a,b,res;
	char op;
	cell *p;
	cell( int n, int *v ) {
		m = n;
		for ( int i = 0; i < n; c[i] = v[i], ++i );
	};
	cell() { m = 0; op = '\0'; };
	i64 operator [] ( int i ) const { return c[i]; };
};

bool operator < ( cell &a, cell &b ) {
	if ( a.m == b.m ) {
		for ( int i = 0; i < a.m; ++i )
			if ( a[i] != b[i] )
				return a[i] < b[i];
		return false ;
	}
	return a.m < b.m;
}
bool operator == ( cell &a, cell &b ) {
	return !(a<b||b<a);
}
bool operator != ( cell &a, cell &b ) {
	return !(a==b);
}

struct comp {
	bool operator () ( const cell *a, const cell *b ) const {
		if ( a->m == b->m ) {
			for ( int i = 0; i < a->m; ++i )
				if ( a->c[i] != b->c[i] )
					return a->c[i] < b->c[i];
			return false ;
		}
		return a->m < b->m;
	};
};

queue<cell *> q;
set<cell *,comp> s;
i64 T;
char op[] = {'+','-','*','/'};

void dump( cell *x ) {
	if ( x->op ) {
		dump(x->p);
		printf("%lld %c %lld = %lld\n",x->a,x->op,x->b,x->res);
	}
}

cell *next( cell *x, int i, int j, char op ) {
	int l,k;
	cell *y = new cell();
	switch ( op ) {
		case '+': y->res = (y->a=x->c[i])+(y->b=x->c[j]);
				  y->op = '+';
				  break ;
		case '-': y->res = (y->a=x->c[i])-(y->b=x->c[j]);
				  if ( y->res < 0 ) return NULL;
				  y->op = '-';
				  break ;
		case '*': y->res = (y->a=x->c[i])*(y->b=x->c[j]);
				  y->op = '*';
				  break ;
		case '/': if ( x->c[j]==0 || 0!=(x->c[i]%x->c[j]) )
						 return NULL;
				  y->res = (y->a=x->c[i])/(y->b=x->c[j]);
				  y->op = '/';
				  break ;
		default: assert(0);
	}
	for ( l = 0, k = 0; k < x->m; ++k )
		 if ( k != i && k != j )
			y->c[l++] = x->c[k];
	 y->p = x, y->m = x->m-1, y->c[l++] = y->res, sort(y->c,y->c+y->m);
	 assert( l == y->m );
	 return y;
};

int main() {
	int i,j,k,cs,ts,l;
	i64 res,w,best;
	cell *src,*u,*v,*e;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( src = new cell(), src->m = N, src->op='\0', i = 0; i < N; scanf("%lld",&src->c[i++]) );
		sort(src->c,src->c+N), scanf("%lld",&T), printf("Target: %lld\n",T), s.clear();
		for ( s.insert(src), e=NULL, w=(1LL<<53), src->op='\0', q.push(src); !q.empty(); ) {
			u = q.front(), q.pop();
			if ( u->m == 1 ) {
				if ( labs((*u)[0]-T) < w ) {
					w = labs((*u)[0]-T);
					best = (*u)[0], e = u;
				}
				continue ;
			}
			assert( u->m >= 2 );
			for ( i = 0; i < u->m; ++i )
				for ( j = 0; j < u->m; ++j ) 
					for ( k = 0; i != j && k < 4; ++k )
						if ( (v=next(u,i,j,op[k])) && !s.count(v) ) 
							s.insert(v), q.push(v);
		}
		dump(e), printf("Best approx: %lld\n\n",best);
	}
	return 0;
}

