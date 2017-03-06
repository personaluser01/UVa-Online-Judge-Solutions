/*
 * 2411. Ants
 * TOPIC: weighted matching
 * status: surprisingly TLE
 * regular hungarian algo I've written, that has worked all along -- but TLE on this one. Numerical issues too, sometimes
 * slackness gives assertion error. Numerical instability with floating points?
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define N 0x80
#define Q (0x400)
#define oo (DBL_MAX-0x400)
#define tight(x,y) (fabs(w[x][y]-p[S][x]-p[T][y]) < tol)
#define tol (1e-9)
#define slackness(x,y) (tight(x,y) || w[x][y]<=p[S][x]+p[T][y])
enum { S, T };
double min(double x,double y ) { return x<y?x:y; }
double max(double x,double y ) { return x>y?x:y; }

int q[Q],head,tail,cnt,n,seen[2][N],visited[N],yes,mate[2][N],dig[256],
	*ptr[2],o[2][N];
double w[N][N],p[2][N],delta;

int pop() {
	int x = q[head++];
	head &= (Q-1); --cnt;
	return x;
}

void push( int x ) {
	q[tail++] = x; ++cnt; tail &= (Q-1);
}

int alt_path( int x ) {
	int y;
	if ( seen[S][x] == yes )
		return 0;
	for ( seen[S][x] = yes, y = 0; y < n; ++y )
		if ( tight(x,y) ) {
			if ( mate[T][y] == -1 || alt_path(mate[T][y]) ) {
				mate[S][mate[T][y]=x]=y;
				return 1;
			}
		}
		else assert( slackness(x,y) );
	return 0;
}

int bpm() {
	int x,y,i,flag,k;
	do {
		for ( flag = 0, ++yes, k = cnt; k--; )
			if ( alt_path(x = pop()) )
				flag = 1;
			else push(x);
	} while ( flag );
	return n-cnt;
}

void dfs( int x ) {
	int y;
	if ( seen[S][x] == yes ) return ;
	for ( seen[S][x] = yes, *ptr[S]++ = x, y = 0; y < n; ++y )
		if ( tight(x,y) ) {
			assert( mate[T][y] != -1 );
			if ( seen[T][y] != yes )
				seen[T][y] = yes, *ptr[T]++ = y;
			dfs(mate[T][y]);
		}
		else 
			delta = min(delta,-w[x][y]+p[S][x]+p[T][y]);
}

void check() {
	int x,y;
	for ( x = 0; x < n; ++x )
		for ( y = 0; y < n; ++y ) {
				/*
			if ( !slackness(x,y) )
				printf("These: (%d,%d) %lf\n",x,y,p[S][x]+p[T][y]-w[x][y]);
			assert(slackness(x,y));
			*/
			if ( !slackness(x,y) )
				w[x][y] = p[S][x]+p[T][y];
		}
}

void hungarian() {
	int x,y,i,j,k;

	for ( head = tail = cnt = 0, x = 0; x < n; push(x), mate[S][x] = mate[T][x] = -1, ++x );
	memset(p,0,sizeof p);
	for ( x = 0; x < n; ++x )
		for ( p[S][x] = -oo, y = 0; y < n; ++y )
			p[S][x] = max(p[S][x],w[x][y]);

	check();

	for (;bpm()<n;) {
		for ( ptr[S]=o[S],ptr[T]=o[T],delta = +oo, ++yes, k = cnt, i = head; k--; dfs(q[i++]), i &= (Q-1) );
		assert( delta > 0);
		for ( k = S; k <= T; ++k )
			for ( i = 0; i < ptr[k]-o[k]; ++i )
				if ( k == S )
					p[k][o[k][i]] -= delta;
				else p[k][o[k][i]] += delta;
		check();
	}
	for ( x = 0; x < n; ++x )
		printf("%d\n",mate[S][x]+1);
}

double getdouble() {
	int sign = 1,ch;
	double n = 0;
	while ( (ch = getchar()) != EOF && !(ch == '-' || dig[ch]) );
	if ( ch == EOF ) return +oo;
	if ( ch == '-' ) {
		sign = -1;
		ch = getchar();
	}
	for( n = ch-'0'; (ch = getchar()) != EOF && dig[ch]; n = 10*n+ch-'0' );
	return n*sign;
}

int main() {
	int i,j,k,ts = 0;
	double x[2][N],y[2][N],xx,yy,D;
#ifndef ONLINE_JUDGE
	freopen("1411.in","r",stdin);
#endif
	for ( i = '0'; i <= '9'; dig[i++] = 1 );
	while ( (D=getdouble()) < +oo ) {
		n = (int)D;
		for ( k = S; k <= T; ++k )
			for ( i = 0; i < n; ++i )
				x[k][i] = getdouble(), y[k][i] = getdouble();
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j ) {
				xx = x[S][i]-x[T][j];
				yy = y[S][i]-y[T][j];
				w[i][j] = -sqrt(xx*xx+yy*yy);
			}
		if ( ts++ ) putchar('\n');
		hungarian();
	}
	return 0;
}

