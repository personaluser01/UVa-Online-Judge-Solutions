/*
 * 254. Towers of Hanoi
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L (1 << 21)
typedef long long i64;
enum { A, B, C };
#if 0
#define P(x,a,b) (printf("Moving %d disks from %s to %s\n",x,nm[a],nm[b]))
#else
#define P(x,a,b) (1)
#endif

char buff[L],x[L],z[L],nm[3][2] = {"A","B","C"};
int D,m,n,cnt[3];;

int div2( char *s, int *n ) {
	int r,i,k;
	assert( *n >= 1 );
	for ( r = 0, i = *n-1; i >= 0; --i, r = k )
		k = (10*r+s[i]-'0')&1, s[i] = ((10*r+s[i]-'0')>>1)+'0';
	for ( i = *n-1; i >= 0 && s[i]=='0'; --i );
	*n = (i<0?1:(i+1));
	return r;
}

void print( char *s, int n ) {
	int i;
	for ( i = n-1; i >= 0; putchar(s[i--]) );
	putchar('\n');
}

void upd( char *s, int *m ) {
	int i;
	for ( i = *m-1; i >= 0 && s[i]=='0'; --i );
	*m = (i<0?1:i+1);
	if ( !(*m==1 && s[0]=='0') )
		assert( s[(*m)-1] == '1' );
	s[*m] = '\0';
}

int is_repunit( char *s, int n ) {
	int i;
	for ( i = 0; i < m; ++i )
		if ( s[i] != '1' )
			return 0;
	return 1;
}

void subtr( char *x, int *n, int k ) {
	int c[1 << 15],i,j,d[1 << 15];
	for ( i = 0; i < *n; ++i )
		c[i] = x[i]-'0';
	if ( c[k] )
		c[k] = 0;
	else {
		for ( i = k+1; i < *n && !c[i]; ++i );
		for ( c[k] = 1, --c[i], j = k+1; j < i; c[j++] = 1 );
	}
	for ( ++c[0], i = 0; i < *n+1; ++i )
		if ( c[i] >= 2 )
			c[i+1] += c[i]>>1, c[i] &= 1;
	for ( i = 0; i < *n; ++i ) x[i] = c[i]+'0';
	upd(x,n);
}

int is_zero( char *s, int m ) {
	return m == 1 && s[0] == '0';
}

void rec( int D, int a, int b, int c ) {
	int i,j,k,h,ND;
	if ( is_zero(x,m)||is_repunit(x,m) ) {
		if ( is_zero(x,m) ) 
			return ;
		(m&1)?(cnt[b]+=m):(cnt[c]+=m);
		cnt[a]-=m;
		return ;
	}
	cnt[a] -= m, ND = m-1;
	subtr(x,&m,m-1);
	if ( !(ND & 1) )
		 cnt[c] += ND, subtr(x,&m,1), ++cnt[b], rec(ND,c,a,b);
	else cnt[b] += ND, subtr(x,&m,1), ++cnt[c], rec(ND,b,c,a);
}

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%d %s",&D,buff) ) {
		for ( cnt[A] = D, i = B; i <= C; cnt[i++] = 0 );
		if ( !D && buff[0] == '0' && (!buff[1]||buff[1] == '\n') )
			break ;
		if ( !D ) {
			puts("0 0 0");
			continue ;
		}
		for ( n = 0; buff[n]; ++n );
		for ( i = 0, j = n-1; i < j; ++i, --j )
			k = buff[i], buff[i] = buff[j], buff[j] = k;
		if ( n == 1 && buff[0] == '0' ) {
			printf("%d 0 0\n",D);
			continue ;
		}
		for ( m = 0; !(n == 1 && buff[0] == '0'); x[m++] = div2(buff,&n)+'0' );
		upd(x,&m);
		for ( z[D] = '\0', i = 0; i < D; z[i++] = '1' );
		rec(D,A,B,C);
		printf("%d %d %d\n",cnt[A],cnt[B],cnt[C]);
	}
	return 0;
}
