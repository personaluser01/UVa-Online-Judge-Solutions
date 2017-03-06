/*
 * 11373. Happy Birthday!
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
#define tol 1e-9
#define SQ(x) ((x)*(x))
#define pi (2*acos(0.0))

typedef struct {
	long double x,y;
} cell;

typedef struct {
	long double A,B,C;
} line;

long double R,h,w;
cell c[2][2],u,v;
line L[2];
int m;

long double ABS( long double x ) {
	if ( x < 0 ) return -x;
	return x;
}

long double area( cell *a, cell *b ) {
	return ABS(a->x*b->y-a->y*b->x);
}

void constr_line( line *L, cell *a, cell *b ) {
	L->A = (b->y-a->y), L->B = -(b->x-a->x);
	L->C = a->y*(b->x-a->x)-a->x*(b->y-a->y);
}

typedef struct { long double r, phi; } polarc;
polarc p[2][2];
int n;

long double value( line *L, cell *a ) {
	return L->A*a->x + L->B*a->y + L->C;
}

long double find_ang( long double co, long double si ) {
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}

int main() {
	int i,j,k;
	long double det,dx,dy,xx,yy,RHS,t[2],ang[0x100],diff,a[0x100],tmp,
		 theta,xi,phi;
	cell cc,tt[2];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 2 == scanf("%Lf %Lf",&R,&h) ) {
		for ( i = 0; i < 2; ++i ) {
			for ( j = 0; j < 2; ++j )
				scanf("%Lf %Lf",&c[i][j].x,&c[i][j].y);
			constr_line(L+i,c[i],c[i]+1);
			assert( ABS(value(L+i,c[i])) < tol );
			assert( ABS(value(L+i,c[i]+1)) < tol );
		}
		det = L[0].A*L[1].B-L[0].B*L[1].A;
		dx = -L[0].C*L[1].B+L[1].C*L[0].B;
		dy =  L[0].C*L[1].A-L[1].C*L[0].A;
		assert( fabs(det) > tol );
		xx = dx/det, yy = dy/det;
		assert( SQ(xx)+SQ(yy)<=SQ(R) );
		cc.x = xx, cc.y = yy;
		assert( ABS(value(L,&cc)) < tol );
		assert( ABS(value(L+1,&cc)) < tol );
		/*
		printf("Intersection point %Lf %Lf\n",xx,yy);
		*/

		for ( m = 0, i = 0; i < 2; ++i ) {
			det = sqrt(SQ(L[i].A)+SQ(L[i].B));
			RHS = -L[i].C/R/det;
			assert( -1 <= RHS && RHS <= 1 );
			theta = find_ang(L[i].A/det,L[i].B/det);
			xi = acos(RHS);
			if ( ABS(xi-pi/2) < tol ) {
				for ( j = 0, k = -10; k <= 10; ++k ) {
					phi = theta+xi+pi*k;
					if ( -pi <= phi && phi < pi )
						t[j++] = phi;
				}
			}
			else if ( ABS(xi) < tol ) {
				for ( j = 0, k = -10; k <= 10; ++k ) {
					phi = theta+xi+2*pi*k;
					if ( -pi <= phi && phi < pi )
						t[j++] = phi;
				}
			}
			else if ( ABS(xi-pi) < tol ) {
				for ( j = 0, k = -10; k <= 10; ++k ) {
					phi = theta+xi+2*pi*k;
					if ( -pi <= phi && phi < pi )
						t[j++] = phi;
				}
			}
			else  {
			for ( j = 0, k = -10; k <= 10; ++k ) {
				phi = theta+xi+2*pi*k;
				if ( -pi <= phi && phi < pi )
					t[j++] = phi;
				phi = theta-xi+2*pi*k;
				if ( -pi <= phi && phi < pi )
					t[j++] = phi;
			}
			}
			assert( j == 2 );
			p[i][0].phi = t[0], p[i][0].r = R;
			p[i][1].phi = t[1], p[i][1].r = R;
			ang[m++] = t[0], ang[m++] = t[1];
			for ( j = 0; j < 2; ++j ) {
				tt[j].x = R*cos(t[j]);
				tt[j].y = R*sin(t[j]);
				assert( ABS(value(L+i,tt+j)) < tol );
			}
		}
		for ( j = 1; j;)
			for ( j = i = 0; i < m-1; ++i )
				if ( ang[i] > ang[i+1] )
					++j, tmp = ang[i], ang[i] = ang[i+1], ang[i+1] = tmp;
		for ( i = 0; i < m; ++i ) {
			j = (i+1)%m;
			u.x = R*cos(ang[i])-xx, u.y = R*sin(ang[i])-yy;
			v.x = R*cos(ang[j])-xx, v.y = R*sin(ang[j])-yy;
			a[i] = area(&u,&v)/2;
			if ( ang[i] > ang[j] )
				diff = (ang[j]+2*pi-ang[i]);
			else diff = (ang[j]-ang[i]);
			a[i] += SQ(R)*(diff-sin(diff))/2;
		}
		for ( j = 1; j; )
			for ( i = j = 0; i < m-1; ++i )
				if ( a[i] < a[i+1] )
					++j, tmp = a[i], a[i] = a[i+1], a[i+1] = tmp;
		for ( w = 0, i = 0; i < m; ++i )
			w += a[i];
		assert( ABS(w-pi*SQ(R)) < tol );
		printf("%.2Lf %.2Lf\n",a[0]*h,a[m-1]*h);
	}
	return 0;
}
