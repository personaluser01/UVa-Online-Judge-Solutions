/*
 * 431. Trial of the Millenium
 * TOPIC: dp
 * status:
 */
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define MAXT BIT(9)
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#define oo 0xfffffffful
#define S 8
#define BIT(k) (1UL<<(k))
#define MASK(k) (BIT(k)-1UL)
#define enc(x,y) ((x)|((y)<<S))

int empty( char *ptr ) {
	for (;*ptr && *ptr != '\n' && isspace(*ptr); ++ptr );
	return !*ptr || *ptr == '\n';
}

int m,T,n,score[N],tm[N],TT,idx[N];
char buff[0x400],*ptr,
	 desc[N][0x400];
unsigned int z[N][MAXT],way[N][MAXT];

int cmp( const void *a, const void *b ) {
	int *x = (int *)a,
		*y = (int *)b;
	if ( tm[*x] == tm[*y] ) {
		if ( score[*x] == score[*y] ) {
			return strcmp(desc[*x],desc[*y]);
		}
		return score[*x]>score[*y]?-1:1;
	}
	return tm[*x]<tm[*y]?-1:1;
}

void dump( int k, int t ) {
	int pk,pt;
	if ( t == 0 || k == 0 ) return ;
	pk = (way[k][t]&MASK(S)), pt = (way[k][t]>>S);
	if ( pt != t ) {
		/*printf("%3d %6d   %s\n",score[k],tm[k],desc[k]);*/
		idx[m++] = k;
	}
	dump(pk,pt);
}

unsigned int max ( unsigned int x, unsigned int y ) { return x<y?y:x; }

unsigned int calc_z( int k, int t ) {
	if ( z[k][t] < +oo ) return z[k][t];
	if ( k == 0 || t == 0 ) return z[k][t] = 0;
	assert( t >= 1 );
	assert( k >= 1 );
	z[k][t] = calc_z(k-1,t), way[k][t] = enc(k-1,t);
	if ( tm[k] <= t && calc_z(k-1,t-tm[k]) < +oo ) {
		if ( z[k][t] < z[k-1][t-tm[k]]+score[k] )
			z[k][t] = z[k-1][t-tm[k]]+score[k], way[k][t] = enc(k-1,t-tm[k]);
	}
	return z[k][t];
}

typedef struct {
	int score,t;
	char d[0x80];
} cell;

int cm( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	if ( x->t == y->t ) {
		if ( x->score == y->score ) {
			return strcmp(x->d,y->d);
		}
		return x->score>y->score?-1:1;
	}
	return x->t<y->t?-1:1;
}

cell c[N];

int main() {
	int i,j,k,l,cs = 0,ts;
	unsigned int w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts), FG; ts--; ) {
		for ( k = (1<<29), sscanf(FG,"%d",&T), n=0; FG && !empty(ptr); ++n ) {
			assert( 3 == sscanf(ptr,"%d %d %[^\n]",score+n+1,tm+n+1,desc[n+1]) );
			if ( tm[n+1] < k ) k = tm[n+1];
			c[n+1].score = score[n+1], c[n+1].t = tm[n+1], strcpy(c[n+1].d,desc[n+1]);
		}
		/*
		qsort(c+1,n,sizeof *c,cm);
		for ( i = 1; i <= n; ++i )
			tm[i] = c[i].t, score[i] = c[i].score, strcpy(desc[i],c[i].d);
		*/
		for ( i = 0; i <= n; ++i )
			for ( j = 0; j <= T; z[i][j++] = +oo );
		w = calc_z(n,T);
		if ( w == 0 ) {
			puts("There is not enough time to present any evidence. Drop the charges.");
			if ( ts ) putchar('\n');
			continue ;
		}
		/*
		for ( w = 0, j = 0; j <= T; ++j )
			for ( i = 0; i <= n; ++i )
				if ( calc_z(i,j) < +oo && calc_z(i,j) > w ) 
					k = i, l = j, w = calc_z(i,j);
		*/
		puts("Score  Time  Description");
		puts("-----  ----  -----------");
		for ( TT = 0; TT <= T && calc_z(n,TT) != w; ++TT );
		assert( calc_z(n,TT) == w );
		m = 0, dump(n,TT), qsort(idx,m,sizeof *idx,cmp);
		for ( i = 0; i < m; ++i ) 
			printf("%3d%7d   %s\n",score[idx[i]],tm[idx[i]],desc[idx[i]]);
		printf("\nTotal score: %u points\n",w);
		printf(" Total time: %d hours\n",TT);
		if ( ts ) putchar('\n');
	}
	return 0;
}

