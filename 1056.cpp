/*
 * 1056. Degrees of Separation
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
using namespace std;
#define N 0x40
#define oo (1 << 29)

int n,m,V,d[N][N],w;
map<string,int> e;
bool g[N][N],ok;

int main() {
	int i,j,k,cs = 0;
	string tmp1,tmp2;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d",&n,&m) && (m||n);) {
		memset(g,0,sizeof g);
		for ( V = 0, e.clear(), k = 0; k < m; ++k ) {
			cin >> tmp1 >> tmp2;
			if ( e.find(tmp1) == e.end() )
				e[tmp1] = V++;
			if ( e.find(tmp2) == e.end() )
				e[tmp2] = V++;
			i = e[tmp1], j = e[tmp2];
			g[i][j] = g[j][i] = true;
		}
		for ( i = 0; i < n; ++i )
			for ( d[i][i] = 0, j = 0; j < n; ++j )
				if ( i != j && g[i][j] )
					d[i][j] = 1;
				else d[i][j] = +oo;
		for ( i = 0; i < n; ++i ) d[i][i] = 0;
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( d[i][k] < +oo && d[k][j] < +oo )
						if ( d[i][j] > d[i][k]+d[k][j] )
							d[i][j] = d[i][k]+d[k][j];
		for ( w = -1, ok = true, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( d[i][j] < +oo && d[i][j] > w )
					w = d[i][j];
				else if ( d[i][j] == +oo ) 
					ok = false;
		printf("Network %d: ",++cs);
		if ( !ok ) puts("DISCONNECTED");
		else {
			printf("%d\n",w);
		}
		puts("");
	}
	return 0;
}

