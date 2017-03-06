/*
 * 10574. Counting Rectangles
 * TOPIC: sorting
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<13)

typedef struct { int x[2]; } cell ;
cell c[N];
int n,tt[2][N],list[2][N],len[N],ans,
	left[N],right[N],m;

int cmp( const void *a, const void *b ) {
	int *x = (int *)a,
		*y = (int *)b;
	if ( *x == *y ) return  0;
	if ( *x < *y )  return -1;
	return 1;
}

int cmp01( const void *a, const void *b ) {
	cell *p = (cell *)a,
		 *q = (cell *)b;
	if ( p->x[0] == q->x[0] ) 
		return p->x[1]-q->x[1];
	return p->x[0]-q->x[0];
}

int main() {
	int i,j,k,l,t,cs = 0,ts,low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n) && printf("Case %d: ",++cs); printf("%d\n",ans) ) {
		for ( i = 0; i < n; ++i )
			scanf("%d %d",c[i].x,c[i].x+1),tt[0][i]=c[i].x[0],tt[1][i]=c[i].x[1];
		for ( t = 0; t <= 1; ++t ) 
			for ( qsort(tt[t],n,sizeof *tt[t],cmp), len[t] = 0, i = 0; i < n; list[t][len[t]++] = tt[t][i], i = j )
				for ( j = i+1; j < n && tt[t][i] == tt[t][j]; ++j );
		for ( t = 0; t <= 1; ++t ) 
			for ( i = 0; i < n; ++i ) 
				if ( list[t][low = 0] == c[i].x[t] ) c[i].x[t] = 0;
				else {
					assert( c[i].x[t] <= list[t][len[t]-1] );
					for ( high = len[t]-1; low+1 < high; )
						if ( list[t][mid = (low+high)/2] < c[i].x[t] )
							low = mid;
						else high = mid;
					assert( c[i].x[t] == list[t][high] );
					c[i].x[t] = high;
				}
		qsort(c,n,sizeof *c,cmp01);
		for ( m = 0, i = 0; i < n; right[m++] = j-1, i = j )
			for ( left[m] = i, j = i+1; j < n && c[j].x[0] == c[i].x[0]; ++j );
		for ( i = 0; i < m; ++i )
			for ( j = left[i]; j <= right[i]-1; ++j )
				assert( c[j].x[0] == c[j+1].x[0] && c[j].x[1] <= c[j+1].x[1] );
		/*
		for ( i = 0; i < m; ++i )
			printf("[%d] %d %d\n",i,left[i],right[i]);
		*/
		for ( ans = 0, i = 0; i < m; ++i )
			for ( j = i+1; j < m; ++j, ans += t*(t-1)/2 ) 
				for ( t = 0, k = left[i], l = left[j]; k <= right[i] && l <= right[j]; ) {
					for ( ;l <= right[j] && c[l].x[1] < c[k].x[1]; ++l );
					if ( l <= right[j] && c[l].x[1] == c[k].x[1] ) ++t, ++k;
					for( ;k <= right[i] && l <= right[j] && c[k].x[1] < c[l].x[1]; ++k );
					assert( l == right[j]+1 || k == right[i]+1 || c[k].x[1] >= c[l].x[1] );
				}
	}
	return 0;
}

