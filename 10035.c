/*
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef long long i64;
enum { BASE = 10LL, DIGL = 1LL, LEN = 64 };

i64 cr,*x,*y,*z;

void print( i64 *x ) {
	int i;
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) {
		puts("0");
		return ;
	}
	for ( printf("%lld",x[i]); --i >= 0; printf("%0*lld",DIGL,x[i]) );
	putchar('\n');
}

int is_zero( i64 *x ) {
	int i;
	for ( i = 0; i < LEN && !x[i]; ++i );
	return i == LEN;
}

i64 *read_int() {
	char s[0x400];
	i64 *x,i,j,k,t;
	if ( 1 != scanf("%s",s) )
		return NULL;
	k = strlen(s);
	for ( i = 0, j = k-1; i < j; ++i, --j )
		t = s[i], s[i] = s[j], s[j] = t;
	for (; k % DIGL; s[k++] = '0' );
	x = (i64 *)calloc(LEN,sizeof *x);
	for ( i = 0; i < k/DIGL; ++i )
		for ( j = (i+1)*DIGL-1; j >= i*DIGL; x[i] = 10*x[i]+(s[j--]-'0') );
	return x;
}

i64 *add( i64 *x, i64 *y ) {
	i64 *z = (i64 *)calloc(LEN, sizeof *z),i;
	for ( i = 0; i < LEN; z[i] = x[i]+y[i], ++i );
	for ( cr = i = 0; i < LEN-1; ++i )
		if (z[i]>=BASE&&++cr&&(z[i+1]+=z[i]/BASE,z[i]%=BASE));
	return z;
}

int main() {
	for (;(x = read_int()) && (y = read_int()) && (!is_zero(x) || !is_zero(y)); ) {
		z = add(x,y), printf(!cr ? "No carry operation.\n" : "%lld carry operation%s.\n",cr, cr == 1 ? "":"s");
	}
	return 0;
}
