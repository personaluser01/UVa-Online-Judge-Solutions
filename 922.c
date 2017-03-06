/*
 * 922. Rectangle by the Ocean
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
#define N 0x100
typedef long long i64;
#define oo (DBL_MAX-1024)
#define tol 1e-9

long double myabs( long double x ) { return x<0?-x:x; }

int ts,n;
i64 x[N],y[N],ux,uy,vx,vy,
	xx[4],yy[4],
	cx[4],cy[4];
long double A,w,B;

void norm( i64 *x, i64 *y ) {
	i64 tmp,i,j,k,l,ux,uy,vx,vy,ii = -1,
		xx = (1 << 29), yy = (1 << 29);
	for ( i = 0; i < 4; ++i )
		if ( y[i] < yy || y[i] == yy && x[i] < xx )
			xx = x[i], yy = y[i], ii = i;
	assert( ii >= 0 );
	/*
	for ( j = 0; j < 4; ++j ) {
		if ( j == ii )
			continue ;
		ux = x[j]-xx, uy = y[j]-yy;
		for ( k = 0; k < 4; ++k )
			if ( k != ii && k != j ) {
				vx = x[k], vy = y[k], l = k;
				break ;
			}
		for ( k = 0; k < 4; ++k )
			if ( k != ii && k != j && k != l ) {
				vx = x[k]-vx, vy = y[k]-vy;
				break ;
			}
		if ( ux*vy-uy*vx != 0 ) break ;
	}
	*/
	j = (ii+2)%4;
	assert( j < 4 );
	ux = x[ii], uy = y[ii], vx = x[j], vy = y[j];
	x[0] = ux, y[0] = uy;
	x[2] = vx, y[2] = vy;
}

int main() {
	int i,j,k,t,l;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i ) 
			scanf("%lld %lld",x+i,y+i);
		for ( A = 0, i = 0; i < n; ++i ) 
			j = (i+1)%n, A += (x[i]-x[j])*(y[i]+y[j]);
		if ( A < 0 ) A = -A;
		A /= 2, B = +oo;
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( j != i && x[i]==x[j]||y[i]==y[j] )
				for ( k = 0; k < n; ++k ) {
					if ( k == i || k == j )
						continue ;
					ux = x[i]-x[j], uy = y[i]-y[j];
					vx = x[k]-x[j], vy = y[k]-y[j];
					if ( ux*uy + vx*vy == 0 ) {
						w = myabs(ux*vy-uy*vx);
						if ( myabs(w-A) < myabs(B-A) ) {
							B = w;
							xx[0] = x[i], yy[0] = y[i];
							xx[1] = x[j], yy[1] = y[j];
							xx[2] = x[k], yy[2] = y[k];
							xx[3] = x[j]+ux+vx, yy[3] = y[j]+uy+vy;
							norm(xx,yy);
						}
						else if ( myabs(myabs(w-A)-myabs(B-A)) < tol ) {
							cx[0] = x[i], cy[0] = y[i];
							cx[1] = x[j], cy[1] = y[j];
							cx[2] = x[k], cy[2] = y[k];
							cx[3] = x[j]+ux+vx, cy[3] = y[j]+uy+vy;
							norm(cx,cy);
						/*	if ( (cx[0] < xx[0] || cx[0] == xx[0] && cy[0] < yy[0]) || 
								 cx[0] == xx[0] && cy[0] == yy[0] && (cx[2] < xx[2] || cx[2] == xx[2] && cy[2] < yy[2]) )*/
							if ( cx[0]<xx[0]||cx[0]==xx[0]&&cy[0]<yy[0]||cx[0]==xx[0]&&cy[0]==yy[0]&&cx[2]<xx[2]||\
								cx[0]==xx[0]&&cy[0]==yy[0]&&cx[2]==xx[2]&&cy[2]<yy[2] )
								for ( t = 0; t < 4; ++t )
									xx[t] = cx[t], yy[t] = cy[t];
						}
					}
				}
		printf("%.1Lf %lld %lld %lld %lld\n",A+tol,xx[0],yy[0],xx[2],yy[2]);
	}
	return 0;
}

