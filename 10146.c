/*
 * 10146. Dictionary
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
#define N 100100
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
typedef unsigned long long u64;
#define M(k) ((1ULL<<(k))-1UL)

int empty( char *p ) {
	for ( ;*p && *p != '\n' && isspace(*p); ++p );
	return *p == '\0'||*p == '\n';
}

u64 conv( char *p, int *len ) {
	u64 u = 0,i;
	for( i = 0; *p && *p != '\n'; ++p, ++i )
		u |= (((u64)(*p-'a')) << (5*i));
	*len = i;
	return u;
}

int access_char( u64 u, int i ) { return (u>>(5*i))&M(5); }

u64 w[N];
char buff[0x400],*ptr;
int len[N],n;

void skip( int k ) { for (;k--; putchar(' ') ); }

void display( u64 u, int len ) {
	int i;
	for ( i = 0; i < len; ++i )
		putchar(((u>>(5*i))&M(5))+'a');
	putchar('\n');
}

int lcp( u64 u, u64 v, int p, int q ) {
	int i,j,k;
	if ( p <= q && (u&v) == u )
		return p;
	if ( q <= p && (u&v) == v )
		return q;
	for ( i = 0, j = (p<q?q:p); i+1 != j; ) {
		k = (i+j)/2;
		if ( (u & M(5*k)) == (v & M(5*k)) )
			i = k;
		else j = k;
	}
	return i;
}

void construct_dict( int a, int b, int shift, int spaces ) {
	int i,j,k;
	if ( a > b ) return ;
	skip( spaces ), display( w[a], len[a] );
	if ( a == b ) return ;
	for ( i = a+1; i <= b; i = j ) {
		for ( k = i; k <= b && len[k] <= shift+1; ++k )
			construct_dict(k,k,shift,spaces+1);
		for ( i = k, j = i+1; j <= b && len[j] > shift+1 && access_char(w[i],shift+1)==access_char(w[j],shift+1); ++j );
		if ( i <= b ) construct_dict(i,j-1,shift+1,spaces+1);
	}
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts), FG; ts--; ) {
		for ( n = 0; FG && !empty(ptr); w[n] = conv(ptr,len+n), ++n ) ;
		for ( i = 0; i < n; i = j ) {
			for ( j = i+1; j < n && access_char(w[i],0)==access_char(w[j],0); ++j );
			construct_dict(i,j-1,0,0);
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}

