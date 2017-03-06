/*
 * 11519. Logo 2
 * status: Accepted
 */
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <vector>
using namespace std;
#define x first
#define y second
#define tol 1e-9
#define N 0x400
#define pi (2*acos(0.0))

int n,m[2],Arg[2][N],carg[N];
char comm[2][N][0x100],arg[2][N][0x100],qu[0x100],
	 command[N][0x100];

long double Len( pair<long double,long double> &a ) { return sqrt(a.x*a.x+a.y*a.y); }

void simul( int t, pair<long double,long double> &pos, int &ang ) {
	pair<long double,long double> r = pos;
	int phi = ang;
	int i,j,k;

	for ( i = 0; i < m[t]; ++i ) {
		switch ( 0[comm[t][i]] ) {
			case 'f': r.x += Arg[t][i]*cos(phi*pi/180.0), r.y += Arg[t][i]*sin(phi*pi/180.0);
					  break ;
			case 'b': r.x -= Arg[t][i]*cos(phi*pi/180.0), r.y -= Arg[t][i]*sin(phi*pi/180.0);
					  break ;
			case 'l': phi += Arg[t][i], phi %= 360;
					  while ( phi < 0 ) phi += 360;
					  break ;
			case 'r': phi -= Arg[t][i], phi %= 360;
					  while ( phi < 0 ) phi += 360;
					  break ;
			default: assert( 0 );
		}
	}
	pos = r, ang = phi;
}

void simul2( pair<long double,long double> &pos, int &ang ) {
	pair<long double,long double> r = pos;
	int phi = ang;
	int i,j,k;

	for ( i = 0; i < m[0]+1+m[1]; ++i ) {
		switch ( 0[command[i]] ) {
			case 'f': r.x += carg[i]*cos(phi*pi/180.0), r.y += carg[i]*sin(phi*pi/180.0);
					  break ;
			case 'b': r.x -= carg[i]*cos(phi*pi/180.0), r.y -= carg[i]*sin(phi*pi/180.0);
					  break ;
			case 'l': phi += carg[i], phi %= 360;
					  while ( phi < 0 ) phi += 360;
					  break ;
			case 'r': phi -= carg[i], phi %= 360;
					  while ( phi < 0 ) phi += 360;
					  break ;
			default: assert( 0 );
		}
	}
	pos = r, ang = phi;
}


long double getang( long double a, long double b, long double c, long double d ) {
	long double co = a*c + b*d,
		 		si = a*d - b*c,
				L = sqrt((a*a+b*b)*(c*c+d*d));
	assert( fabs(L) > tol );
	co /= L, si /= L;
	assert( fabs(co) <= 1 && fabs(si) <= 1 );
	/*
	if ( fabs(co+1) < tol )
		return -pi;
		*/
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co < 0 && si >= 0 )
		return acos(co);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	return -pi+acos(-co);
}

int Rint( long double x ) { return (int)(x+tol); }

int main() {
	int i,j,k,t,ts,res;
	long double mx,my,tau,alpha,beta;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {

		for ( t = 0, scanf("%d",&n), 0[m] = 1[m] = 0, i = 0; i < n; ++i ) {
			scanf("%s %s",comm[t][m[t]],arg[t][m[t]]);
			if ( 0[arg[t][m[t]]] == '?' ) { strcpy(qu,comm[t][m[t]]), t = 1; continue; }
			Arg[t][m[t]] = atoi(arg[t][m[t]]), ++m[t];
		}

		pair<long double,long double> a[2];
		int ang[2];

		for ( i = 0; i < m[0]; ++i )
			carg[i] = Arg[0][i], strcpy(command[i],comm[0][i]);
		for ( i = 0; i < m[1]; ++i )
			carg[m[0]+1+i] = Arg[1][i], strcpy(command[i+m[0]+1],comm[1][i]);
		strcpy(command[m[0]],qu);

		long double w,tmp;
		if ( 0[qu] == 'l'||0[qu] == 'r' ) {
			w = DBL_MAX-1024;
			for ( j = 0; j <= 359; ++j ) {
				carg[m[0]] = j;
				a[0].x = a[0].y = ang[0] = 0;
				simul2(a[0],ang[0]);
				tmp = fabs(Len(a[0]));
				if ( tmp < w )
					w = tmp, res = j;
			}
			goto nx;
		}

		for ( t = 0; t <= 1; ++t )
			a[t].x = a[t].y = ang[t] = 0, simul(t,a[t],ang[t]);

		if ( fabs(Len(a[0])) < tol && fabs(Len(a[1])) < tol ) {
			res = 0;
			goto nx;
		}

		mx = a[1].x, my = a[1].y;
		ang[1] += ang[0];
		a[1].x = cos(ang[0]*pi/180.0)*mx-sin(ang[0]*pi/180.0)*my;
		a[1].y = sin(ang[0]*pi/180.0)*mx+cos(ang[0]*pi/180.0)*my;

	    a[1].x += a[0].x, a[1].y += a[0].y;

		/*tau = getang(a[0].x,a[0].y,a[1].x,a[1].y);*/
		if ( Len(a[1]) < tol ) {
			res = 0;
			goto nx;
		}
		alpha = getang(1,0,a[1].x,a[1].y);
		beta = getang(1,0,cos(ang[0]*pi/180.0),sin(ang[0]*pi/180.0));
		if ( 0[qu] == 'f' ) {
			if ( fabs(alpha-beta) < tol )
				res = -Rint(Len(a[1]));
			else
				res = Rint(Len(a[1]));
		}
		else {
			if ( fabs(alpha-beta) < tol )
				res = Rint(Len(a[1]));
			else
				res = -Rint(Len(a[1]));
		}
		nx: printf("%d\n",res);
	}
	return 0;
}

