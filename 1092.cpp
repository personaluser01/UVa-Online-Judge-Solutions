/*
 * 1092. Tracking Bio-Robots
 * TOPIC: coordinate compression
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#define vc(x,y) (0<=(x)&&(x)<mm&&0<=(y)&&(y)<nn)
#define N (0x400<<2)
#include <queue>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define enc(x,y) ((x) | ((y)<<15))
typedef long long i64;
using namespace std;

int m,n,walls,mm,nn,
	dx[] = {-1,0},
	dy[] = {0,-1};
pair<int,int> w[N][2];
set<int> X,Y;
map<int,int> xx,yy;
char g[N][N],dp[N][N];
i64 hx[N],hy[N];

int main() {
	i64 i,j,k,l,t,x,y,nx,ny,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("1092.in","r",stdin);
#endif
	for ( ;3 == scanf("%d %d %d",&n,&m,&walls) && (m||n||walls); ) {
		X.clear(); Y.clear();
		X.insert(0); X.insert(m);
		Y.insert(0); Y.insert(n);
		for ( i = 0; i < walls; ++i ) {
			scanf("%d %d %d %d",&w[i][0].first,&w[i][0].second,&w[i][1].first,&w[i][1].second);
			++w[i][1].first;
			++w[i][1].second;
			X.insert(w[i][0].first);
			X.insert(w[i][1].first);
			Y.insert(w[i][0].second);
			Y.insert(w[i][1].second);
		};
		/*
		top = toadd, k = -2;
		for ( set<int>::iterator it = X.begin(); it != X.end(); k = *it++ ) 
			if ( k >= 0 && k+1 < *it ) *++top = k+1;
		for ( i = 0; i < top-toadd; ++i )
			X.insert(toadd[i+1]);
		*/

		xx.clear(), yy.clear(), mm = nn = 0;
		for ( set<int>::iterator it = X.begin(); it != X.end(); hx[xx[*it] = mm++] = *it, ++it );
		for ( set<int>::iterator it = Y.begin(); it != Y.end(); hy[yy[*it] = nn++] = *it, ++it );
		memset(g,0,sizeof g);
		for ( i = 0; i < walls; ++i ) {
			int jj,jjj,kk,kkk;
			jj = xx[w[i][0].first]+1;
			jjj = xx[w[i][1].first];
			for ( j = jj, k = yy[w[i][1].second]; j <= jjj; ++j )
				g[j][k] = 1;
		}
		/*
		for ( seen[mm-2][nn-2] = yes, head=tail=q,*tail++=enc(mm-2,nn-2); head<tail; ) {
			unsigned int u = *head++;
			x = u&MASK(15), y = u>>15;
			for ( i = 0; i < 2; ++i ) {
				nx = x+dx[i], ny = y+dy[i];
				if ( !vc(nx,ny) || g[nx][ny] == yes || seen[nx][ny] == yes ) continue ;
				seen[nx][ny] = yes, *tail++ = enc(nx,ny);
			}
		}*/
		/*
		for ( k = 0, i = 0; i < mm; ++i )
			for ( j = 0; j < nn; ++j ) {
				if ( processed[i][j] == yes || isopen[i][j] == yes ) {
					processed[i][j] = yes;
					continue ;
				}
				for ( l = i+1; l < mm && isopen[l][j] != yes; ++l ) 
					processed[l][j] = yes;
				k += hx[l-1]-hx[i]+1;
			}
		*/
		/*
		for ( k = 0, j = 1; j < nn-1; ++j )
			for ( i = 1; i < mm-1; ++i ) {
				if ( seen[i][j] == yes || g[i][j] == yes ) continue ;
				//for ( l = i+1; l < mm-1 && seen[l][j] != yes && g[l][j] != yes; ++l ) 
				//	processed[l][j] = yes;
				// printf("[%d] line %d -- %d\n",hy[j]-1,hx[i]-1,hx[l-1]-1);
				//k += (hx[l]-hx[i])*(hy[j+1]-hy[j]);
				// i = l;
				k += (hx[i+1]-hx[i])*(hy[j+1]-hy[j]);
				// printf("[%d] cell %d, contributes [%d,%d]x[%d,%d]\n",hy[j]-1,hx[i]-1,hx[i]-1,hx[i+1]-2,hy[j]-1,hy[j+1]-2);
			}
			*/
		memset(dp,0,sizeof dp);
		dp[mm-1][nn-1] = 1;
		for ( k = 0, i = mm-1; i >= 1; --i )
			for ( j = nn-1; j >= 1; --j ) {
				if ( g[i][j] ) continue ;
				if ( !dp[i][j] )
					k += (hx[i]-hx[i-1])*(hy[j]-hy[j-1]);
				dp[i-1][j] |= dp[i][j];
				dp[i][j-1] |= dp[i][j];
			}
next:
		printf("Case %lld: %lld\n",++cs,k);
	};
	return 0;
}

