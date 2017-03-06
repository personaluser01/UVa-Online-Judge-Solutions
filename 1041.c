/*
 * 1041.
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
#define C 52
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define cp(x,y) (strncpy(x,y,C),x[C] = '\0')

int ts,cs,n,m,e[N],s[N],num,limit;
char t[N],canonical[N][N],y[N][N];

int hamming( char *a, char *b ) {
	int i,j = 0;
	for ( i = 0; i < C; ++i )
		if ( a[i] != b[i] ) ++j;
	return j;
}

int getnum( char *c ) {
	int i,j,k = (1<<29),ans;
	for ( i = 0; i <= 10; ++i )
		if ( (j=hamming(canonical[i],c)) < k ) 
			k = j, ans = i;
	return ans;
}

void shuffle( char *c ) {
	static char d[N],i,j,k;
	for ( k = 0, i = 26, j = 0; j < 26; d[k++] = c[i++], d[k++] = c[j++] );
	for ( i = 0; i < 52; ++i ) c[i] = d[i];
	c[C] = '\0';
}

void unshuffle( char *c ) {
	static char d[N],i,j,k,l;
	for ( i = 0, j = 1, k = 26, l = 0; i < C/2; j += 2, l += 2 )
		d[i++] = c[j], d[k++] = c[l];
	for ( i = 0; i < C; ++i ) c[i] = d[i];
	c[C] = '\0';
}

void print( char *c ) {
	int i;
	for ( i = 0; i < C; ++i )
		printf("%d ",c[i]-'A');
	puts("");
}

int f( char *c, int cost, int num_shuffles_made ) {
	char d[C+2],i,j,k;
	if ( num_shuffles_made == num )
		return 0==strncmp(c,t,C); 
	assert( num_shuffles_made < num );
	if ( cost > limit ) return 0;
	if ( (cp(d,c),shuffle(d),hamming(d,y[num_shuffles_made+1])<=2*(limit-cost))&&f(d,cost,num_shuffles_made+1) )
		return 1;
	for ( cp(d,c),shuffle(d), i = 0; i < C-1; ++i	) {
		xchg(d[i],d[i+1]), e[m] = i, s[m++] = num_shuffles_made+1;
		if ( hamming(d,y[num_shuffles_made+1])<=2*(limit-cost-1)&&f(d,cost+1,num_shuffles_made+1) ) return 1;
		xchg(d[i],d[i+1]), --m;
	}
	return 0;
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( j = 0; j < C; ++j )
		canonical[0][j] = j+'A';
	for ( i = 1; i <= 11; ++i )
		cp(canonical[i],canonical[i-1]), shuffle(canonical[i]);

	for ( scanf("%d",&ts); ts--; putchar('\n') ) {
		printf("Case %d\n",++cs);
		for ( n = 52, i = 0; i < n; ++i ) 
			scanf("%d",&k), t[i] = k+'A';
		printf("Number of shuffles = %d\n",num=getnum(t));
		for ( i = num, cp(y[i],t); --i >= 0; cp(y[i],y[i+1]), unshuffle(y[i]) );
		for ( m = 0, limit = 0; limit <= num && !f(canonical[0],0,0); ++limit );
		if ( !limit ) {
			puts("No error in any shuffle");
		}
		else {
			assert( limit <= 10 );
			assert( m == limit );
			for ( i = 0; i < m; ++i ) 
				printf("Error in shuffle %d at location %d\n",s[i],e[i]);
		}
	}
	return 0;
}

