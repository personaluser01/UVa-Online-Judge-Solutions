/*
 * 11421. Arranging Cards
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVAL    13
#define MAXS      5
#define N 0x80
#define BIT(k)    (1ULL<<(k))
#define MASK(k)   (BIT(k)-1ULL)
#define SET(u,k)  ((u)|=BIT(k))
#define CLR(u,k)  ((u)&=~BIT(k))
#define TST(u,k)  ((u)&BIT(k))
#define L(u) 	  ((u)&((~(u))+1))
#define B(u,k)    (((u)>>((MAXS-1)*(k)))&MASK(MAXS-1))
typedef long long i64;
typedef unsigned long long u64;
enum { BASE = 10000LL, DIGL = 4, LEN = 4 };
#define LIM (1000000000000000001LL)
#define oo 0xffffffffffffffffull
#define Q (1 << 20)

u64 encode( int value, int suit ) { return value*(MAXS-1)+suit; }

int ch2val( char ch ) {
	if ( isdigit(ch) )
		return ch-'2';
	assert( isalpha(ch) );
	ch = toupper(ch);
	switch ( ch ) {
		case 'A': return 8;
		case 'T': return 12;
		case 'J': return 9;
		case 'Q': return 11;
		case 'K': return 10;
		default: assert( 0 );
	}
	assert( 0 );
}

int ch2suit( char ch ) {
	assert( isalpha(ch) );
	ch = toupper(ch);
	switch ( ch ) {
		case 'C': return 0;
		case 'D': return 1;
		case 'H': return 2;
		case 'S': return 3;
		default: assert ( 0 );
	}
	assert(0);
}

const char *_suit = "CDHS",
	  	   *_val  = "23456789AJKQT";
i64 c[N][N],F[N],mu[MAXS][MAXS],d[MAXS][MAXVAL*MAXS],q[MAXS][MAXS][MAXVAL*MAXS],
	p[MAXS][MAXS][MAXS][MAXVAL*MAXS],r[MAXS][MAXS][MAXS][MAXS][MAXVAL*MAXS],
	s[MAXS][MAXS][MAXS][MAXS][MAXS][MAXVAL*MAXS],
	w[MAXS][MAXS][MAXS][MAXS][MAXS][MAXS][MAXVAL*MAXS],
	ans[MAXS][MAXS][MAXS][MAXS][MAXS][MAXS][MAXS][MAXVAL*MAXS];

u64 z[Q];
char who[1<<MAXS],bts[1<<MAXS];
int n,cs;

int get_val( u64 u ) {
	int k;
	assert( u );
	assert( !(u & (u-1)) );
	for(k=0;k<MAXVAL&&!(u&MASK(MAXS-1));++k,u>>=(MAXS-1));
	return k;
}

void decode( u64 crd, int *value, int *suit ) {
	assert( crd );
	assert( !(crd & (crd-1)) );
	*value = get_val(crd), *suit = who[B(crd,*value)];
}

void display_card( u64 u ) {
	int k,i;
	decode(u,&k,&i);
	printf(" %c%c",_val[k],_suit[i]);
}

i64 multinomial_coeff( int *m, int sum, int n ) {
	if ( n == 1 ) {
		assert( sum == *m );
		return 1;
	}
	return c[sum][*m]*multinomial_coeff(m+1,sum-*m,n-1);
}

void H( int *m, int cur, int n, i64 *res, int *y ) {
	i64 ax,i,k;

#if 1
	if ( cur == n-7 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-7; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 8 )
			ax *= multinomial_coeff(y,k,n-7);
		ax *= ans[m[n-7]][m[n-6]][m[n-5]][m[n-4]][m[n-3]][m[n-2]][m[n-1]][k];
		*res += ax;
		return ;
	}

	if ( cur == n-6 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-6; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 7 )
			ax *= multinomial_coeff(y,k,n-6);
		ax *= w[m[n-6]][m[n-5]][m[n-4]][m[n-3]][m[n-2]][m[n-1]][k];
		*res += ax;
		return ;
	}

	if ( cur == n-5 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-5; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 6 )
			ax *= multinomial_coeff(y,k,n-5);
		ax *= s[m[n-5]][m[n-4]][m[n-3]][m[n-2]][m[n-1]][k];
		*res += ax;
		return ;
	}

	if ( cur == n-4 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-4; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 5 )
			ax *= multinomial_coeff(y,k,n-4);
		ax *= r[m[n-4]][m[n-3]][m[n-2]][m[n-1]][k];
		*res += ax;
		return ;
	}

	if ( cur == n-3 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-3; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 4 )
			ax *= multinomial_coeff(y,k,n-3);
		ax *= p[m[n-3]][m[n-2]][m[n-1]][k];
		*res += ax;
		return ;
	}
	if ( cur == n-2 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-2; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 3 )
			ax *= multinomial_coeff(y,k,n-2);
		ax *= q[m[n-2]][m[n-1]][k];
		*res += ax;
		return ;
	}
	if ( cur == n-1 ) {
		for ( ax = 1LL, k = 0, i = 0; i < n-1; ++i )
			k += y[i], ax *= mu[m[i]][y[i]];
		if ( n >= 2 ) ax *= multinomial_coeff(y,k,n-1);
		assert( k < MAXVAL*MAXS );
		ax *= d[m[n-1]][k];
		*res += ax;
		return ;
	}
#else
	if ( cur == n ) {
		for ( k = 0, ax = 1LL, i = 0; i < n && ax; ++i )
			ax *= mu[m[i]][y[i]], k += y[i];
		if ( ax ) *res += ax*multinomial_coeff(y,k,n);
		return ;
	}
#endif
	for ( y[cur] = 1; y[cur] <= m[cur]; ++y[cur] )
		H(m,cur+1,n,res,y);
}

/*
 * returns how many valid arrangements are there
 */
i64 how_many( u64 u ) {
	int m[MAXVAL],y[MAXVAL],
		k,sum = 0, n = 0,j,i,ok = 1;
	u64 v = 0;
	i64 res = 0;

	if ( !u ) return 1LL;

	for ( k = 0; k < MAXVAL; ++k )
		if ( m[n] = bts[B(u,k)] ) {
			sum += m[n++];
			if ( m[n-1]==MAXS-1 )
				ok = 0;
		}
	
	if ( n <= 10 && ok ) {
		for ( j = 1;j;)
			for ( j = i = 0; i < n-1; ++i )
				if ( m[i] > m[i+1] )
					++j, k = m[i], m[i] = m[i+1], m[i+1] = k;
		for ( i = 0; i < n; ++i ) {
			assert( m[i] >= 1 && m[i] < MAXS );
			v |= ((u64)(m[i]))<<(2*i);
		}
		assert( v < Q );
		if ( z[v] == LIM )
			return z[v];
		if ( z[v] < +oo )
			return (i64)z[v];
	}

	H(m,0,n,&res,y);
	for ( k = 0; k < n && res && res < LIM; ++k )
		if ( ((long double)res) >= ((long double)LIM)/F[m[k]] ) 
			res = LIM;
		else res *= F[m[k]];
	if ( n <= 10 && ok ) {
		assert( v < Q );
		assert( res < +oo );
		z[v] = res;
	}
	return res;
}

/*
 * returns how many arrangements are there with
 * the first card fixed
 * u:    bitmask representing all the cards available
 * crd:  which card to fix at the first position
 */
i64 kuinka_monta( u64 u, u64 crd ) {
	int i,j,k,l;
	i64 res = 0;

	if ( !u ) { assert( !crd ); return 1LL; }

	assert( crd & u );
	
	decode(crd,&k,&i);

	if ( (l = bts[B(u,k)]) == 1 )
		return how_many(u&~crd);

	assert( l >= 2 );

	res = how_many(u&~crd);
	if ( res >= LIM )
		return res;
	j = who[L(B(u&~crd,k))];
	assert( j != i && j < MAXS-1 );
	return res-(l-1)*kuinka_monta(u&~crd,BIT(encode(k,j)));
}

void f( u64 u, u64 K, int last_val ) {
	i64 ax=0,t;
	u64 e,c;

	if ( !u ) {assert(K==1);return;}

	for(e=u;e;) {
		if ( get_val(c = L(e))==last_val ) {
			e &= ~c;
			continue ;
		}
		if ( (t = kuinka_monta(u,c)) >= LIM || K <= ax+t ) 
			break ;
		assert( ax <= LIM-t );
		ax += t, e &= ~c;
	}

	assert(t == LIM||(ax<K&&K<=(ax+t)));
	display_card(c);
	/*printf("  Permutations left %llu, t = %lld, ax = %lld\n",K-ax,t,ax);*/
	f(u&~L(e),K-ax,get_val(c));
}

int main() {
	i64 i,j,k,l,t,m,mm,nn,ii;
	u64 e,K;
	char a[4];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	/*
	 * initialisation
	 */
	memset(z,0xffull,sizeof(z));
	for ( i = 0; i < N; c[i++][0] = 1 );
	for ( i = 1; i < N; ++i )
		for ( j = 1; j <= i; ++j )
			c[i][j] = c[i-1][j]+c[i-1][j-1];
	for ( F[0] = 1, i = 1; i < N; ++i ) F[i] = i*F[i-1];
	for ( t = 1; t < MAXS; ++t )
		for ( k = 0; k < MAXVAL*MAXS; ++k )
			for ( i = 1; i <= t; ++i )
				if ( k+i < MAXVAL*MAXS )
					d[t][k] += (((t-i)&1)?-1:1)*c[t-1][i-1]*c[k+i][i];
	for ( m = 1; m < MAXS; ++m )
		for ( t = 1; t <= m; ++t )
			for ( mm = 1; mm < MAXS; ++mm )
				for ( k = 0; k+t < MAXVAL*MAXS; ++k )
					q[m][mm][k] += (((m-t)&1)?-1:1)*c[m-1][t-1]*c[k+t][t]*d[mm][k+t];
	for ( m = 1; m < MAXS; ++m )
		for ( t = 1; t <= m; ++t )
			for ( mm = 1; mm < MAXS; ++mm )
				for ( n = 1; n < MAXS; ++n )
					for ( k = 0; k+t < MAXVAL*MAXS; ++k )
						p[m][mm][n][k] += (((m-t)&1)?-1:1)*c[m-1][t-1]*c[k+t][t]*q[mm][n][k+t];
	for ( m = 1; m < MAXS; ++m )
		for ( t = 1; t <= m; ++t )
			for ( mm = 1; mm < MAXS; ++mm )
				for ( n = 1; n < MAXS; ++n )
					for ( nn = 1; nn < MAXS; ++nn )
						for ( k = 0; k+t < MAXS*MAXVAL; ++k )
							r[m][mm][n][nn][k] += (((m-t)&1)?-1:1)*c[m-1][t-1]*c[k+t][t]*p[mm][n][nn][k+t];
	for ( m = 1; m < MAXS; ++m )
		for ( t = 1; t <= m; ++t )
			for ( mm = 1; mm < MAXS; ++mm )
				for ( n = 1; n < MAXS; ++n )
					for ( nn = 1; nn < MAXS; ++nn )
						for ( l = 1; l < MAXS; ++l )
							for ( k = 0; k+t < MAXS*MAXVAL; ++k )
								s[m][mm][n][nn][l][k] += (((m-t)&1)?-1:1)*c[m-1][t-1]*c[k+t][t]*r[mm][n][nn][l][k+t];
	for ( m = 1; m < MAXS; ++m )
		for ( t = 1; t <= m; ++t )
			for ( mm = 1; mm < MAXS; ++mm )
				for ( n = 1; n < MAXS; ++n )
					for ( nn = 1; nn < MAXS; ++nn )
						for ( l = 1; l < MAXS; ++l )
							for ( i = 1; i < MAXS; ++i )
								for ( k = 0; k+t < MAXS*MAXVAL; ++k )
									w[m][mm][n][nn][l][i][k] += (((m-t)&1)?-1:1)*c[m-1][t-1]*c[k+t][t]*s[mm][n][nn][l][i][k+t];
	for ( m = 1; m < MAXS; ++m )
		for ( t = 1; t <= m; ++t )
			for ( mm = 1; mm < MAXS; ++mm )
				for ( n = 1; n < MAXS; ++n )
					for ( nn = 1; nn < MAXS; ++nn )
						for ( l = 1; l < MAXS; ++l )
							for ( i = 1; i < MAXS; ++i )
								for ( j = 1; j < MAXS; ++j )
								for ( k = 0; k+t < MAXS*MAXVAL; ++k )
									ans[m][mm][n][nn][l][i][j][k] += (((m-t)&1)?-1:1)*c[m-1][t-1]*c[k+t][t]*w[mm][n][nn][l][i][j][k+t];
	for ( k = 1; k < MAXS; ++k )
		for ( l = 0; l <= k-1; ++l )
			mu[k][k-l] = ((l&1)?-1:1)*c[k-1][k-l-1];
	for ( i = 0; i < (1 << MAXS); ++i ) bts[i] = bts[i>>1]+(i&1);
	for ( i = 0; i < MAXS; ++i ) who[1<<i] = i;
	while(2==scanf("%d %llu",&n,&K)&&(n||K)){
		for ( e = 0, i = 0; i < n; ++i ) {
			scanf("%s",a);
			k = ch2val(0[a]), j = ch2suit(1[a]);
			assert( !TST(e,encode(k,j)) );
			SET( e,encode(k,j) );
		}
		printf("Case %d:",++cs);
		if ( (t = how_many(e)) < K )
			puts(" Not found");
		else {
			/*printf("Good news: %lld total arrangements, and K is %llu\n",t,K);*/
			f(e,K,MAXVAL), putchar('\n');
		}
	}
	return 0;
}

