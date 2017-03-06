/*
 * 1103. Ancient Messages
 * status: Accepted
 * TOPIC: floodfill, connected components
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;
#define N 0x200
#define vc(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)
enum { ANKH, WEDJAT, DJED, SCARAB, WAS, AKEHT };

unsigned int
getval( const char ch ) {
	if ( '0' <= ch && ch <= '9' )
		return ch-'0';
    assert( isalpha(ch) );
	return 10+(tolower(ch)-'a');
}

int m,n,cs,cn[256],cc[N][N],seen[N][N],yes,
	dx[] = {-1,0,1,0},K,
	dy[] = {0,-1,0,1},mark;
char g[N][N],cd[256];

void floodfill( int x, int y, const char ch ) {
	int nx,ny,i;
	assert( ch == g[x][y] );
	assert( seen[x][y] != yes );
	for ( seen[x][y] = yes, cc[x][y] = mark, i = 0; i < 4; ++i ) 
		if ( vc(nx=x+dx[i],ny=y+dy[i]) && seen[nx][ny] != yes && g[nx][ny] == ch )
			floodfill(nx,ny,ch);
}

void dfs( int x, int y, const int k ) {
	int i,nx,ny;
	if ( seen[x][y] == yes )
		return ;
    assert( !(g[x][y]=='1'&&cc[x][y]==k) );
	for ( seen[x][y] = yes, i = 0; i < 4; ++i )
		if ( vc(nx=x+dx[i],ny=y+dy[i]) && !(g[nx][ny]=='1'&&cc[nx][ny]==k) && seen[nx][ny] != yes ) 
			dfs(nx,ny,k);
}

int main() {
	int i,j,k,l;
	unsigned int u,v;
	char tmp[0x400];
	const char *e = "ADJKSW";
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	cd[ANKH] = 'A', cd[WEDJAT] = 'J', cd[DJED] = 'D', cd[SCARAB] = 'S', cd[WAS] = 'W', cd[AKEHT] = 'K';
	for(;2==scanf("%d %d",&m,&n)&&(m||n);) {
		printf("Case %d: ",++cs);
        for ( j = 0; j <= (4*n)+1; ++j )
            g[0][j] = g[m+1][j] = '0';
		for ( i = 1; i <= m; ++i ) 
			for ( g[i][0]=g[i][4*n+1]='0', scanf("%s",tmp), k = 0, j = 0; j < n; ++j, ++k ) 
				for ( u = getval(tmp[j]), l = 0; l < 4; ++l )
					g[i][1+(4*k+3-l)] = (((u>>l)&1)+'0');
		n <<= 2, n += 2,  m+=2, memset(cn,0,sizeof cn);
		for ( ++yes, mark = 0, i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( seen[i][j] != yes && g[i][j] == '1' ) 
					floodfill(i,j,'1'), ++mark;
		for ( k = 0; k < mark; ++k ) {
			for ( ++yes, K = 0, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					if ( seen[i][j] != yes && !(g[i][j]=='1'&&cc[i][j]==k) )
						dfs(i,j,k), ++K;
			if ( K == 2 )
				++cn[cd[ANKH]-'A'];
			if ( K == 6 )
				++cn[cd[DJED]-'A'];
			if ( K == 5 )
				++cn[cd[SCARAB]-'A'];
			if ( K == 1 )
				++cn[cd[WAS]-'A'];
			if ( K == 4 )
				++cn[cd[WEDJAT]-'A'];
			if ( K == 3 )
				++cn[cd[AKEHT]-'A'];
            //assert( 1 <= K && K <= 6 );
		}
		for ( i = 0; i <= 5; ++i ) 
			for(;cn[e[i]-'A']--;putchar(e[i]));
		putchar('\n');
	}
	return 0;
}

