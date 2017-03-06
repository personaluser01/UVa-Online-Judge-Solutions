/*
 * 11848. Cargo Trains
 * TOPIC: spfa, dijkstra
 * status: in progress
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define MAXE (1<<20)
#define N 0x80
#define oo (1L<<29)
#define tol 1e-13
typedef long long i64;
enum { companyA, companyB };
#include <iostream>
#include <vector>
using namespace std;

int n,qr,to[MAXE],next[MAXE],last[N],heap[2*N],pos[N],cnt,E;
vector<int> lst[2][N][N];
char who[MAXE];
double tau,d[N],cost[MAXE];

void add_arcs( int x, int y, i64 cc, char wh ) {
	int i = E++, j = E++;
	to[i] = y, cost[i] = cc, who[i] = wh, next[i] = last[x], last[x] = i;
	to[j] = x, cost[j] = cc, who[j] = wh, next[j] = last[y], last[y] = j;
	lst[wh][x][y].push_back(i), lst[wh][y][x].push_back(j);
}

void push( int x ) {
	int i,j;
	if ( pos[x]<0 )
		pos[heap[cnt]=x]=cnt,++cnt;
	for ( j=pos[x]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( cnt += (pos[x]=-1) )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

double dijkstra() {
	int i,j,k,x,y;
	for ( x = 0; x < n; d[x++] = +oo, pos[x-1] = -1 );
	for ( cnt = 0, d[0] = 0, push(0); cnt; ) {
		for ( i = last[x = pop()]; i >= 0; i = next[i] ) {
			if ( d[y = to[i]] > d[x]+cost[i] ) 
				d[y] = d[x]+cost[i], push(y);
		}
		for ( y = 0; y < n; ++y )
			if ( x != y ) 
				for ( int l = 0; l < (int)lst[0][x][y].size(); ++l )
					for ( int t = 0; t < (int)lst[1][x][y].size(); ++t )
						if ( d[y] > d[x] + tau*cost[lst[0][x][y][l]]+(1-tau)*cost[lst[1][x][y][t]] )
							d[y] = d[x] + tau*cost[lst[0][x][y][l]]+(1-tau)*cost[lst[1][x][y][t]], push(y);
	}
	return d[n-1];
}

int main() {
	int i,j,k,l,t;
	i64 cc;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;4==scanf("%d %d %d %d",&n,&l,&t,&qr)&&(n+1||l+1||t+1||qr+1);) {
		for ( E = 0, i = 0; i < n; last[i++] = -1 );
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				lst[0][i][j].clear(), lst[1][i][j].clear();
		for (;l--; scanf("%d %d %lld",&i,&j,&cc), add_arcs(i,j,cc,companyA) );
		for (;t--; scanf("%d %d %lld",&i,&j,&cc), add_arcs(i,j,cc,companyB) );
		for ( ;qr-- && 1 == scanf("%lf",&tau); ) 
			printf("%.lf\n",dijkstra()+tol);
	}
	return 0;
}

