/*
 * 1382. Distant Galaxy
 * TOPIC: clever neat dp, prefix sums
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define oo (1<<29)
#define N 0x80

int n,a,b;
set<int> X,Y;
map<int,int> mx,my;
int x[N],y[N],g[N][N],yes,
	row[N][N],col[N][N];

int H( int k, int i, int j ) { return col[j][k]-col[i-1][k]; }
int M( int k, int i, int j ) { return row[k][j]-row[k][i-1]; }

int main() {
	int i,j,k,w,mn,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("1382.in","r",stdin);
#endif
	for (;1==scanf("%d",&n) && n>0;) {
		for ( X.clear(), Y.clear(), i = 0; i < n; scanf("%d %d",x+i,y+i), X.insert(x[i]), Y.insert(y[i]), ++i );
		a = b = 0, mx.clear(), my.clear();
		for ( auto &it: X )  mx[it] = ++a;
		for ( auto &it: Y )  my[it] = ++b;
		for ( i = 0; i < n; x[i] = mx[x[i]], y[i] = my[y[i]], ++i );
		memset(g,0,sizeof g);
		for ( i = 0; i < n; ++g[x[i]][y[i]], ++i );
		for ( i = 1; i <= a; ++i )
			for ( j = 1; j <= b; ++j )
				row[i][j] = row[i][j-1]+g[i][j];
		for ( j = 1; j <= b; ++j )
			for ( i = 1; i <= a; ++i )
				col[i][j] = col[i-1][j]+g[i][j];
		for ( w = -oo, i = 1; i <= a; ++i )
			for ( k = i+1; k <= a; ++k )
				for ( mn = 0, j = 1; j <= b; ++j ) {
					w = max(w,M(i,1,j)+M(k,1,j)+H(j,i,k)-g[i][j]-g[k][j]-mn);
					mn = min(mn,M(i,1,j)+M(k,1,j)-H(j,i,k));
				}
		for ( i = 1; i <= a; w = max(M(i++,1,b),w) );
		for ( j = 1; j <= b; w = max(H(j++,1,a),w) );
		printf("Case %d: %d\n",++cs,w);
	}
	return 0;
}


