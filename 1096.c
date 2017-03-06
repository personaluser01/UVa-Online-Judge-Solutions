/*
 * 1096. The Islands
 * TOPIC: bitonic TSP, dp, printing the path
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-12
#define N 0x80
#define S(x) ((x)*(x))
#define oo (1<<29)
#define SH 7
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define enc(t,x,y) ((x)|((y)<<SH)|((t)<<(SH+SH)))
typedef long long i64;

double min( double x, double y ) { return x<y?x:y; }

int n,b1,b2,cs,way[N][N],*ptr,out[N*N];
double d[N][N],z[N][N];
i64 x[N],y[N];

double calc_z( int i, int j ) {
	int k=(i<j?j+1:i+1);
	if ( z[i][j] < +oo )
		return z[i][j];
	if ( k == b1 ) {
		way[i][j] = enc(0,k,j);
		return z[i][j] = calc_z(k,j)+d[i][k];
	}
	else if ( k == b2 ) {
		way[i][j] = enc(1,i,k);
		return z[i][j] = calc_z(i,k)+d[j][k];
	}
	else if ( k == n ) {
		return z[i][j] = d[i][n-1]+d[j][n-1];
	}
	else {
		if ( (z[i][j] = min(calc_z(i,k)+d[j][k],calc_z(k,j)+d[i][k])) == calc_z(i,k)+d[j][k] )
			way[i][j] = enc(1,i,k);
		else way[i][j] = enc(0,k,j);
		return z[i][j];
	}
};

void dump( int i, int j ) {
	int k,l,t,o;
	if ( i == n-1 || j == n-1 ) 
		return ;
	l = way[i][j], k=(l&MASK(SH)), t=(way[i][j]>>SH)&MASK(SH), o = way[i][j]>>(SH+SH);
	*ptr++ = o|((o?t:k)<<1);
	dump(k,t);
};

double nearest( double x ) {
	return ((int)(100*(x+0.005)))/100.00;
};

double solve( int *e ) {
	int i,j,k,*left,*right,L[N],R[N];
	double ans;
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			z[i][j] = +oo;
	z[n-1][n-1] = 0, ans = calc_z(0,0);
	ptr = out, dump(0,0), left = L, right = R;
	for ( i = 0; i < ptr-out; ++i )
		if ( !(out[i]&1) )
			*left++ = out[i]>>1;
	for ( j = ptr-out-1; j >= 0; --j )
		if ( out[j]&1 )
			*right++ = out[j]>>1;
	ptr = e, *ptr++ = 0;
	for ( i = 0; i < left-L; *ptr++ = L[i++] );
	for ( i = 0; i < right-R; *ptr++ = R[i++] );
	*ptr++ = 0, *ptr = N;
	return ans;
};

int main() {
	int i,j,k,A[N+N],B[N+N];
	double a,b,ans;
#ifndef ONLINE_JUDGE
	freopen("1096.in","r",stdin);
#endif
	for(;3==scanf("%d %d %d",&n,&b1,&b2)&&(n||b1||b2);) {
		for ( i = 0; i < n; ++i )
			scanf("%lld %lld",&x[i],&y[i]);
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				d[i][j] = d[j][i] = sqrt(S(x[i]-x[j])+S(y[i]-y[j]));
		a = solve(A), k=b1,b1=b2,b2=k, b = solve(B);
		if ( A[1] == 1 && B[1] != 0 || A[1] == 1 && B[1] ==1 && a < b ) {
			printf("Case %d: %.2lf\n",++cs,nearest(a)+tol);
			for ( i = 0; ; ++i ) {
				printf("%d",A[i]);
				if ( A[i+1] != N ) putchar(' ');
				else break ;
			}
		}
		else {
			printf("Case %d: %.2lf\n",++cs,nearest(b)+tol);
			for ( i = 0; ; ++i ) {
				printf("%d",B[i]);
				if ( B[i+1] != N ) putchar(' ');
				else break ;
			}
		}
		putchar('\n');
	}
	return 0;
};

