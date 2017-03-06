/*
 * 10141. Request for Proposal
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-9
#define N 0x400

int m,n,cs,r[N],id[N];
char **prop;
double price[1 << 17];

typedef struct {
	double pr;
	int c,id;
} cell;

int cmp( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	if ( x->c < y->c )
		return 1;
	if ( x->c > y->c )
		return -1;
	if ( fabs(x->pr-y->pr) < tol ) 
		return x->id - y->id;
	return x->pr < y->pr ? -1 : 1;
}

cell *x;

int main() {
	int i,j,k;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;2 == scanf("%d %d\n",&n,&m)&&(m||n);) {
		if ( ++cs > 1 ) putchar('\n');
		prop = (char **)malloc(m*sizeof *prop);
		for ( i = 0; i < m; ++i )
			prop[i] = (char *)malloc(82*sizeof *prop[i]);
		for ( j = 0; j < n; fgets(tmp,sizeof(tmp),stdin), ++j );
		for ( i = 0; i < m; ++i ) {
			fgets(prop[i],82,stdin);
			scanf("%lf %d\n",price+i,r+i);
			for ( j = 0; j < r[i]; fgets(tmp,sizeof(tmp),stdin), ++j );
		}
		assert( x = (cell *)malloc(m*sizeof *x) );
		for ( i = 0; i < m; ++i )
			x[i].id = i, x[i].c = r[i], x[i].pr = price[i];
		qsort(x,m,sizeof *x,cmp);
		printf("RFP #%d\n%s",cs,prop[x[0].id]);
		for ( i = 0; i < m; free(prop[i++]) );
		free(prop), free(x);
	}
	return 0;
}
