/*
 * 10162. Last Digit
 * KEYWORDS: Long integer, cycle finding, last digit
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define xchg(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
typedef long long i64;
/* enum { BASE = 1000000LL, DIGL = 6, LEN = 20 };*/
enum { BASE = 10LL, DIGL = 1, LEN = 101 };
#define D 10LL

char *ptr,buff[0x400];
int seen[D],yes;

i64 *read_int( char *ptr ) {
	int i,j,k,blocks,ax,cur;
	i64 *x = (i64 *)calloc(LEN,sizeof *x);
	for ( k = 0; *(ptr+k) && *(ptr+k) != '\n'; ++k );	
	for ( i = 0, j = k-1; i < j; ++i, --j )
		xchg(ptr[i],ptr[j]);
	for (;k % DIGL; ptr[k++] = '0' );
	for ( cur = 0, blocks = k/DIGL, i = 0; i < blocks; x[i++] = ax, cur += DIGL )
		for ( ax = 0, j = cur+DIGL-1; j >= cur; ax = ax*10 + ptr[j--]-'0' );
	return x;
}

void print( i64 *x ) {
	int i;
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	if ( i < 0 ) {
		putchar('0');
		return ;
	}
	for ( printf("%lld",x[i]); --i >= 0; printf("%*lld",DIGL,x[i]) );
}

void dec( i64 *x ) {
	int i;
	for ( i = 0; i < LEN && !x[i]; ++i );
	assert( i < LEN );
	for ( --x[i]; --i >= 0; x[i] = BASE-1 );
}

void divi( i64 *x, i64 a, i64 *r ) {
	i64 q,rem,i,tmp;
	for ( rem = 0, i = LEN-1; i >= 0; --i ) {
		tmp = (BASE*rem+x[i]) % a;
		x[i] = (BASE*rem+x[i]) / a;
		rem = tmp;
	}
	*r = rem;
}

int is_zero( i64 *x ) {
	int i;
	for ( i=  LEN-1; i >= 0 && !x[i]; --i );
	return i < 0;
}

int is_dig( i64 *x ) {
	int i;
	for ( i = LEN-1; i >= 0 && !x[i]; --i );
	return i <= 0;
}

int main() {
	int i,j,k,cycle_len[D];
	i64 *x,z[LEN],ax,bx,T,c[D],sum[D],r[D],g,tmp,pre[D];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	/*
	x = read_int(FG);
	divi(x,23,&tmp);
	print(x);
	printf(" remainder %lld\n",tmp);
	return 0;
	*/
	for ( i = 2, pre[1] = 1; i < D; ++i ) {
		for ( ax = 1, j = 0; j < i; ++j )
			ax *= i, ax %= D;
		pre[i] = pre[i-1]+ax;
		pre[i] %= D;
	}
	while ( !is_zero(x = read_int(FG)) ) {
		if ( is_dig(x) ) {
			printf("%lld\n",pre[x[0]]);
			continue ;
		}
		for ( T = 0, i = 1; i <= 9; ++i ) {
			for ( j = 0; j < LEN; ++j ) z[j] = x[j];
			for (;!is_zero(z) && z[0] % 10 != i;dec(z));
			for ( j = 1; j < LEN; z[j-1] = z[j], ++j );
			for ( ax = 1LL, j = 0; j < D; ++j )
				ax *= i, ax %= D;
			bx = ax*ax, bx %= D;
			for ( seen[g = ax] = ++yes, j = 2, sum[i] = ax;\
				seen[bx] != yes; ++j, sum[i] += bx, sum[i] %= D, bx *= ax, bx %= D );
			cycle_len[i] = j-1;
			for ( ax = 1, j = 0; j < i; ++j, ax *= i, ax %= D );
			T += (c[i] = ax), T %= D;
			divi( z, cycle_len[i], r+i );
			T += c[i]*(sum[i]*z[0]), T %= D;
			for ( tmp = 0, ax = g, j = 0; j < r[i]; ++j )
				tmp += ax, ax *= g, ax %= D;
			T += (tmp % D)*c[i], T %= D;
		}
		printf("%lld\n",T);
	}
	return 0;
}

