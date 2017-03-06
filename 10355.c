/*
 * 10355. Superman
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define tol 1e-9
#define N 0x10
long double SQ(long double x){return x*x;}
#define oo (DBL_MAX-1024)

char cname[0x10];
long double cx[2],cy[2],cz[2],tx[N],ty[N],tz[N],r[N],x[N],y[N],z[N],R[N],d[N],
	 left,right;
int n,g[N][N],yes,m,in[N];

int subsumes( int i, int j ) {
	if ( r[i] < r[j] )
		return 0;
	return sqrt(SQ(tx[i]-tx[j])+SQ(ty[i]-ty[j])+SQ(tz[i]-tz[j]))+r[j] <= r[i];
}

long double dist( long double x0, long double y0, long double z0, long double x1, long double y1, long double z1 ) {
	return sqrt(SQ(x0-x1)+SQ(y0-y1)+SQ(z0-z1));
}

long double dist2( long double x0, long double y0, long double z0, long double x1, long double y1, long double z1 ) {
	return (SQ(x0-x1)+SQ(y0-y1)+SQ(z0-z1));
}

void sqp( long double *a, long double *b ) {
	long double t = *a;
	*a = *b, *b = t;
}

int main() {
	int i,j,k;
	long double a,b,na,nb,t,da,db,mid,good,bad,A[N],B[N],xx,yy,zz,len;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;1 == scanf("%s",cname) && ++yes && printf("%s\n",cname);) {
		for ( i = 0; i <= 1; ++i )
			scanf("%Lf %Lf %Lf",cx+i,cy+i,cz+i);
		for ( scanf("%d",&n), i = 0; i < n; ++i ) 
			scanf("%Lf %Lf %Lf %Lf",tx+i,ty+i,tz+i,r+i);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( i != j && subsumes(i,j) ) 
					g[i][j] = yes;
		for ( k = 0; k < n; ++k )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( g[i][k] == yes && g[k][j] == yes )
						g[i][j] = yes;
		for ( i = 0; i < n; ++i )
			for ( in[i] = 0, j = 0; j < n; ++j )
				if ( g[j][i] == yes && ++in[i] );
		for ( m = 0, i = 0; i < n; ++i )
			if ( !in[i] )
				x[m] = tx[i], y[m] = ty[i], z[m] = tz[i], R[m] = r[i], ++m;
		for ( k = 0, i = 0; i < m; ++i ) {
			for ( a = 0, b = 1; fabs(b-a) > tol; ) {
				na = (2*a+b)/3, nb = (2*b+a)/3;
				da = dist2(cx[0]+na*(cx[1]-cx[0]),cy[0]+na*(cy[1]-cy[0]),cz[0]+na*(cz[1]-cz[0]),x[i],y[i],z[i]);
				db = dist2(cx[0]+nb*(cx[1]-cx[0]),cy[0]+nb*(cy[1]-cy[0]),cz[0]+nb*(cz[1]-cz[0]),x[i],y[i],z[i]);
				if ( da > db ) a = na;
				else b = nb;
			}
			d[i] = dist(cx[0]+a*(cx[1]-cx[0]),cy[0]+a*(cy[1]-cy[0]),cz[0]+a*(cz[1]-cz[0]),x[i],y[i],z[i]);
			if ( d[i] >= R[i] ) continue ;
			t = (a+b)/2;
			good = 0, bad = +10000;
			for(;fabs(good-bad) > tol;) {
				mid = (good+bad)/2;
				xx=cx[0]+(mid+t)*(cx[1]-cx[0]),yy=cy[0]+(mid+t)*(cy[1]-cy[0]),zz=cz[0]+(mid+t)*(cz[1]-cz[0]);
				dist2(xx,yy,zz,x[i],y[i],z[i]) <= SQ(R[i]) ? (good = mid):(bad = mid);
			}
			A[k] = t-good, B[k] = t+good, ++k;
		}
		for ( i = 0; i < k; ++i ) {
			if ( A[i] < 0 ) A[i] = 0;
			if ( B[i] > 1 ) B[i] = 1;
			assert( A[i] < B[i] );
		}
		if ( !k ) {
			puts("0.00");
			continue ;
		}
		for ( j = 1; j; )
			for ( i = j = 0; i < k-1; ++i )
				if ( A[i] > A[i+1] )
					++j, sqp(A+i,A+i+1), sqp(B+i,B+i+1);
		for ( len = 0, left = A[0], right = B[0], i = 1; i < k; ++i )
			if ( A[i] > right )
				len += (right-left), left = A[i], right = B[i];
			else if ( B[i] > right ) right = B[i];
		len += (right-left);
		printf("%.2Lf\n",len*100);
	}
	return 0;
}
