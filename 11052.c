/*
 * 11052. Economic Phone Calls
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
#define N 0x400
#define oo 0xfffffffful
typedef long long i64;

typedef struct{int mm,dd,hh,mi,keep,idx,year;i64 val;}entry;
entry e[N];
int n;
unsigned int z[N][N],w;

int cmp( const void *a, const void *b ) {
	entry *x = (entry *)a,
		  *y = (entry *)b;
	/*
	if ( x->val == y->val )
		return 0;
	return x->val < y->val ? -1 : 1;
	*/
	if ( x->mm == y->mm ) {
		if ( x->dd == y->dd ) {
			if ( x->hh == y->hh ) {
				if ( x->mi == y->mi )
					return 0;
				return x->mi < y->mi ? -1 : 1;
			}
			return x->hh < y->hh ? -1 : 1;
		}
		return x->dd < y->dd ? -1 : 1;
	}
	return x->mm < y->mm ? -1 : 1;
}

unsigned int 
min(unsigned int x,unsigned int y) 
{return x<y?x:y;}

int main() {
	int i,j,k,l,t;
	char tmp1[0x400],tmp2[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n) && n; printf("%u\n",w) ) {
		for ( i = 1; i <= n; ++i ) {
			scanf("%d:%d:%d:%d %s %s",&e[i].mm,&e[i].dd,&e[i].hh,&e[i].mi,tmp1,tmp2);
			/*printf("%02d:%02d:%02d:%02d\n",e[i].mm,e[i].dd,e[i].hh,e[i].mi);*/
			e[i].keep = (0[tmp2]=='+'); e[i].idx = i;
			/*e[i].val = e[i].mm*31LL*24LL*60LL + e[i].dd*24LL*60LL + e[i].hh*60LL + e[i].mi;*/
		}
		for ( k = n+1, j = n; j >= 1; j = i ) 
			for ( e[j].year = k--, i = j-1; i >= 1 && cmp(e+i,e+i+1) < 0; e[i--].year = e[j].year );
		for ( i = 0; i <= n+1; ++i )
			for ( j = 0; j <= n+1; ++j )
				z[i][j] = +oo;

		e[n+1].year = e[n].year, e[n+1].mm = 13, e[n+1].dd = 32, e[n+1].hh = 24, e[n+1].mi = 60;
		for ( i = 1; i <= n; ++i )
			assert( cmp(e+i,e+n+1) < 0 );
		z[n][n] = 1;
		if ( !e[n].keep ) z[n][n+1] = 0;

		for ( i = n-1; i >= 1; --i ) {
			if ( e[i].keep ) {
				for ( j = i+1; j <= n+1; ++j )
					if ( z[i+1][j] < +oo ) {
						if ( cmp(e+i,e+j) < 0 && e[i].year == e[j].year ) 
							z[i][i] = min(z[i][i],z[i+1][j]+1);
						if ( cmp(e+i,e+j) >= 0 && e[i].year+1 == e[j].year )
							z[i][i] = min(z[i][i],z[i+1][j]+1);
					}
				continue ;
			}
			for ( j = i+1; j <= n+1; ++j )
				if ( z[i+1][j] < +oo ) {
					if ( cmp(e+i,e+j) < 0 && e[i].year == e[j].year ) 
						z[i][i] = min(z[i][i],z[i+1][j]+1);
					if ( cmp(e+i,e+j) >= 0 && e[i].year+1 == e[j].year )
						z[i][i] = min(z[i][i],z[i+1][j]+1);
				}
			for ( j = i+1; j <= n+1; ++j )
				z[i][j] = z[i+1][j];
		}
		for ( w = +oo, j = 1; j <= n+1; ++j )
			w = min(w,z[1][j]);
	}
	return 0;
}

