/*
 * 10864. Predator
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#define MAXR 10000
using namespace std;
typedef long long i64;
#define vc(x,y) (1<=(x)&&(x)<X&&1<=(y)&&(y)<Y)

int compartments,queries,X,Y,
	col[0x400][0x400],scc,
	dx[]={-1,0,1,0},
	dy[]={0,1,0,-1};
i64 xx[9],yy[9],rr[9],ix[0x800],iy[0x800],
	qx[0x400],qy[0x400],card[0x800];
set<i64> sx,sy;
map<i64,int> mx,my;

int inside_which( i64 x, i64 y ) {
	int j;
	for ( j = 0; j < compartments-1; ++j )
		if ( xx[j]< x&&x <= xx[j]+rr[j] )
			if ( yy[j]< y&&y <= yy[j]+rr[j] )
				return j;
	return compartments;
}

void dfs( int x, int y ) {
	int i,j,nx,ny;
	for ( col[x][y] = scc, i = 0; i < 4; ++i ) {
		nx = x+dx[i], ny = y+dy[i];
		if ( !vc(nx,ny) )
			continue ;
		for ( j = 0; j < compartments-1; ++j ) {
			if ( nx == x && mx[xx[j]] < nx && nx <= mx[xx[j]+rr[j]] ) {
				if ( (y<=my[yy[j]] && my[yy[j]]<ny)||(ny<=my[yy[j]] && my[yy[j]]<y) ) {
					//printf("between (%lld,%lld) anlld (%lld,%lld) there is a wall\n",ix[x],iy[y],ix[nx],iy[ny]);
					goto next;
				}
			}
			if ( nx == x && mx[xx[j]] < nx && nx <= mx[xx[j]+rr[j]] ) {
				if ( (y<=my[yy[j]+rr[j]] && my[yy[j]+rr[j]]<ny)||(ny<=my[yy[j]+rr[j]] && my[yy[j]+rr[j]]<y) ) {
					//printf("between (%lld,%lld) anlld (%lld,%lld) there is a wall\n",ix[x],iy[y],ix[nx],iy[ny]);
					goto next;
				}
			}
			if ( ny == y && my[yy[j]] < ny && ny <= my[yy[j]+rr[j]] ) {
				if ( (x<=mx[xx[j]] && mx[xx[j]]<nx)||(nx<=mx[xx[j]] && mx[xx[j]]<x) ) {
					//printf("between (%lld,%lld) anlld (%lld,%lld) there is a wall\n",ix[x],iy[y],ix[nx],iy[ny]);
					goto next;
				}
			}
			if ( ny == y && my[yy[j]] < ny && ny <= my[yy[j]+rr[j]] ) {
				if ( (x<=mx[xx[j]+rr[j]] && mx[xx[j]+rr[j]]<nx)||(nx<=mx[xx[j]+rr[j]] && mx[xx[j]+rr[j]]<x) ) {
					//printf("between (%lld,%lld) anlld (%lld,%lld) there is a wall\n",ix[x],iy[y],ix[nx],iy[ny]);
					goto next;
				}
			}
		}
		/*printf("CAN pass from (%lld,%lld) to (%lld,%lld) with scc = %d\n",ix[x],iy[y],ix[nx],iy[ny],scc);
		j = inside_which(ix[nx],iy[ny]);
		if ( j < compartments-1 )
			printf("THIS is inside rectangle %d\n",j);
			*/
		if ( !col[nx][ny] ) dfs(nx,ny);
		next: continue ;
	}
}

int main() {
	int i,j,k,l,t,low,high,mid,ii,jj,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&compartments) && compartments;) {
		for ( sx.clear(), sy.clear(), i = 0; i < compartments; ++i ) {
			scanf("%lld %lld %lld",&xx[i],&yy[i],&rr[i]);
			sx.insert(--xx[i]), sy.insert(--yy[i]);
			sx.insert(xx[i]+rr[i]), sy.insert(yy[i]+rr[i]);
		}
		i = compartments;
		xx[i] = 0, yy[i] = 0, rr[i] = MAXR, ++compartments;
		sx.insert(xx[i]), sy.insert(yy[i]);
		sx.insert(xx[i]+rr[i]), sy.insert(yy[i]+rr[i]);

		for ( scanf("%d",&queries), k = 0; k < queries; ++k ) {
			scanf("%d %d",&i,&j), qx[k] = i, qy[k] = j;
			i = max(i,1), j = max(j,1);
			i = min(i,MAXR), j = min(j,MAXR);
			qx[k] = i, qy[k] = j;
			// sx.insert(i), sy.insert(j);
		}

		mx.clear(), my.clear(), X = Y = 0;
		for ( set<i64>::iterator it = sx.begin(); it != sx.end(); ++it )
			ix[mx[*it] = X++] = *it;
		for ( set<i64>::iterator it = sy.begin(); it != sy.end(); ++it )
			iy[my[*it] = Y++] = *it;
		for ( i = 1; i < X; ++i )
			for ( j = 1; j < Y; ++j )
				col[i][j] = 0;
		for ( scc = 0, i = 1; i < X; ++i )
			for ( j = 1; j < Y; ++j )
				if ( !col[i][j] ) {
					card[++scc] = 0, dfs(i,j);
				}
		for ( i = 1; i < X; ++i )
			for ( j = 1; j < Y; ++j )
				card[col[i][j]] += (ix[i]-ix[i-1])*(iy[j]-iy[j-1]);
		printf("Case %d:\n",++cs);
		for ( k = 0; k < queries; ++k ) {
			i = qx[k], j = qy[k];
			/*
			i = max(i,1), j = max(j,1);
			i = min(i,MAXR), j = min(j,MAXR);
			*/
			low = 0, high = X-1;
			assert( ix[low] < i );
			assert( i <= ix[high] );
			while ( low+1 != high ) {
				mid = (low+high)/2;
				if ( ix[mid] < i )
					low = mid;
				else high = mid;
			}
			ii = high;
			low = 0, high = Y-1;
			assert( iy[low] < j );
			assert( j <= iy[high] );
			while ( low+1 != high ) {
				mid = (low+high)/2;
				if ( iy[mid] < j )
					low = mid;
				else high = mid;
			}
			jj = high;
			printf("%lld\n",card[col[ii][jj]]);
		}
	}
	return 0;
}

