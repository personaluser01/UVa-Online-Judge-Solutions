/*
status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 128
#define ABS(x) ((x)>0 ? (x) : -(x))
typedef long i64;
#define tol 1e-9
#define max(x,y) ((x)<(y)?(y):(x))
#define min(x,y) ((x)>(y)?(y):(x))

i64 Y0[N],dy[N],F,src,dst;
int n,g[N][N],yes,
	can_visit[2][N];

i64 gcd(i64 x,i64 y) { return !y ? x : gcd(y,x%y); }

int ext_euclid( i64 A, i64 B, i64 *x, i64 *y, i64 C ) {
	int tmp;
	if (!C) {
		*x = -B, *y = A;
		return 1;
	}
	return (!B)? ((C%A)==0?(*x=C/A,*y=0,1):0):(tmp=ext_euclid(B,A%B,y,x,C),*y-=(*x)*(A/B),tmp);
}

int contains_integer( double p, double q ) {
	assert( p <= q );
	if ( p >= 0 ) 
		return (i64)p < (i64)q;
	if ( p <= 0 && q >= 0 )
		return 1;
	return contains_integer(-q,-p);
}

int Stops( int j, i64 k ) {
	return k < F && (k>=Y0[j]) && (((k-Y0[j])%dy[j])==0);
}

int get_elev( i64 targ ) {
	int i;
	for ( i = 0; i < n; ++i ) 
		if ( Stops(i,targ) )
			return i;
	return -1;
}

int f( int i, int j ) {
	i64 A,B,C,x,y,d,L,t,ii,jj,period;
	double p,q,r,s;
	/*
	if ( Y0[i] == Y0[j] )
		return 1;
	*/
	C = Y0[i]-Y0[j],A = -dy[i], B = dy[j];
	d = gcd(-A,B);
	/*
	period = dy[i]*dy[j]/gcd(dy[i],dy[j]);
	if ( F-1-max(Y0[i],Y0[j]) >= period )
		return 1;
	*/
	if ( (C % d) != 0 )
		return 0;
	A/=d,B/=d,C/=d;

	if ( !ext_euclid(A,B,&x,&y,C) )
		return 0;
	/*
	 * now the general solution is
	 * x = x_0 - Bt,
	 * y = y_0 + At,
	 * where t is integer parameter
	 */
	p = (Y0[i]-F+1)/(dy[i]*B+tol)+x/(B+tol), q = x/(B+tol);
	s = -y/(A+tol), r = (F-1-Y0[j])/(dy[j]*A+tol) - y/(A+tol);
	/*printf("(%d,%d): %ld %ld, [%lf,%lf] -- [%lf,%lf]\n",i,j,x,y,p,q,r,s);*/
	if ( p > q || r > s ) return 0;
	if ( s < p || q < r ) return 0;
	p = max(p,r), q = min(q,s);
	return contains_integer(p,q);
}

int seen[N],*head,*tail,q[N];

int bfs( int src, int dst ) {
	int x,y;
	for (head=tail=q,seen[*tail++=src]=yes;head<tail&&seen[dst]!=yes;)
		for (x=*head++,y=0;y<n;++y)
			if (g[x][y]==yes&&seen[y]!=yes)
				seen[*tail++=y]=yes;
	return seen[dst]==yes;
}

int main() {
	int i,j,k,ts;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && ++yes; ) {
		for(scanf("%ld %d %ld %ld",&F,&n,&src,&dst),\
		i=0;i<n;scanf("%ld %ld",dy+i,Y0+i),++i);
		if ( dst == F ) --dst;
		if ( src == F ) --src;
		if ( src == dst ) goto ok;
		for(i=0;i<n;++i)
			for(g[i][i]=yes,j=i+1;j<n;++j)
				if(f(i,j))
					g[i][j] = g[j][i] = yes;
		if ( (i=get_elev(src)) != (j=get_elev(dst)) ) {
			if ( i == -1 || j == -1 )
				goto no;
			if ( bfs(i,j) ) goto ok;
			else goto no;
		}
		if ( i == -1 || j == -1 ) goto no;
		ok: puts("It is possible to move the furniture.");
		goto next;
		no: puts("The furniture cannot be moved.");
		next: continue;
	}
	return 0;
}

