/*
 * 11902. Dominator
 * TOPIC: dfs, bottleneck vertices
 * status: Accepted
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define N 0x80

int g[N][N],seen[N],yes,dominates[N][N],n;
bool reachable[N];

	void traverse( int x ) {
		if ( reachable[x] ) return ;
		reachable[x] = true;
		for ( int y = 0; y < n; ++y )
			if ( g[x][y] == 1 )
				traverse(y);
	}
	void dfs( int x, int L ) {
		if ( x == L || seen[x] == yes ) return ;
		seen[x] = yes;
		for ( int y = 0; y < n; ++y )
			if ( g[x][y] && seen[y] != yes )
				dfs(y,L);
	}
	void go() {
		int i,j,k,l,ts,cs = 0;
		string s;
		for ( scanf("%d",&ts); ts-- > 0; ) {
			printf("Case %d:\n",++cs), scanf("%d",&n);
			for ( i = 0; i < n; ++i ) 
				for ( reachable[i] = false, j = 0; j < n; ++j )
					scanf("%d",&g[i][j]), dominates[i][j] = 0;
			for ( traverse(0), i = 0; i < n; ++i )
				if ( reachable[i] ) {
					++yes; dfs(0,i), dominates[i][i] = true;
					for ( j = 0; j < n; ++j )
						if ( reachable[j] && seen[j] != yes )
							dominates[i][j] = true;
				}
			s = string("+");
			for ( j = 0; j < 2*n-1; ++j ) s += string("-");
			s += string("+");
			for ( i = 0; i < n; ++i ) {
				printf("%s\n",s.c_str());
				for ( j = 0; j < n; ++j ) {
					putchar('|');
					if ( dominates[i][j] )
						putchar('Y');
					else 
						putchar('N');
				}
				puts("|");
			}
			printf("%s\n",s.c_str());
		}
	}

int main() {
	go();
	return 0;
}

