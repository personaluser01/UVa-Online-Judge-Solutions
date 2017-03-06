/*
 * 10448. Unique World
 * TOPIC: dp
 * status: 
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
#include <set>
#include <queue>
using namespace std;
#define N 0x40
#define oo 0xfffffffful
#define M (100100)
#define bubble (swap(pos[heap[i]],pos[heap[j]]),swap(heap[i],heap[j]))

queue<int> q;
bool precalc[N][N];
int n,m,g[N][N],p[N][N],heap[M],pos[M/2],cn;
vector<pair<int,int> > adj[N],v[N][N];
unsigned int d[N][N],z[M/2],dp[N][M/2];

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cn]=x]=cn, ++cn;
	for ( j = pos[x]; j && z[heap[i=(j-1)>>1]] > z[heap[j]]; bubble, j = i );
}

int pop() {
	int x = *heap,i,j;
	if ( (pos[x]=-1,--cn) )
		pos[heap[0]=heap[cn]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cn; bubble ) {
		if ( j < cn-1 && z[heap[j+1]] < z[heap[j]] ) ++j;
		if ( z[heap[i]] <= z[heap[j]] ) break ;
	}
	return x;
}

void dump( int src, int dst, int x ) {
	if ( x == src ) 
		return ;
	assert( p[src][x] != -1 );
	dump(src,dst,p[src][x]);
	assert( g[p[src][x]][x] < (1<<29) );
	v[src][dst].push_back(make_pair(x,g[p[src][x]][x]));
}

bool f( int src, int dst, int diff, int *res ) {
	vector<int> c;
	set<pair<unsigned int,int> > s;
	set<pair<unsigned int,int> >::iterator it;
	int i,j,k,t,total = 0;
	if ( diff&1 ) {
		return false;
	}
	diff >>= 1;

	for ( i = 0; i <= n; ++i )
		for ( k = 0; k <= diff; ++k )
			dp[i][k] = +oo;
	set<int> e,h[2];
	set<int> :: iterator jt,l[2];
	e.clear();
	for ( c.clear(), cn = 0, i = 0; i+1 < (int)v[src][dst].size(); ++i )
		e.insert(v[src][dst][i].second);
	for ( c.clear(), jt = e.begin(); jt != e.end(); ++jt )
		c.push_back(*jt);

	/*
	n = c.size();
	for ( dp[0][0] = 0, i = 0; i <= n; ++i )
		for ( k = 0; k <= diff; ++k )
			dp[i][k] = +oo;
	for ( dp[0][0] = 0, t = 0, h[t].insert(0), i = 0; i < n; ++i )
		for ( t ^= 1, h[t].clear(), l[t^1] = h[t^1].begin(); l[t^1] != h[t^1].end(); ++l[t^1]  )
			if ( dp[i][k=*l[t^1]] < +oo )
				for ( j = 0; j*c[i]+k <= diff; ++j )
					if ( dp[i+1][j*c[i]+k] > dp[i][k]+j )
						dp[i+1][j*c[i]+k] = dp[i][k]+j, h[t].insert(j*c[i]+k);
	if ( dp[n][diff] == +oo ) {
		return false;
	}
	*res = dp[n][diff]*2;
	return true;
	*/

	for ( k = 0; k <= diff; ++k )
		z[k] = +oo, pos[k] = -1;
	for ( z[0]=0, push(0); cn;) {
		for ( k = pop(), jt = e.begin(); jt != e.end() && k != diff; ++jt ) 
			for ( j = 0; j*(*jt)+k <= diff; ++j )
				if ( z[j*(*jt)+k] > z[k]+j )
					z[j*(*jt)+k]=z[k]+j,push(j*(*jt)+k);
		if ( k == diff ) break ;
	}
	if ( z[diff] < +oo ) {
		*res = z[diff]*2;
		return true;
	}
	return false;
}

int main() {
	int i,j,k,l,ts,qr,diff;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&n,&m);
		for ( i = 0; i < n; adj[i++].clear() );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				g[i][j]=(1<<29),p[i][j]=-1;
		for ( l = m; l--; ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			adj[i].push_back(make_pair(j,k));
			adj[j].push_back(make_pair(i,k));
			g[i][j]=g[j][i]=min(g[i][j],k),p[i][j]=i;
		}
		for ( i = 0; i < n; ++i )
			p[i][i] = i, g[i][i] = 0;
		memset(d,0xff,sizeof d);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j] < (1<<29) )
					d[i][j] = g[i][j], p[i][j] = i;
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n && i != k; ++j )
					if ( k != j && d[i][k] < +oo && d[k][j] < +oo )
						if ( (d[i][j]=min(d[i][j],d[i][k]+d[k][j]))==d[i][k]+d[k][j] )
							p[i][j] = p[k][j];
		/*
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( i != j ) {
					v[i][j].clear();
					if ( d[i][j] < +oo )
						dump(i,j,j);
				}
				*/
		memset(precalc,0,sizeof precalc);
		for ( scanf("%d",&qr); qr--; ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			if ( k == d[i][j] ) {
				if ( !precalc[i][j] ) dump(i,j,j), precalc[i][j] = true;
				printf("Yes %lu\n",v[i][j].size());
				continue ;
			}
			if ( k < d[i][j] ) {
				puts("No");
				continue ;
			}
			diff = k-d[i][j];
			if ( !precalc[i][j] ) dump(i,j,j), precalc[i][j] = true;
			if ( f(i,j,diff,&k) ) {
				printf("Yes %lu\n",v[i][j].size()+k);
				continue ;
			}
			puts("No");
		}
		if ( ts ) putchar('\n');
	}
    return 0;
}



