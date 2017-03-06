/*
 * 11165. Galactic Travel
 * TOPIC: bfs, sqrt decomposition, interval union, blocks
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#define SH (17)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define MAXE (1<<21)
#define MAXN (1<<SH)
#define N MAXN
#define MAXB 0x400
#define oo (1<<29)
using namespace std;
typedef unsigned long long u64;

int n,m,last[MAXN],_next[MAXE],E,src,dst,BS,p[MAXN],
	queue[MAXN],*head,*tail,seen[N],yes,d[N]; 
bool block[MAXB],b[MAXB][MAXB];
u64 edge[MAXE];
vector<pair<int,int> > segments, vec[N];

void add_arcs( int x, int i, int j ) {
	int k = E++;
	edge[k] = ((u64)i|(((u64)j)<<SH)), _next[k] = last[x], last[x] = k;
}

void occupy( int i, int j ) {
	int bi = i/BS, bj = j/BS;
	for ( int k = bi+1; k <= bj-1; block[k++] = true );
	for ( int k = (i%BS); k < BS; b[bi][k++] = true );
	for ( int k = 0; k <= (j%BS); b[bj][k++] = true );
}

void mark( int t ) {
	for ( int i = 0; i < BS; ++i )
		if ( !b[t][i] )
			return ;
	block[t] = true ;
}

void dump( int x ) {
	if ( x != src ) dump(p[x]);
	printf("%d\n",x);
}

int main() {
	int i,j,k,cs = 0,ts,x,y,z,left,right,by,bz,nx;
#ifndef ONLINE_JUDGE
	freopen("11165.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && printf("Case #%d: ",++cs); ) {
		for ( E = 0, scanf("%d %d",&n,&m), i = 0; i < n; vec[i].clear(), last[i++] = -1 );
		for ( ;m-- && 3 == scanf("%d %d-%d",&x,&i,&j); vec[x].push_back(make_pair(i,j)) );
		for ( scanf("%d %d",&src,&dst), x = 0; x < n; ++x ) {
			sort(vec[x].begin(),vec[x].end()), segments.clear();
			for ( left = +oo, right = -oo, i = 0; i < (int)vec[x].size(); ++i ) {
				if ( right < vec[x][i].first ) {
					if ( left <= right ) 
						segments.push_back(make_pair(left,right));
					left = vec[x][i].first, right = vec[x][i].second;
				}
				else if ( right < vec[x][i].second )
					right = vec[x][i].second;
			}
			if ( left <= right )
				segments.push_back(make_pair(left,right));
			for ( y = 0, i = 0; i < (int)segments.size(); ++i, y = right+1 ) {
				left = segments[i].first, right = segments[i].second;
				if ( y < left && left < n ) add_arcs(x,y,left-1);
			}
			if ( y < n ) add_arcs(x,y,n-1);
		}
		for ( BS = (int)(sqrt(n)), i = 0; i < n/BS+1; block[i++] = false )
			for ( j = 0; j < BS; b[i][j++] = false );
		for ( head = tail = queue, seen[*tail++=src]=++yes, b[src/BS][src%BS]=true,mark(src/BS), p[src] = -1, d[src] = 0; head < tail && seen[dst] != yes; ) {
			for ( i = last[x = *head++]; i >= 0; i = _next[i] ) {
				y = (edge[i]&MASK(SH)), z = (edge[i]>>SH);
				assert( y <= z );
				by = y/BS, bz = z/BS;
				for ( j = by+1; j <= bz-1; block[j++] = true )
					for ( k = 0; k < BS && !block[j]; ++k )
						if ( !b[j][k] ) {
							assert( seen[j*BS+k] != yes );
							b[j][k] = true, seen[*tail++=nx=j*BS+k]=yes, d[nx]=d[x]+1, p[nx]=x;
						}
				for ( k = (y%BS); k < BS && !block[by] && by*BS+k <= z; ++k )
					if ( !b[by][k] ) {
						assert( seen[by*BS+k] != yes );
						b[by][k]=true, seen[*tail++=nx=by*BS+k]=yes, d[nx]=d[x]+1, p[nx]=x;
					}
				mark(by);
				for ( k = (by<bz?0:y%BS); k <= (z%BS) && !block[bz]; ++k )
					if ( !b[bz][k] ) {
						assert( seen[bz*BS+k] != yes );
						b[bz][k]=true, seen[*tail++=nx=bz*BS+k]=yes, d[nx]=d[x]+1, p[nx]=x;
					}
				mark(bz);
			}
		}
		if ( seen[dst] == yes )
			printf("%d\n",d[dst]);
		else puts("Impossible");
	}
	return 0;
}


