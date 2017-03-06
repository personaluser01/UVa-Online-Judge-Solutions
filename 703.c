/*
 * Triple Ties
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
#define N 0x80

int n,a[N][N],m,wins[N],K;
int c [50000][3];

void add( int i, int j, int k ) { c[K][0] = i, c[K][1] = j, c[K][2] = k, ++K; }

typedef struct {int x,score;} team;

team t[N];

int cmp( const void *A, const void *B ) {
	team *a = (team *)A,
		 *b = (team *)B;
	if ( a->score == b->score )
		return a->x < b->x ? -1 : 1;
	return a->score > b->score?-1:1;
}

int lex_larger( int i, int j ) {
	int k;
	for ( k = 0; k < 3; ++k )
		if ( c[i][k] != c[j][k] )
			break ;
	return k<3 && c[i][k]>c[j][k];
}

void xchg( int *a, int *b ) {
	int c = *a;
	*a = *b, *b = c;
}

int main() {
	int i,j,k,w;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) ) {
		for ( i = 0; i < n; ++i )
			for ( wins[i] = 0, j = 0; j < n; ++j )
				scanf("%d",&a[i][j]), wins[i] += a[i][j];
		for ( i = 0, w = -1; i < n; ++i )
			if ( wins[i] > w )
				w = wins[i];
		for ( K = 0, i = 0; i < n; ++i )
			/*if ( wins[i] == w )*/
			for ( j = 0; j < n; ++j )
				/*if ( wins[j] == w )*/
				for ( k = 0; k < n; ++k )
					if ( 1||wins[k] == w ) {
						if ( ((i>j&&j>k)||(i<j&&j<k))&&(a[i][j]+a[j][k]+a[k][i]==3) )
							add(i,j,k);
						else if ( (i<j&&j<k) && (a[i][j]+a[j][k]+a[k][j]+a[j][i]+a[k][i]+a[i][k])==0 )
							add(i,j,k);
					}
		printf("%d\n",K);
		if ( K ) {
			for ( j = 1; j;)
				for ( i = 0, j = 0; i < K-1; ++i )
					if ( lex_larger(i,i+1) ) {
						for ( ++j, k = 0; k < 3; ++k )
							xchg(&c[i][k],&c[i+1][k]);
					}
		}
		for ( i = 0; i < K; ++i ) {
			for ( j = 0; j < 2; ++j )
				printf("%d ",c[i][j]+1);
			printf("%d\n",c[i][j]+1);
		}

		/*
		for ( i = 0; i < n; ++i ) t[i].x = i, t[i].score = wins[i];
		qsort(t,n,sizeof *t,cmp);
		for ( k = t[0].score, i = 1; i < n && t[i].score == k; ++i );
		for ( K = 0, m = i, i = 0; i < m; ++i )
			for ( j = i+1; j < m; ++j )
				for ( k = j+1; k < m; ++k ) {
					if ( a[t[i].x][t[j].x] == 0 && a[t[i].x][t[k].x] == 0 && a[t[k].x][t[j].x] == 0 ) {
						assert( t[i].x < t[j].x );
						assert( t[j].x < t[k].x );
						add(t[i].x,t[j].x,t[k].x);
						continue ;
					}
					if ( a[t[i].x][t[j].x] && a[t[j].x][t[k].x] && a[t[k].x][t[i].x] ) {
						add(t[i].x,t[j].x,t[k].x);
						continue ;
					}
					if ( a[t[k].x][t[j].x] && a[t[j].x][t[i].x] && a[t[i].x][t[k].x] ) {
						add(t[k].x,t[j].x,t[i].x);
						continue ;
					}
				}
		printf("%d\n",K);
		if ( K ) {
			for ( j = 1; j;)
				for ( i = 0, j = 0; i < K-1; ++i )
					if ( lex_larger(i,i+1) ) {
						for ( ++j, k = 0; k < 3; ++k )
							xchg(&c[i][k],&c[i+1][k]);
					}
		}
		for ( i = 0; i < K; ++i ) {
			for ( j = 0; j < 2; ++j )
				printf("%d ",c[i][j]+1);
			printf("%d\n",c[i][j]+1);
		}
		*/
	}
	return 0;
}
