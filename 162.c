/*
 * 162. Beggar My Neighbour
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
#define M(k) ((1 << (k))-1UL)
#define enc(s,v) ((s)|((v)<<2))
#define N 0x200

unsigned int c[2][N],n[2],S[256],val[256],T,*top[2],*ptr,q[N];
char suite[4][5] = {"C","D","H","S"};

int V( char *s ) {
	int n;
	if ( isdigit(*s) ) { sscanf(s,"%d",&n); return n; }
	return val[*s];
}

int rinp() {
	int i,j,k,t;
	char suit[0x40],value[0x40];
	for ( t = 0; t <= 1; ++t ) top[t] = c[t];
	for ( t = 0, i = 0; i < 52; ++i, *++top[t] = enc(S[*suit],V(value)), t ^= 1 ) 
		if ( 2 != scanf("%[C,D,H,S]%s ",suit,value) )
			return 0;
	for ( t = 0; t <= 1; n[t] = top[t]-c[t], ++t );
	assert( n[0] == i/2 && n[1] == i/2 );
	return 1;
}

int face( unsigned int u ) { return (u>>2)>=11; }

void rev( unsigned int *s, unsigned int *t ) {
	unsigned int *i,*j,k;
	for ( i = s, j = t; i < j; ++i, --j )
		k = *i, *i = *j, *j = k;
}

int main() {
	int i,j,k,t,l;
	unsigned int ini;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	S['C'] = 0, S['D'] = 1, S['H'] = 2, S['S'] = 3;
	val['T'] = 10, val['J'] = 11, val['Q'] = 12, val['K'] = 13, val['A'] = 14;
	while ( rinp() ) {
		for ( t = 0; top[t] > c[t]; ) {
			nx01: for ( ptr = q; top[t] > c[t] && !face(*++ptr = *top[t]--); t ^= 1 );
			if ( ptr > q && face(*ptr) ) {
				nx02: for ( l = t^1, ini = *ptr, k = ((int)((*ptr)>>2))-10; top[l] > c[l] && k && !face(*++ptr = *top[l]--); k-- );
				if ( ptr > q && face(*ptr) && *ptr != ini ) { t = l; goto nx02; }
				if ( !k && !(ptr > q && face(*ptr)) ) {
					rev(c[l^1]+1,top[l^1]);
					for ( j = 1; j <= ptr-q; *++top[l^1] = q[j++] );
					rev(c[l^1]+1,top[l^1]);
					goto nx01;
				}
				if ( k && top[l] == c[l] ) { t = l; break; }
			}
		}
		t ^= 1, printf("%d%3lu\n",t==0?2:1,top[t]-c[t]);
	}
	return 0;
}
