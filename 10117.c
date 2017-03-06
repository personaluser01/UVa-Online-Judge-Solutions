/*
 * 10117. Nice Milk
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
#define N 21
#define tol 1e-11
typedef struct { long double x,y; } cell;
typedef struct { long double A,B,C,NOR; } line;
#define LSB(x) ((x)&((~(x))+1))
#define X(a) ((a)->x)
#define Y(a) ((a)->y)
#define oo (DBL_MAX-10000)
#define eps 1e-3
#define SQ(x) ((x)*(x))

long double min( long double x, long double y ) { return x < y ? x : y; }
long double max( long double x, long double y ) { return x > y ? x : y; }

int n,K,all_area,m;
long double h,paras;
cell c[N],md[N],base[N*N];
line G[N*N],B[N*N];
char bits[1 << N],deg[1 << N];

long double val_at( line *L, cell *c ) { return ((L->A)*c->x + (L->B)*c->y + (L->C))/(L->NOR); }

void line_eq( cell *a, cell *b, line *L ) {
	L->A =  (b->y-a->y);
	L->B = -(b->x-a->x);
	/*assert( fabs(L->A) > tol||fabs(L->B) > tol );*/
	L->C = a->y*(b->x-a->x)-a->x*(b->y-a->y);
	L->NOR = sqrt(L->A*L->A + L->B*L->B);
}

void get_point( cell *a, cell *b, long double t, cell *q ) {
	q->x = a->x + (b->x-a->x)*t;
	q->y = a->y + (b->y-a->y)*t;
}

int cmp_cell( cell *a, cell *b ) {
	if ( fabs(X(a)-X(b)) < tol && fabs(Y(a)-Y(b)) < tol )
		return 0;
	if ( fabs(X(a)-X(b)) < tol )
		return Y(a) < Y(b) ? -1 : 1;
	return X(a) < X(b) ? -1 : 1;
}

long double Dist( cell *a, line *L ) { return fabs(val_at(L,a)); }


long double find_t( cell *a, cell *b, line *L ) {
	long double low,high,mid,H = h*L->NOR,t,P,Q;
	cell m;
	get_point(a,b,1.00,&m);
	/*
	assert( Dist(&m,L) >= h );
	*/
	P = L->A*a->x + L->B*a->y + L->C;
	Q = L->A*b->x + L->B*b->y + L->C;
	/*
	assert( fabs(P-Q) > tol );
	*/
	t = (H-P)/(Q-P);
	if ( 0 <= t && t <= 1 )
		return t;
	t = (-P-H)/(Q-P);
/*	assert( 0 <= t && t <= 1 );*/
	return t;
	/*
	for ( low = 0, high = 1; fabs(high-low) >= tol; ) {
		mid = (low+high)/2;
		get_point(a,b,mid,&m);
		if ( Dist(&m,L) < h )
			low = mid;
		else high = mid;
	}
	return high;
	*/
}

long double volume( cell *c, int n ) {
	long double w = 0;
	int i,j;
	for ( i = 0; i < n; ++i ) {
		j = (i+1)%n;
		w += (c[i].x-c[j].x)*(c[i].y+c[j].y);
	}
	return fabs(w)/2.00;
}

int same_orientation( line *L, line *R ) {
	long double si = (L->A*R->B-L->B*R->A),
		 		co = L->A*R->A+L->B*R->B;
	return fabs(si) <= eps && co >= 0;
}

void rec( int lim, cell *c, int n ) {
	int i,j,k,idx,l,t,ii,jj,nn,right,left,cuts = 0;
	line L,LL;
	long double tmp,w,ti,tj;
	cell e[2],nc[N];

	if ( all_area||fabs(paras) <= tol ) {
		all_area = 1;
		return ;
	}

	if ( !lim ) {
		paras = min(paras,volume(c,n));
		if ( fabs(paras) <= tol )
			all_area = 1;
		return ;
	}
	/*
	printf("lim = %d, n = %d, m = %d\n",lim,n,m);
	*/
	for ( i = 0; i < n; ++i ) {
		j = (i+1)%n;
		if ( 0 == cmp_cell(c+i,c+j) )
			goto nx;
		line_eq(c+i,c+j,&L);
		for ( k = 0; k < m; ++k ) 
			if ( same_orientation(G+k,&L) )
				goto nx;
		for ( k = -1, w = -1.00, k = 0; k < n; ++k )
			if ( k != i && k != j && (tmp = Dist(c+k,&L)) > w )  
				w = tmp, idx = k;
		if ( idx == -1 ) goto nx;
		/*assert( idx >= 0 );*/

		if ( w <= h ) {
			all_area = 1, paras = 0;
			return ;
		}
		/*assert( w > h );*/

		for ( l = i;; l = jj ) {
			ii = l, jj = (l+n-1)%n;
			if ( Dist(c+jj,&L) >= h )
				break ; 
		}
		/*assert( Dist(c+ii,&L) < h );
		assert( Dist(c+jj,&L) >= h );
		*/
		ti = find_t(c+ii,c+jj,&L);
		get_point(c+ii,c+jj,ti,e);
		/*assert( fabs(Dist(e,&L)-h) <= eps );*/
		left = ii;

		for ( l = j;;l = jj ) {
			ii = l, jj = (l+1)%n;
			if ( Dist(c+jj,&L) >= h )
				break ; 
		}
		/*assert( Dist(c+ii,&L) < h );*/
		/*assert( Dist(c+jj,&L) >= h );*/
		tj = find_t(c+ii,c+jj,&L);
		get_point(c+ii,c+jj,tj,e+1);
		/*assert( fabs(Dist(e+1,&L)-h) <= eps );*/
		right = jj;

		for ( nn = 0, k = idx; k != left; ) {
			nc[nn++] = c[k];
			k = (k+1) % n;
		}
		nc[nn++] = e[0], nc[nn++] = e[1];
		for ( k = jj; k != idx; ) {
			nc[nn++] = c[k];
			k = (k+1)%n;
		}
		G[m++] = L;
		line_eq(e,e+1,&LL);
		/*printf("Line L: %.2Lfx + %.2Lfy + %.2Lf vs Line LL: %.2Lfx + %.2Lfy + %.2Lf\n",L.A,L.B,L.C,LL.A,LL.B,LL.C);
		printf("sin = %Lf\n",L.A*LL.B-L.B*LL.A);
		printf("cos = %Lf\n",L.A*LL.A+L.B*LL.B);
		*/
		/*assert( same_orientation(&L,&LL) );
		assert( fabs(Dist(e,&L)-h) <= eps );
		assert( fabs(Dist(e+1,&L)-h) <= eps );
		*/
		rec( lim-1, nc, nn ), ++cuts;
		if ( all_area ) return ;
		--m;
		nx: continue ;
	}
	if ( !cuts ) {
		paras = min(paras,volume(c,n));
		if ( fabs(paras) <= tol )
			all_area = 1;
	}
}

int intersect( line *L, line *R, cell *c ) {
	long double si = L->A*R->B - L->B*R->A;
	if ( fabs(si) <= tol )
		return 0;
	c->x = (-L->C*R->B+L->B*R->C)/si;
	c->y = (-L->A*R->C+L->C*R->A)/si;
	return 1;
}

long double dist( cell *a, cell *b ) {
	return sqrt(SQ(a->x-b->x)+SQ(a->y-b->y));
}

int between( cell *a, cell *b, cell *c ) {
	long double d1,d2,d3;
	d1 = dist(a,b), d2 = dist(b,c), d3 = dist(a,c);
	return fabs(d3-d1-d2) <= tol;
}

void solve( unsigned int u ) {
	cell cc[2][N*N],e[2];
	int i,j,k,t,m[2],idx,left,right,ii,jj,cnt;
	unsigned int v;
	line L,R;
	long double tmp,w;

	for ( t = 0, i = 0; i < n; ++i )
		cc[t][i] = c[i];
	m[t] = n;

	for ( v = u; v && m[t] >= 3; v -= LSB(v) ) {
		i = deg[LSB(v)], j = (i+1) % n;
		/*
		assert( 0 <= i && i <= n-1 );
		*/
		line_eq(c+i,c+j,&L);
		for ( w = -1, idx = -1, k = 0; k < m[t]; ++k )
			if ( (tmp = Dist(cc[t]+k,&L)) > w )
				w = tmp, idx = k;
		if ( w <= h ) {
			all_area = 1;
			paras = 0;
			return ;
		}
		for ( cnt = 0, left = -1, k = idx; cnt <= m[t]; k = jj, ++cnt ) {
			ii = k, jj = (k+1)%m[t];
			line_eq(cc[t]+ii,cc[t]+jj,&R);
			if ( intersect(B+i,&R,e) && between(cc[t]+ii,e,cc[t]+jj)) {
				left = ii;
				break ;
			}
		}
		for ( cnt = 0, right = -1, k = idx; cnt <= m[t];k = jj, ++cnt ) {
			ii = k, jj = (k+m[t]-1)%m[t];
			line_eq(cc[t]+ii,cc[t]+jj,&R);
			if ( intersect(B+i,&R,e+1) && between(cc[t]+ii,e+1,cc[t]+jj)) {
				right = ii;
				break ;
			}
		}
		if ( left == -1||right == -1 ) {
			continue ;
		}
		for ( k = 0, (t^=1), m[t] = 0, ii = idx; ii != left; ii = (ii+1)%m[t^1] )
			cc[t][k++] = cc[t^1][ii];
		cc[t][k++] = cc[t^1][left];
		if ( 0 != cmp_cell(cc[t^1]+left,e) )
			cc[t][k++] = e[0]; 
		if ( 0 != cmp_cell(cc[t^1]+right,e+1) )
			cc[t][k++] = e[1];
		for ( ii = right; ii != idx; ii = (ii+1)%m[t^1] )
			cc[t][k++] = cc[t^1][ii];
		m[t] = k;
	}
	paras = min(paras,volume(cc[t],m[t]));
}

int main() {
	int i,j,k,l,yes = 0;
	unsigned int u;
	long double total_area,w,tmp,a,b,na,nb,
		 low,mid,high;
	line L,R;
	cell pa,pb;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( u = 0; u < (1 << N); ++u )
		bits[u] = bits[u>>1] + (u&1);
	for ( i = 0; i < N; ++i )
		deg[1 << i] = i;
	for (;3 == scanf("%d %d %Lf",&n,&K,&h) && !(fabs(h)<tol&&n==0&&K==0) && ++yes;) {
		for ( i = 0; i < n; scanf("%Lf %Lf",&c[i].x,&c[i].y), ++i );
		total_area = volume(c,n);
		if ( K > n ) K = n;
		if ( !K||fabs(h)<=tol ) {
			puts("0.00");
			continue ;
		}
		for ( i = 0; i < n; ++i ) {
			j = (i+1)%n;
			line_eq(c+i,c+j,&L);
			for ( w = -1, k = 0; k < n; ++k )
				if ( k != i && k != j )
					if ( (tmp = Dist(c+k,&L)) > w )
						w = tmp, md[i].x = c[k].x, md[i].y = c[k].y;
			if ( w <= h ) {
				printf("%.2Lf\n",total_area);
				goto ok;
			}
			R.A = L.B; R.B = -L.A; R.C = -R.A*md[i].x-R.B*md[i].y, R.NOR = sqrt(SQ(R.A)+SQ(R.B));
			/*
			assert( fabs(val_at(&R,md+i)) <= tol );
			*/
			intersect(&L,&R,base+i);
			/*
			assert( fabs(val_at(&R,base+i)) <= tol );
			assert( fabs(val_at(&L,base+i)) <= tol );
			*/
			get_point(base+i,md+i,0,&pa);
			/*
			assert( Dist(&pa,&L) < h );
			*/
			get_point(base+i,md+i,1,&pa);
			/*
			assert( Dist(&pa,&L) >= h );
			*/

			for ( low = 0, high = 1.00; fabs(high-low) > tol; ) {
				mid = (low+high)/2;
				get_point(base+i,md+i,mid,&pa);
				if ( Dist(&pa,&L) < h )
					low = mid;
				else high = mid;
			}
			get_point(base+i,md+i,(high+low)/2,&pa);
			/*
			assert( fabs(val_at(&R,&pa)) <= tol );
			*/
			B[i].A = L.A, B[i].B = L.B, B[i].C = -B[i].A*pa.x - B[i].B*pa.y, B[i].NOR = sqrt(SQ(B[i].A)+SQ(B[i].B));
			/*
			assert( fabs(val_at(B+i,&pa)) <= tol );
			assert( fabs(Dist(md+i,B+i)+Dist(&pa,&L)-w) <= tol );
			assert( fabs(Dist(&pa,&L)-h) <= eps );
			*/
		}
		for ( paras = +oo, all_area = 0, u = 0; u < (1 << n) && !all_area; ++u )
			if ( bits[u] <= K ) {
				solve(u);
			}
		if ( all_area )
			printf("%.2Lf\n",total_area);
		else
			printf("%.2Lf\n",total_area-paras+tol);
		ok:;
	}
	return 0;
}
