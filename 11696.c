/*
 * 11696. Beacons
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol (1e-7)
#define pi (2*acos(0.00))
#define DIM 2
#define N 0x400
#define S(x) ((x)*(x))
enum { X, Y };

double x[N][DIM],c[N][DIM],r[N],left[4*N],right[4*N],a[4*N],b[4*N];
int n,m,len[N],yes,g[N][N],seen[N],indeed,rank[N],p[N];

void link( int x, int y ) {
	if ( rank[x] > rank[y] )
		p[y]=x;
	else {
		p[x] = y;
		if ( rank[x] == rank[y] ) ++rank[y];
	}
}

int find( int x ) {
	return p[x]==x?x:find(p[x]);
}

void merge( int x, int y ) {
	link(find(x),find(y));
}

void make_set( int x ) {
	rank[p[x] = x] = 0;
}

double get_angle( double a, double b, double c, double d ) {
	double co = (a*c + b*d),
		   si = (a*d - b*c),
		   A = sqrt(a*a+b*b),
		   B = sqrt(c*c+d*d),
		   D = A*B;
	co /= D, si /= D;
	if ( fabs(co-1.00) < tol )
		return 0;
	if ( fabs(co+1.00) < tol )
		return pi;
	if ( fabs(si-1.00) < tol )
		return pi/2;
	if ( fabs(si+1.00) < tol )
		return -pi/2;
	if ( co >= 0 && si >= 0 ) 
		return acos(co);
	if ( co >= 0 && si < 0 )
		return asin(si);
	if ( co < 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}

void dfs( int x ) {
	int y;
	for ( seen[x] = indeed, y = 0; y < n; ++y )
		if ( g[x][y] == yes && seen[y] != indeed )
			dfs(y);
}

int inside_rift( int i, int j ) {
	double u = x[j][X]-x[i][X],
		   v = x[j][Y]-x[i][Y],
		   ang = get_angle(1,0,u,v);
	int low,high,mid;
	if ( !len[i] ) return 0;
	if ( left[0] > ang ) return 0;
	if ( right[len[i]-1] < ang )
		return 0;
	/*if ( right[len[i]-1] < ang || left[0] > ang )
		return 0;
	*/
	assert( right[len[i]-1] >= ang );
	assert( left[0] <= ang );
	if ( right[0] >= ang )
		return 1;
	assert( right[0] < ang );
	for ( low = 0, high = len[i]-1; low+1 < high; )
		right[mid=(low+high)/2]>=ang?(high=mid):(low=mid);
	return left[high] <= ang;
}

typedef struct { double x,y; } cell;
cell e[4*N];

int cmp( const void *a, const void *b ) {
	cell *A = (cell *)a,
		 *B = (cell *)b;
	if ( fabs(A->x-B->x) < tol ) {
		if ( fabs(A->y-B->y) < tol )
			return 0;
		if ( A->y < B->y )
			return -1;
		return 1;
	}
	if ( A->x < B->x )
		return -1;
	return 1;
}

int main() {
	int i,j,k,l,t,ts;
	double u,v,d,tau,phi,L,R;
	for ( scanf("%d",&ts); ts-- && ++yes && 2 == scanf("%d %d",&n,&m); printf("%d\n",k-1) ) {
		for ( i = 0; i < n; ++i ) 
			for ( j = 0; j < DIM; scanf("%lf",&x[i][j++]) );
		for ( i = 0; i < m; scanf("%lf",&r[i++]) ) 
			for ( j = 0; j < DIM; scanf("%lf",&c[i][j++]) );
		for ( i = 0; i < n; ++i ) make_set(i);
		for ( i = 0; i < n; ++i ) {
			for ( j = 0; j < m; ++j ) {
				u = (c[j][X]-x[i][X]), v = (c[j][Y]-x[i][Y]), d = sqrt(u*u+v*v);
				tau = get_angle(1,0,u,v), phi = asin(r[j]/d);
				assert( d >= r[j] );
				a[j] = tau-phi, b[j] = tau+phi;
			}
			/*
			 * formation of rifts here
			 */
			for ( k = 0, j = 0; j < m; ++j ) {
				if ( -pi < a[j] && b[j] <= pi ) {
					left[k] = a[j], right[k++] = b[j];
					continue ;
				}
				if ( a[j] <= -pi && b[j] > -pi ) {
					left[k] = a[j]+2*pi, right[k++] = pi;
					left[k] = -pi, right[k++] = b[j];
					continue ;
				}
				if ( a[j] <= -pi && b[j] <= -pi ) {
					left[k] = a[j]+2*pi, right[k++] = b[j]+2*pi;
					continue ;
				}
				if ( b[j] > pi && a[j] <= pi ) {
					left[k] = a[j], right[k++] = pi;
					left[k] = -pi, right[k++] = b[j]-2*pi;
					continue ;
				}
				if ( b[j] > pi && a[j] > pi ) {
					left[k] = a[j]-2*pi, right[k++] = b[j]-2*pi;
					continue ;
				}
			}
			for ( j = 0; j < k; ++j ) {
				e[j].x = left[j], e[j].y = right[j];
				assert( -pi <= e[j].x && e[j].y <= pi );
			}
			qsort(e,len[i]=k,sizeof *e,cmp);
			if ( !k ) {
				for ( j = i+1; j < n; ++j )
					g[i][j] = g[j][i] = yes;
				continue ;
			}
			k = 0;
			if ( fabs(-pi-e[0].x) >= tol )
				left[k] = -pi, right[k++] = e[0].x;
			for ( L = e[0].x, R = e[0].y, j = 1; j < len[i]; ++j ) {
				if ( e[j].x > R ) {
					left[k] = R, right[k++] = e[j].x;
					L = e[j].x, R = e[j].y;
					continue ;
				}
				if ( e[j].y > R ) R = e[j].y;
			}
			if ( fabs(R-pi) >= tol )
				left[k] = R, right[k++] = pi;
			/*
			printf("Open directions for %d\n",i);
			for ( j = 0; j < k; ++j )
				printf("%4.2lf %4.2lf\n",left[j]/pi*180,right[j]/pi*180);
			*/
			/* now construct the graph */
			for ( j = 0; j < k-1; ++j ) {
				assert( right[j] >= left[j] );
				assert( right[j] <= left[j+1] );
				assert( left[j+1] <= right[j+1] );
			}
			for ( len[i] = k, j = 0; j < n; ++j )
				if ( i != j && g[i][j] != yes && inside_rift(i,j) ) {
					g[i][j] = g[j][i] = yes;
					merge(i,j);
				}
		}
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j ) {
				if ( g[i][j] != yes && find(i) != find(j) ) {
					for ( k = 0; k < m; ++k ) {
						tau = (x[j][X]-x[i][X])*(c[k][X]-x[i][X])+(x[j][Y]-x[i][Y])*(c[k][Y]-x[i][Y]);
						tau /= (S(x[j][X]-x[i][X]) + S(x[j][Y]-x[i][Y]));
						if ( 0 <= tau && tau <= 1 )
							if ( S(c[k][X]-x[i][X]-(x[j][X]-x[i][X])*tau) + S(c[k][Y]-x[i][Y]-(x[j][Y]-x[i][Y])*tau) <= S(r[k]) )
								goto next;
					}
				}
				g[i][j] = g[j][i] = yes, merge(i,j);
				next:;
			}
		/* ...and run dfs... */
		for ( ++indeed, k = 0, i = 0; i < n; ++i )
			if ( seen[i] != indeed && ++k )
				dfs(i);
	}
	return 0;
}

