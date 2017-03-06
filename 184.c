/*
 * 184. Laser Lines
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
#define enc(x,y) ((y)|((x)<<14))
#define M(k) ((1 << (k))-1UL)
#define N 0x200
#define GOOD (puts("No lines were found"))
#define BAD  (puts("The following lines were found:"))
#define SQ(x) ((x)*(x))
#define tol 1e-9
#define X(k) ((int)(c[k]>>14))
#define Y(k) ((int)(c[k]&M(14)))

unsigned int c[N];
int n,*ptr[N][N],q[N][N][N],z[N][N],yes,id[N*N],v[N*N],m;

int rinp() {
	int i,x,y;
	for ( i = 0; 2 == scanf("%d %d",&x,&y) && (x+y); ) {
		assert( 0 <= x && x <= 9999 );
		assert( 0 <= y && y <= 9999 );
		c[i++] = enc(x,y);
	}
	return n = i;
}

long double f( int idx, int i, int j, long double t ) {
	long double x = (c[i]>>14)+t*(((int)(c[j]>>14))-((int)(c[i]>>14))),
		 		y = (c[i]&M(14))+t*(((int)(c[j]&M(14)))-((int)(c[i]&M(14))));
	return SQ(x-(c[idx]>>14))+SQ(y-(c[idx]&M(14)));
}

long double dist( int idx, int i, int j ) {
	long double a,b,t,na,nb;
	for ( a = 0, b = 1; fabs(b-a) > tol; ) {
		na = (2*a+b)/3, nb = (2*b+a)/3;
		f(idx,i,j,na)>f(idx,i,j,nb) ? (a = na) : (b = nb);
	}
	return f(idx,i,j,a);
}

int area( int i, int j, int k ) {
	long double ux = X(i)-X(k),
		 		uy = Y(i)-Y(k),
				vx = X(j)-X(k),
				vy = Y(j)-Y(k);
	return fabs(ux*vy-uy*vx);
}

int cmp( int x0, int x1 ) {
	int i0,j0,i1,j1,l;
	assert( x0 != x1 );
	i0 = v[x0] & M(9), j0 = v[x0] >> 9;
	i1 = v[x1] & M(9), j1 = v[x1] >> 9;
	for ( l = 0; l < ptr[i1][j1]-q[i1][j1] && l < ptr[i0][j0]-q[i0][j0]; ++l )
		if ( c[q[i0][j0][l]] != c[q[i1][j1][l]] )
			return c[q[i0][j0][l]] < c[q[i1][j1][l]] ? -1 : 1;
	assert( 0 );
}

int main() {
	int i,j,k,ok,t,l,o;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( rinp() && ++yes ) {
		/*printf("This many points %d\n",n);*/
		for ( ok = 0, j = 1; j;)
			for ( i = j = 0; i <n-1; ++i )
				if ( c[i] > c[i+1] && ++j )
					k = c[i], c[i] = c[i+1], c[i+1] = k;
		for ( i = 0; i < n-1; ++i ) 
			assert( X(i) < X(i+1)||X(i)==X(i+1)&&Y(i)<Y(i+1) );
		for ( i = 0; i < n; ++i )
			for ( j = i+2; j < n; ++j ) {
				for ( ptr[i][j] = q[i][j]+1, k = i+1; k <= j-1; ++k )
					if ( area(k,i,j) < tol && (ok = z[i][j] = yes) && (*ptr[i][j]++ = k) );
				if ( z[i][j] == yes ) *ptr[i][j]++ = j, q[i][j][0] = i;
			}
		for ( k = n; k >= 3; --k )
			for ( i = 0; (j = i+k-1) < n; ++i ) 
				for ( l = 0; z[i][j] == yes && l < ptr[i][j]-q[i][j]; ++l ) 
					for ( o = l+2; o < ptr[i][j]-q[i][j]; ++o )
						if ( !(q[i][j][l] == i && q[i][j][o] == j) )
							z[q[i][j][l]][q[i][j][o]] = 0;
		if ( !ok ) {
			GOOD;
			continue ;
		}
		BAD;
		for ( m = 0, i = 0; i < n; ++i )
			for ( j = i+2; j < n; ++j )
				if ( z[i][j] == yes ) (v[m] = ((i)|(j<<9))), id[m] = m, ++m;
		assert( m );
		for ( j = 1; j; )
			for ( j = i = 0; i < m-1; ++i )
				if ( cmp(id[i],id[i+1]) > 0 && ++j )
					k = id[i], id[i] = id[i+1], id[i+1] = k;
		for ( k = 0; k < m; ++k, putchar('\n') ) {
			i = v[id[k]]&M(9), j = v[id[k]]>>9;
			for ( l = 0; l < ptr[i][j]-q[i][j]; ++l )
				printf("(%4u,%4u)",(c[q[i][j][l]]>>14),c[q[i][j][l]]&M(14));
		}
	}
	return 0;
}
