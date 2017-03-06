/*
 * 10228. Star not a Tree?
 * TOPIC: gradient descent, numerical
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define tol 1e-9
using namespace std;
#define N 0x80
typedef long long i64;
#define oo (1<<29)

typedef struct cell { 
	double x,y;
	cell( double X, double Y ) 
	{ this->x = X, this->y = Y; }
	cell() {};
} cell;

cell operator + ( const cell &a, const cell &b ) { cell r = cell(a.x+b.x,a.y+b.y); return r; }
cell operator - ( const cell &a, const cell &b ) { cell r = cell(a.x-b.x,a.y-b.y); return r; }
cell operator * ( double t, const cell &a ) { cell r = cell(t*a.x,t*a.y); return r; }
cell operator / ( const cell &a, double t ) { cell r = cell(a.x/t,a.y/t); return r; }
double operator , ( const cell &a, const cell &b ) { return a.x*b.x + a.y*b.y; }

cell c[N];
int n;

i64 rnd( double x ) {
	i64 dx = (i64)(x),
		ux = (i64)(x)+1;
	if ( x-dx < ux-x )
		return dx;
	return ux;
}

cell delta( cell &p ) {
	cell r = cell(0,0);
	for ( int i = 0; i < n; r = r+(p-c[i])/sqrt((c[i]-p,c[i]-p)), ++i );
	return r;
}

void gradient_descent( const cell &initial_approximation ) {
	cell x[2];
	int t,i;
	double h = 0.01;
	for ( x[t=0]=initial_approximation,x[t^1]=cell(+oo,initial_approximation.y); (x[t]-x[t^1],x[t]-x[t^1])>tol*tol; t ^= 1, x[t] = x[t^1]-h*delta(x[t^1]) );
	for ( h=0,i=0; i < n; ++i ) h += sqrt((x[t]-c[i],x[t]-c[i]));
	printf("%lld\n",rnd(h));
}

int main() {
	int i,j,k,ts;
	cell s;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		for ( s = cell(0,0), i = 0; i < n; scanf("%lf %lf",&c[i].x,&c[i].y), s = s+c[i++] );
		gradient_descent(s/n);
		if ( ts ) putchar('\n');
	}
	return 0;
}

