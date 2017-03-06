/*
 * 10070. Leap Year
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;
enum { DIGL = 5, BASE = 100000LL };

char buff[0x400];

i64 *read_int( char *s ) {
	i64 *x,i,j,k,t;
	for ( k = strlen(s), i = 0, j = k-1; i < j; ++i, --j )
		t = s[i], s[i] = s[j], s[j] = t;
	for (;k % DIGL; s[k++] = '0' );
	x = (i64 *)calloc((k/DIGL+4),sizeof *x);
	for ( i = 0; i < k/DIGL; x[++i] = t ) 
		for ( t = 0, j = (i+1)*DIGL-1; j >= i*DIGL; t = 10*t+(s[j--]-'0') );
	for ( i = k/DIGL+1; i && !x[i]; --i );
	*x = !i ? 1 : i+1;
	return x;
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

i64 div_mod( i64 *x, i64 m ) {
	i64 rem,k,i,*z = (i64 *)calloc((*x+1),sizeof *z);
	for ( i = 0; i <= *x; ++i ) z[i] = x[i];
	for ( rem = k = 0, i = *x; i ; --i, rem = k ) 
		k = (rem*BASE+z[i])%m, z[i] = (rem*BASE+z[i])/m;
	return rem;
}

int main() {
	int cs = 0,k,leap,huku,bulu;
	i64 *x;
	while ( 1 == scanf("%s",buff) ) {
		if ( ++cs > 1 ) putchar('\n');
		x = read_int(buff);
		if ( leap=((!div_mod(x,4)&&div_mod(x,100))||!div_mod(x,400)) ) 
			puts("This is leap year.");
		huku = !div_mod(x,15);
		bulu = leap && !div_mod(x,55);
		if ( !leap && !huku && !bulu )
			puts("This is an ordinary year.");
		if ( huku )
			puts("This is huluculu festival year.");
		if ( bulu )
			puts("This is bulukulu festival year.");
	}
	return 0;
}
