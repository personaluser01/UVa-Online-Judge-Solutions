/*
 * 11283. Playing Boggle
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define M 0x80
#define L 0x20
#define N 0x10
#define vc(i,j) (0<=(x)&&(x)<4&&0<=(y)&&(y)<4)

int ts,n,m,score[L],used[N][N],len[M],yes;
char g[N][N],word[M][L];

int f( const int idx, int x, int y, int matched ) {
	int i,j,k,nx,ny;
	if ( matched == len[idx] )
		return score[matched];
	assert( matched < len[idx] );
	for ( i = -1; i <= 1; ++i )
		for ( j = -1; j <= 1; ++j ) {
			if ( abs(i)+abs(j) == 0)
				continue ;
			nx = x+i, ny = y+j;
			if ( !vc(nx,ny) )
				continue ;
			if ( used[nx][ny] == yes )
				continue ;
			if ( g[nx][ny] != word[idx][matched] )
				continue ;
			used[nx][ny] = yes;
			if ( k = f(idx,nx,ny,matched+1) ) {
				used[nx][ny] = 0;
				return k;
			}
			used[nx][ny] = 0;
		}
	return 0;
}

int h( const int idx ) {
	int i,j,k;
	for ( ++yes, i = 0; i < 4; ++i )
		for ( j = 0; j < 4; ++j )
			if ( g[i][j] == word[idx][0] ) {
				used[i][j] = yes;
				if ( k = f(idx,i,j,1) )
					return k;
				used[i][j] = 0;
			}
	return 0;
}

int main() {
	int i,j,k,T,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	score[3]=score[4]=1,score[5]=2,score[6]=3,score[7]=5,score[8]=11;
	for ( k = 9; k < L; ++k ) score[k] = 11;
	for ( scanf("%d",&ts); ts--; ) {
		for ( i = 0; i < 4; ++i )
			scanf("%s",g[i]);
		for ( T = 0, scanf("%d",&m), i = 0; i < m; ++i ) 
			scanf("%s",word[i]), len[i] = strlen(word[i]), T += h(i);
		printf("Score for Boggle game #%d: %d\n",++cs,T);
	}
	return 0;
}

