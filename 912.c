/*
 * 912. Live From Mars
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
#define N 0x100

int n,dna[2][N],cs,m;
typedef struct { int from,to; } mutation;
mutation mut[1 << 16];

void effect_the_change() {
	int i,t;
	for ( i = 0; i < n; ++i )
		for ( t = 0; t <= 1; ++t )
			if ( mut[m-1].from == dna[t][i] )
				dna[t][i] = mut[m-1].to;
}

int cmp( const void *A, const void *B ) {
	mutation *a = (mutation *)A,
			 *b = (mutation *)B;
	if ( a->from < b->from )
		return -1;
	if ( a->from > b->from )
		return 1;
	return 0;
}

int main() {
	int i,j,k,t,flag;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1 == scanf("%d",&n);) {
		if ( ++cs > 1 ) putchar('\n');
		for ( t = 0; t <= 1; ++t )
			for ( i = 0; i < n; ++i ) {
				scanf("%s",tmp);
				if ( isupper(0[tmp]) )
					dna[t][i] = -(0[tmp]-'A');
				else dna[t][i] = atoi(tmp);
			}
		/*
		 * Changes that HAVE TO be made
		 */
		for ( m = 0, flag = 1; flag; ) 
			for ( flag = 0, i = 0; i < n; ++i ) {
				if ( dna[0][i] <= 0 && dna[1][i] > 0 ) {
					mut[m].from = dna[1][i], mut[m].to = dna[0][i], ++m;
					effect_the_change(), ++flag;
					continue ;
				}
				if ( dna[0][i] > 0 && dna[1][i] <= 0 ) {
					mut[m].from = dna[0][i], mut[m].to = dna[1][i], ++m;
					effect_the_change(), ++flag;
					continue ;
				}
			}
		/*
		 * if there are unsurmountable inconsistencies, goto NO
		 */
		for ( i = 0; i < n; ++i )
			if ( dna[0][i] <= 0 && dna[1][i] <= 0 )
				if ( dna[0][i] != dna[1][i] )
					goto NO;
		puts("YES");
		qsort(mut,m,sizeof *mut,cmp);
		for ( i = 0; i < m; ++i )
			printf("%d %c\n",mut[i].from,-mut[i].to+'A');
		continue ;
		NO: puts("NO");
	}
	return 0;
}

