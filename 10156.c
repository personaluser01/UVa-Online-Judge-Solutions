/*
 * 10156. Sala-ma-Sond
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10001
#define S 64
#define valid_cell(x,y) (0<=(x)&&(x)<m&&0<=(y)&&(y)<n)

int id[N],m,n,T,K,g[S][S],yes,
	cx[N],cy[N],nx,ny,row[S],
	dx[] = { 1,-1, 0, 0, -1, 1, 1, -1},
	dy[] = { 0, 0, 1,-1, -1,-1, 1,  1};

int dir( char *s ) {
	if ( s[1] == '\0' ) {
		switch ( 0[s] ) {
			case 'E': return 0;
			case 'W': return 1;
			case 'S': return 2;
			case 'N': return 3;
			default: assert( 0 );
		}
	}
	else {
		if ( strcmp(s,"NW") == 0 )
			return 4;
		if ( strcmp(s,"SW") == 0 )
			return 7;
		if ( strcmp(s,"SE") == 0 )
			return 6;
		if ( strcmp(s,"NE") == 0 )
			return 5;
		assert( 0 );
	}
}

int main() {
	int i,j,k;
	char a[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;4 == scanf("%d %d %d %d",&n,&m,&T,&K) && ++yes; putchar('\n') ) {
		for ( i = 0; i < T; ++i ) {
			scanf("%d",id+i),scanf("%d %d",cy+id[i],cx+id[i]);
			assert( valid_cell(cx[id[i]],cy[id[i]]) );
			g[cx[id[i]]][cy[id[i]]]=yes;
		}
		for ( i = 0; i < K; ++i ) {
			scanf("%d %s",&k,a),j=dir(a),nx=cx[k]+dx[j],ny=cy[k]+dy[j];
			if ( valid_cell(nx,ny)&&g[nx][ny]!=yes )
				g[nx][ny]=yes,g[cx[k]][cy[k]]=0,cx[k]=nx,cy[k]=ny;
		}
#if 1
		memset(row,0,sizeof(row));
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j]==yes && ++row[j] );
		for ( j = 0; j < n; ++j, putchar('\n') ) 
			for ( i = 0; i < m && row[j]; putchar(g[i++][j] == yes ? --row[j],'*':' ') );
#else
		memset(row,0,sizeof(row));
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[i][j]==yes && ++row[i] );
		for ( i = 0; i < m; ++i, putchar('\n') ) 
			for ( j = 0; j < n && row[i]; putchar(g[i][j++] == yes ? --row[i],'*':' ') );
#endif
	}
	return 0;
}
