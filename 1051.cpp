/*
 * 1051. Bipartite Numbers
 * TOPIC: DP
 * status: Accepted
 */
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N (1<<17)
#define D 10
using namespace std;
typedef long long i64;

class Soln {
	public: 
			i64 m,s,n,t;
	Soln( i64 a, i64 b, i64 c, i64 d ) { m = a, s = b, n = c, t = d; }
	bool operator < ( const Soln &b ) {
		if ( m+n != b.m+b.n )
			return m+n < b.m+b.n;
		assert ( m+n == b.m+b.n );
		if ( s != b.s )
			return s < b.s;
		assert ( s == b.s );
		if ( m != b.m ) 
			return s < b.t;
		assert( m == b.m );
		return t < b.t;
	}
};

class Soln *best;
i64 z[N],deg[N],x,A,B,xlen;
int seen[N],yes;

bool is_suitable( i64 m, i64 s, i64 n, i64 t ) {
	i64 y,i;
	if ( m+n > xlen ) return true ;
	if ( m+n < xlen ) return false ;
	//return (z[m]*deg[n]*s+z[n]*t)>x;
	for ( y=0,i = 0; i < m; ++i )
		y=10*y+s;
	for ( i=0; i < n; ++i )
		y=10*y+t;
	return y>x;
}

int main() {
	i64 i,j,k,l,t,curlen;
	bool ok;
	Soln *e;
	for(;1==scanf("%lld",&x)&&x>0;printf("%lld: %lld %lld %lld %lld\n",x,best->m,best->s,best->n,best->t)){
		/*for(seen[deg[0]=(1%x)]=++yes,A=1;seen[deg[A]=(deg[A-1]*10)%x]!=yes;seen[deg[A++]]=yes);
		for(seen[z[0]=0]=++yes,B=1;seen[z[B]=(z[B-1]*10+1)%x]!=yes;seen[z[B++]]=yes);*/
		for ( z[0]=0,deg[0]=(1%x), i = 1; i < N; ++i ) {
			z[i] = (z[i-1]*10+1)%x;
			deg[i] = (deg[i-1]*10)%x;
		}
		for(xlen=0,k=x;k;k/=10,++xlen);
		for(best=new Soln(N,9LL,N,8LL),ok=false,curlen=xlen;curlen<N&&!ok;++curlen)
			// for ( l = max(1LL,curlen-A); l <= curlen-1 && l < B && !ok; ++l )
			for ( l = x%10||curlen<=20?1:curlen-20; l <= curlen-1; ++l )
				for ( i = 1; i < D; ++i )
					for ( t = curlen-l, j = 0; j < D; ++j )
						if ( i != j ) {
							if ( !is_suitable(l,i,t,j) ) continue ;
							if ( ((k=((z[l]*deg[t]*i)%x)),(k+=z[t]*j),(k%=x)) ) continue ;
							e = new Soln(l,i,t,j);
							if ( *e  < *best ) { delete best, best = e, ok = true ; }
							else delete e;
						}
	}
	return 0;
}

