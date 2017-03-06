/*
 * 10897. Travelling Distance
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
#define R (6371.01)
#define pi (2*acos(0.00))

typedef struct {
	long double a,b,c,d,e,f;
	char X[0x10],Y[0x10];
	long double phi,theta,x,y,z;
} locus;

int read_locus( locus *g ) {
	return 8 == scanf("%Lf %Lf %Lf %s %Lf %Lf %Lf %s",&g->a,&g->b,&g->c,g->X,&g->d,&g->e,&g->f,g->Y);
}

void locus2radians( locus *g ) {
	long double x,y;
	x = pi*(g->a*3600 + g->b*60 + g->c)/(180.00*60*60);
	y = pi*(g->d*3600 + g->e*60 + g->f)/(180.00*60*60);
	if ( 0[g->X] == 'S' )
		x = -x;
	if ( 0[g->Y] == 'W' )
		y = -y;
	g->phi = x, g->theta = y;
	g->x = cos(x)*cos(y);
	g->y = cos(x)*sin(y);
	g->z = sin(x);
}

long double min( long double x, long double y ) { return x < y ? x : y; }

int main() {
	int i,j,k,ts;
	long double x[2],y[2],z[2],co,t;
	locus L[2];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( k = 0; k <= 1; ++k ) {
			assert( read_locus(L+k) );
			locus2radians(L+k);
			x[k] = L[k].x, y[k] = L[k].y, z[k] = L[k].z;
		}
		co = (x[0]*x[1] + y[0]*y[1] + z[0]*z[1]);
		t = acos(co);
		printf("%.2Lf\n",R*min((2*pi-t),t));
	}
	return 0;
}
