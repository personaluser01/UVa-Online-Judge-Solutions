/*
 * 10109. Solving Systems of Linear Equations
 */
#include <assert.h>
#include <stdio.h>
#include <cstdlib.h>
#include <string.h>
#include <ctype.h>
#define N 64
typedef long long i64;
enum { BASE = 100000LL, DIGL = 5, LEN = 4 };

i64 *init() {
	i64 *z = (i64 *)calloc(LEN, sizeof *z);
	return z;
}

int is_negative( i64 *x ) { return x[LEN-1] >= BASE/2; }

void negate( i64 *x ) {
	int i;
	for ( i = 0; i < LEN; ++i ) x[i] = BASE-1-x[i];
	for ( i = 0; i < LEN && x[i] == BASE-1; x[i++] = 0 );
	++x[i];
}

void print( i64 *x ) {
	int i;
	if ( is_negative(x) ) {
		putchar('-'), negate(x), print(x), negate(x);
		return ;
	}
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) {
		puts("0");
		return ;
	}
	for ( printf("%lld",x[i]); --i >= 0; printf("%0*lld",x[i]) );
	putchar('\n');
}

i64 *mult( i64 *x, i64 *Y ) {
	int i,j;
	i64 *z = init();
	for ( i = 0; i < LEN; ++i )
		for ( j = 0; j+i < LEN; ++j )
			z[i+j] += x[i]*y[j];
	for ( i = 0; i < LEN; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i] / BASE, z[i] %= BASE;
	return z;
}

i64 *add( i64 *x, i64 *y ) {
	i64 *z = init();
	int i;
	for ( i = 0; i < LEN; ++i )
		z[i] = x[i]+y[i];
	for ( i = 0; i < LEN; ++i )
		if ( z[i] >= BASE )
			z[i+1] += z[i] / BASE, z[i] %= BASE;
	return z;
}

int is_zero( i64 *x ) {
	int i;
	for ( i = 0; i < LEN; ++i )
		if ( x[i] )
			return 0;
	return 1;
}

i64 *subtr( i64 *x, i64 *y ) {
	i64 *z;
	negate(y), z = add(x,y), negate(y);
	return z;
}

typedef struct frac {
	i64 *x, *y;
} frac;

void read_bignum( i64 *x, char *s ) {
	int i,j,k,L = strlen(s);
	for ( i = L; L % DIGL; s[L++] = '0' );
	for ( k = 0; k < L/DIGL; ++k )
		for ( x[k] = 0, i = (k+1)*DIGL-1; i >= k*DIGL; --i )
			x[k] *= 10, x[k] += s[i]-'0';
}

void read_Frac( frac *a ) {
	int ch,sign = 1;
	char str[0x400],*ptr = str;
	while ( (ch = getchar()) != EOF && ch != '-' && ch != '+' && !isdigit(ch) );
	assert( ch != EOF );
	if ( ch == '-' || ch == '+' ) {
		if ( ch == '-' ) sign = -1;
	}
	else *ptr++ = ch;
	for (;(ch = getchar()) != EOF && isdigit(ch); *ptr++ = ch );
	*ptr = '\0', read_bignum(a->x,str);
	if ( ch == '/' ) {
		for ( ptr = str; (ch = getchar()) != EOF && isdigit(ch); *ptr++ = ch );
		*ptr = '\0', read_bignum(a->y,str);
	}
	else a->y[0] = 1LL;
}

i64 big2int( i64 *x ) {
	i64 z = 0,i,sign = 1;
	if ( is_negative(x) )
		sign = -1, negate(x);
	for ( i = LEN-1; i >= 0; z *= BASE, z += x[i--] );
	if ( sign == -1 )
		negate(x);
	return sign*z;
}

i64 gcd( i64 *x, i64 *y ) {
	if ( is_zero(y) ) {
		return big2int(x);
	}
	return gcd(y,subtr(x,y));
}

i64 longdiv( i64 *x, i64 m ) {
	i64 r,i,tmp;
	for ( i = LEN-1; i >= 0; --i, r = tmp ) {
		tmp = (r*BASE+x[i]) / m;
		x[i] = (r*BASE+x[i]) % m;
	}
	return r;
}

frac *add_frac( frac *a, frac *b ) {
	frac *c = (frac *)malloc(sizeof *c);
	c->y = mult(a->y,b->y);
	c->x = add(mult(a->x,b->y),mult(a->y,b->x));
	normalise(c);
	return c;
}

frac *mult_frac( frac *a, frac *b ) {
	i64 *m = mult(a->x,b->x),
		*n = mult(a->y,b->y),
		d = gcd(m,n);
	frac *c = (frac *)malloc(sizeof *c);
	longdiv(m,d), longdiv(n,d);
	c->x = m, c->y = n;
	return c;
}

void div_frac( i64 *x ) {
}

int main() {
}

