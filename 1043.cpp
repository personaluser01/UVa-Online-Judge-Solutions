/*
 * 1043. Crossing Streets
 * TOPIC: Dijkstra, binary search
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#define N 512
#define Q 0x400
#define oo (1LL<<29)
#define vc(x,y) (0<=(x)&&(x)<H&&0<=(y)&&(y)<W)
using namespace std;

int W,H,m,n,sx,sy,A[Q],B[Q],tx,ty;
set<int> X,Y;
set<pair<int,pair<int,int> > > s;
int x[2][N],y[2][N],d[Q][Q];
vector<int> XX,YY;

int getrank( vector<int> &v, int x ) {
	int i,j,k,n = v.size();
	if ( !n ) return -1;
	if ( v[n-1] < x ) return -1;
	if ( v[n-1] == x ) return n-1;
	if ( x < v[0] ) return 0;
	assert( v[0] <= x && x < v[n-1] );
	for(i=0,j=n-1;i+1<j;v[k=(i+j)/2]<=x?(i=k):(j=k));
	return v[i]==x?i:-1;
}

vector<pair<int,int> > r[Q],c[Q];

bool intersection( int a, int b, int c, int d ) { return !(b<=c||d<=a); }

bool along_row_street( int row, int j0, int j1 ) {
	int left  = min(j0,j1),
		right = max(j0,j1),
		i,j,k,n = r[row].size();
	if ( !r[row].size() ) return false;
	if ( r[row][0].first >= right ) return false;
	if ( r[row][n-1].second <= left ) return false;
	assert( r[row][0].first < right );
	if ( intersection(r[row][0].first,r[row][0].second,left,right) )
		return true;
	assert( r[row][0].first < left );
	if ( intersection(r[row][n-1].first,r[row][n-1].second,left,right) )
		return true;
	assert( r[row][n-1].first >= left );
	for(i=0,j=n-1;i+1<j;r[row][k=(i+j)/2].first<left?(i=k):(j=k));
	assert( r[row][i].first < left );
	return intersection(r[row][i].first,r[row][i].second,left,right)||intersection(r[row][j].first,r[row][j].second,left,right);
}

bool along_col_street( int col, int i0, int i1 ) {
	int left  = min(i0,i1),
		right = max(i0,i1),
		i,j,k,n = c[col].size();
	if ( !c[col].size() ) return false;
	if ( c[col][0].first >= right ) return false;
	if ( c[col][n-1].second <= left ) return false;
	assert( c[col][0].first < right );
	if ( intersection(c[col][0].first,c[col][0].second,left,right) )
		return true;
	assert( c[col][0].first < left );
	if ( intersection(c[col][n-1].first,c[col][n-1].second,left,right) )
		return true;
	assert( c[col][n-1].first >= left );
	for(i=0,j=n-1;i+1<j;c[col][k=(i+j)/2].first<left?(i=k):(j=k));
	assert( c[col][i].first < left );
	return intersection(c[col][i].first,c[col][i].second,left,right)||intersection(c[col][j].first,c[col][j].second,left,right);
}

int on_row_street( int x, int y ) {
	int i,j,k,n=r[x].size();
	if ( !r[x].size() ) return 0;
	if ( r[x][0].first > y ) return 0;
	if ( r[x][n-1].second < y ) return 0;
	if ( r[x][n-1].second == y ) return 1;
	if ( r[x][n-1].first <= y ) return 1;
	assert( r[x][0].first <= y );
	assert( r[x][n-1].first > y );
	for(i=0,j=n-1;i+1<j;r[x][k=(i+j)/2].first<=y?(i=k):(j=k));
	return r[x][i].first<=y&&y<=r[x][i].second?1:0;
}

int on_col_street( int x, int y ) {
	int i,j,k,n=c[y].size();
	if ( !c[y].size() ) return 0;
	if ( c[y][0].first > x ) return 0;
	if ( c[y][n-1].second < x ) return 0;
	if ( c[y][n-1].second == x ) return 1;
	if ( c[y][n-1].first <= x ) return 1;
	assert( c[y][0].first <= x );
	assert( c[y][n-1].first > x );
	for(i=0,j=n-1;i+1<j;c[y][k=(i+j)/2].first<=x?(i=k):(j=k));
	return c[y][i].first<=x&&x<=c[y][i].second?1:0;
}

int main() {
	int i,j,k,cs = 0,u,v,l,t,dw,w,left,right;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 && printf("City %d\n",++cs) ) {
		X.clear(), Y.clear(), XX.clear(), YY.clear();
		for ( i = 0; i < n; ++i ) {
			for ( j = 0; j <= 1; ++j ) 
				scanf("%d %d",&x[j][i],&y[j][i]),X.insert(x[j][i]),Y.insert(y[j][i]);
			assert( abs(x[0][i]-x[1][i])+abs(y[0][i]-y[1][i]) );
		}
		scanf("%d %d %d %d",&sx,&sy,&tx,&ty);
		X.insert(sx), X.insert(tx);
		Y.insert(sy), Y.insert(ty);
		XX = vector<int>(X.begin(),X.end());
		YY = vector<int>(Y.begin(),Y.end());
		for ( i = 0; i < n; ++i )
			for ( j = 0; j <= 1; ++j ) {
				assert( -1 != (x[j][i] = getrank(XX,x[j][i])) ); 
				assert( -1 != (y[j][i] = getrank(YY,y[j][i])) );
			}
		sx = getrank(XX,sx), tx = getrank(XX,tx);
		sy = getrank(YY,sy), ty = getrank(YY,ty);
		assert( sx != -1 && sy != -1 && tx != -1 && ty != -1 );
		H = XX.size(), W = YY.size(), s.clear();
		for ( i = 0; i <= H; ++i )
			for ( j = 0; j <= W; d[i][j++] = +oo );
		for ( i = 0; i <= H; ++i ) r[i].clear();
		for ( j = 0; j <= W; ++j ) c[j].clear();
		for ( i = 0; i < n; ++i )
			if ( x[0][i] == x[1][i] ) 
				r[x[0][i]].push_back(make_pair(min(y[0][i],y[1][i]), max(y[0][i],y[1][i])));
			else 
				c[y[0][i]].push_back(make_pair(min(x[0][i],x[1][i]), max(x[0][i],x[1][i])));

		for ( i = 0; i < H; ++i ) {
			sort(r[i].begin(),r[i].end());
			if ( !r[i].size() ) continue ;
			for ( m = 0, left = r[i][0].first, right = r[i][0].second, j = 1; j < (int)r[i].size(); ++i ) {
				if ( right < r[i][j].first ) {
					A[m] = left, B[m++] = right, left = r[i][j].first, right = r[i][j].second;
					continue ;
				}
				if ( r[i][j].second > right )
					right = r[i][j].second;
			}
			A[m] = left, B[m++] = right;
			for ( r[i].clear(), j = 0; j < m; ++j )
				r[i].push_back(make_pair(A[j],B[j]));
		}

	    for ( j = 0; j < W; ++j ) {
			sort(c[j].begin(),c[j].end());
			if ( !c[j].size() ) continue ;
			for ( m = 0, left = c[j][0].first, right = c[j][0].second, i = 1; i < (int)c[j].size(); ++i ) {
				if ( right < c[j][i].first ) {
					A[m] = left, B[m++] = right, left = c[j][i].first, right = c[j][i].second;
					continue ;
				}
				if ( c[j][i].second > right )
					right = c[j][i].second;
			}
			A[m] = left, B[m++] = right;
			for ( c[j].clear(), i = 0; i < m; ++i )
				c[j].push_back(make_pair(A[i],B[i]));
		}

		s.insert(make_pair(0,make_pair(sx,sy))), d[sx][sy] = 0;
		for (;!s.empty();) {
			set<pair<int,pair<int,int> > > :: iterator it = s.begin();
			s.erase(*it), u = it->second.first, v = it->second.second, w = d[u][v];
			for ( i = -1; i <= 1; ++i )
				for ( j = -1; j <= 1; ++j ) {
					if ( !vc(u+i,v+j)||abs(i)+abs(j) != 1 ) continue ;
					if ( !i && along_row_street(u,v,v+j) ) continue ;
					if ( !j && along_col_street(v,u,u+i) ) continue ;
					dw = on_col_street(u+i,v+j)|on_row_street(u+i,v+j);
					if ( d[u+i][v+j] > w+dw ) 
						s.insert(make_pair(d[u+i][v+j]=w+dw,make_pair(u+i,v+j)));
				}
		}
		printf("Peter has to cross %d streets\n",d[tx][ty]);
	}
	return 0;
}

