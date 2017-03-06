/*
 * 12200. Darts
 * TOPIC: probability, dp, systems of linear equations, swerc 2009
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#define N 0x200
#define L 20
#define oo (1L<<29)
using namespace std;
enum { A, B };

int m,n,c[] = {1,18,4,13,6,10,15,2,17,3,19,7,16,8,11,14,9,12,5,20};
long double p[2][N][N];

long double f( long double x ) { return max((long double)-1.00,min((long double)1.00,x)); }

long double calc_p( int t, int m, int n ) {
	int i,j,k;

	if ( p[t][m][n] < +oo )
		return p[t][m][n];

	assert( m >= 20 && n >= 20 );

	if ( m >= 20 && n >= 20 ) {
		if ( t == A ) {
			for ( p[t][m][n] = 0, i = 0; i < L; ++i ) 
				p[t][m][n] += f((1-calc_p(t^1,m-c[i],n))/L);
		}
		else {
			for ( p[t][m][n] = -oo, i = 0; i < L; ++i ) {
				j = (i+1)%L, k = (i-1+L)%L;
				p[t][m][n] = max(p[t][m][n],(1-calc_p(t^1,m,n-c[i]))+(1-calc_p(t^1,m,n-c[k]))+(1-calc_p(t^1,m,n-c[j])));
			}
			p[t][m][n] /= 3.00;
		}
		return p[t][m][n] = f(p[t][m][n]);
	}
};

int main() {
	int i,j,k,l;
	long double a[2][2],b[2],det,da,db,pp,qq;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	assert( L == sizeof(c)/sizeof *c );
	for ( i = A; i <= B; ++i )
		for ( j = 0; j < N; ++j )
			for ( k = 0; k < N; p[i][j][k++] = +oo );
	for ( m = 1; m < N; p[A][m++][0] = 0.00 );
	for ( n = 1; n < N; p[B][0][n++] = 0.00 );
	for ( m = 1; m < N; p[B][m++][0] = 1.00 );
	for ( n = 1; n < N; p[A][0][n++] = 1.00 );
	for ( m = 1; m < N; ++m )
		for ( n = 1; n < N; ++n )
			if ( m < L || n < L ) {
			for ( p[B][m][n] = -oo, l = 0; l < L; ++l ) {
				memset(a,0,sizeof a);
				memset(b,0,sizeof b);
				a[A][A] = a[B][B] = 1.00;
				for ( i = 0; i < L; ++i )
					if ( m < c[i] )
						a[A][B] += 1.00/L, b[A] += 1.00/L;
					else b[A] += (1-p[B][m-c[i]][n])/L;
				i = l, j = (l+1)%L, k = (l-1+L)%L;
				if ( c[i] > n ) 
					a[B][A] += 1/3.00, b[B] += 1/3.00;
				else b[B] += (1-p[A][m][n-c[i]])/3.00;
				if ( c[j] > n ) 
					a[B][A] += 1/3.00, b[B] += 1/3.00;
				else b[B] += (1-p[A][m][n-c[j]])/3.00;
				if ( c[k] > n ) 
					a[B][A] += 1/3.00, b[B] += 1/3.00;
				else b[B] += (1-p[A][m][n-c[k]])/3.00;
				det = a[A][A]*a[B][B]-a[A][B]*a[B][A];
				da = b[A]*a[B][B]-b[B]*a[A][B];
				db = a[A][A]*b[B]-a[B][A]*b[A];
				pp = f(da/det), qq = f(db/det);
				if ( qq > p[B][m][n] ) {
					p[A][m][n] = pp;
					p[B][m][n] = qq;
				}
				// printf("%Lf\n",pp);
			}
			}
	for (;1==scanf("%d",&n) && n>0;) 
		printf("%.12Lf %.12Lf\n",calc_p(A,n,n),calc_p(B,n,n));
	return 0;
}

