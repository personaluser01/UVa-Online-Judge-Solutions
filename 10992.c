/*
 * 10992. The Ghost of Programmers
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
typedef long long i64;
enum { DIGL = 6, BASE = 1000000LL };

int cs;

int is_zero( i64 *x ) {
	int i;
	for ( i = *x; i && !x[i]; --i );
	return !i;
}

void print( i64 *x ) {
	int i;
	for ( i = *x; i && !x[i]; --i );
	if ( !i ) {
		puts("0");
		return ;
	}
	for ( printf("%lld",x[i]); --i; printf("%0*lld",DIGL,x[i]) );
	putchar('\n');
}

i64 *read_int() {
	char s[0x400],os[0x400];
	int i,j,k,t;
	i64 *x;
	if ( !fgets(s,sizeof(s),stdin) )
		return NULL;
	for ( k = 0; s[k] && s[k] != '\n'; os[k] = s[k], ++k );
	os[k] = '\0';
	for ( i = 0, j = k-1; i < j; ++i, --j )
		t = s[i], s[i] = s[j], s[j] = t;
	for (;k % DIGL; s[k++] = '0' );
	s[k] = '\0';
	x = (i64 *)calloc(k/DIGL+4,sizeof *x);
	for ( i = 0; i < k/DIGL; ++i )
		for ( j = (i+1)*DIGL-1; j >= i*DIGL; x[i+1] = 10*x[i+1] + (s[j--]-'0') );
	for ( i = k/DIGL; i && !x[i]; --i );
	*x = !i ? 1 : i;
	if ( !is_zero(x) ) {
		if ( ++cs > 1 ) putchar('\n');
		puts(os);
	}
	return x;
}


i64 m[8] = {2,5,7,11,15,20,28,36},*F;
char nm[][0x80] = {"Tanveer Ahsan","Shahriar Manzoor","Adrian Kugel","Anton Maydell","Derek Kisman",
		"Rezaul Alam Chowdhury","Jimmy Mardell","Monirul Hasan","K. M. Iftekhar"};
#define ANN(k) (++g,printf("Ghost of %s!!!\n",nm[k]))

i64 divmod( i64 *y, i64 n ) {
	i64 rem,k,i,x[0x400];
	for ( i = 0; i <= *y; ++i ) x[i] = y[i];
	for ( rem = 0, i = *x; i; --i, rem = k )
		k = (BASE*rem+x[i])%n, x[i] = (BASE*rem+x[i])/n;
	return rem;
}

int is_less( i64 *x, i64 *y ) {
	int i,j,k;
	for ( i = *x; i && !x[i]; --i );
	for ( j = *y; j && !y[j]; --j );
	if ( i == j ) {
		for ( k = i; k; --k )
			if ( x[k] != y[k] )
				return x[k] < y[k];
		return 0;
	}
	return i < j;
}

int main() {
	i64 *x,i,j,k,g,itef;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	F = (i64 *)calloc(2,sizeof *F);
	F[1] = 2148, F[0] = 1;
	while ( (x = read_int()) && !is_zero(x) ) {
		if ( (g = 0),is_less(x,F) )
			goto nx;
		itef = ( (!divmod(x,4) && divmod(x,100))||!divmod(x,400) );
		for ( x[1] -= 2148, i = 1; i <= *x; ++i )
			if ( x[i] < 0 )
				--x[i+1], x[i] += BASE;
		for ( i = *x; i && !x[i]; --i );
		*x = !i ? 1 : i;
		for ( i = 0; i < 8; ++i )
			if ( !divmod(x,m[i]) )
				ANN(i);
		if ( itef ) ANN(8);
		nx: 
		if ( !g ) puts("No ghost will come in this year");
	}
	return 0;
}

