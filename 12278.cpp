/*
 * 12278. Three-Sided Dice
 * TOPIC: geometry, probability, vector calculus
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#define DIM 3
#define tol 1e-9
using namespace std;

const long double pi = 2*acos(0.00), L = (long double)10000.00;

struct cell {
	long double x[DIM];
	cell( long double a, long double b, long double c ) {
		0[x] = a, 1[x] = b, 2[x] = c;
	};
	cell() { memset(x,0,sizeof x); };
	long double operator [] ( int i ) const { return x[i]; };
	long double getlen() const {
		long double s = 0;
		for ( int i = 0; i < DIM; s += x[i]*x[i], ++i );
		return sqrt(s);
	};
};

cell operator + ( const cell &a, const cell &b ) { return cell(a[0]+b[0],a[1]+b[1],a[2]+b[2]); };
cell operator - ( const cell &a, const cell &b ) { return cell(a[0]-b[0],a[1]-b[1],a[2]-b[2]); };
long double operator , ( const cell &a, const cell &b ) {
	long double s = 0;
	for ( int i = 0; i < DIM; s += a[i]*b[i], ++i );
	return s;
};
cell operator * ( const cell &a, const cell &b ) {
	cell r;
	for ( int j,k,i = 0; i < DIM; ++i ) 
		k=((j=(i+1)%DIM)+1)%DIM, r.x[i] = a[j]*b[k]-a[k]*b[j];
	return r;
};
long double operator ^ ( const cell &a, const cell &b ) {
	long double A = a.getlen(), B = b.getlen(),
		 		co = min((long double)1.00,max((long double)-1.00,(a,b)/A/B));
	return acos(co);
};

bool operator < ( const cell &a, const cell &b ) {
	for ( int i = 0; i < DIM; ++i )
		if ( fabs(a[i]-b[i]) >= tol )
			return a[i]<b[i];
	return false ;
};

bool operator == ( const cell &a, const cell &b ) {
	return !(a<b||b<a);
};

int signum( long double t ) {
	if ( fabs(t) < tol ) return 0;
	return t<0?-1:1;
};

cell p[3],t,n,m,ZERO;

int main() {
	int i,j,k,l,u;
	bool ok;
#ifndef ONLINE_JUDGE
	freopen("12278.in","r",stdin);
#endif
	for (;3 == scanf("%d %d %d",&i,&j,&k) && (i+j+k);) {
		p[0] = cell(i,j,k);
		for ( l = 1; l < 3; ++l )
			scanf("%d %d %d",&i,&j,&k), p[l] = cell(i,j,k);
		scanf("%Lf %Lf %LF",t.x,t.x+1,t.x+2);
		if ( ZERO == ((p[2]-p[0])*(p[1]-p[0])) ) {
			if ( t==p[0]&&fabs(((t-p[1])^(t-p[2]))-pi)<tol || t==p[2]&&fabs(((t-p[0])^(t-p[1]))-pi)<tol || t==p[1]&&fabs(((t-p[2])^(t-p[0]))-pi)<tol ) {
				puts("YES");
				continue ;
			}
			if ( t == p[0] || t == p[1] || t == p[2] ) {
				puts("NO");
				continue ;
			}
			for ( ok = false, i = 0; i < 3 && !ok; ++i )
				for ( j = i+1; j < 3 && !ok; ++j ) {
					//printf("%.2Lf\n",((t-p[i])^(t-p[j]))*180/pi);
					if ( fabs(((t-p[i])^(t-p[j]))-pi) < tol )
						ok = true ;
				}
			puts(ok?"YES":"NO");
			continue ;
		}
		if ( p[0] == p[1] && p[1] == p[2] ) {
			puts(p[0]==t?"YES":"NO");
			continue ;
		}
		if ( p[0] == p[1] ) {
			puts(fabs(((t-p[0])^(t-p[2]))-pi)<tol?"YES":"NO");
			continue ;
		}
		// printf("%Lf %Lf %Lf vs %Lf %Lf %Lf\n",p[1][0],p[1][1],p[1][2],p[2][0],p[2][1],p[2][2]);
		if ( p[1] == p[2] ) {
			puts(fabs(((t-p[0])^(t-p[1]))-pi)<tol?"YES":"NO");
			continue ;
		}
		if ( p[2] == p[0] ) {
			puts(fabs(((t-p[0])^(t-p[1]))-pi)<tol?"YES":"NO");
			continue ;
		}
		n = (p[1]-p[0])*(p[2]-p[0]), u = 0;
		if ( fabs((n,(t-p[0]))) >= tol ) {
			puts("NO");
			continue ;
		}
		for ( ok = true, i = 0; i < 3 && ok && !(u&(u-1)); ++i ) {
			j = ((i+1)%3), m = (p[i]-t)*(p[j]-t);
			if ( ok &= !(m == ZERO) ) {
				k = signum((m,n));
				u |= (1<<(k==0?0:(k==-1?2:1)));
			}
		}
		puts(ok&&!(u&(u-1))?"YES":"NO");
	}
	return 0;
}

