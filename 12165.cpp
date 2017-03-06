/*
 * 12165. Triangle Hazard
 * TOPIC: barycentric coordinates, triangles, geometry, swerc, system of linear eq
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
	
double sa,sb,sc;

class Main {
	double m[8];
	class Cell {
			public:
		double x,y,z;
		Cell( double X, double Y, double Z ) {
			double t = X+Y+Z;
			this->x = X/t; this->y = Y/t; this->z = Z/t;
		};
		Cell() { x = 1; y = 0; z = 0; };
		double distTo( const Cell &other ) {
			Cell c = this->sub(other);
			return -sa*c.y*c.z-sb*c.z*c.x-sc*c.x*c.y;
		};
		Cell sub( const Cell &other ) {
			Cell c;
			c.x = this->x-other.x;
			c.y = this->y-other.y;
			c.z = this->z-other.z;
			return c;
		}
	};
	class Point2D {
			public:
				   	double x[2];
		Point2D( double a, double b ) {
			x[0] = a; x[1] = b;
		};
		Point2D() { x[0]=x[1]=0; };
		Point2D sub( const Point2D &other ) { return Point2D(x[0]-other.x[0],x[1]-other.x[1]); };
		Point2D add( const Point2D &other ) { return Point2D(x[0]+other.x[0],x[1]+other.x[1]);	};
		Point2D mult( double t ) { return Point2D(x[0]*t,x[1]*t); };
		Point2D div( double t ) { return Point2D(x[0]/t,x[1]/t); };
		double getLen() { return (x[0]*x[0]+x[1]*x[1]); };
	};
		public:
	void go() {
		int i,j,k,ts;
		scanf("%d",&ts);
		Cell A,B,C,P,Q,R,D,E,F;
		double BP,_PQ,QE,CQ,_QR,RF,AR,_RP,PD;
		double a[3][3],b[3],xx[3],yy[3];
		Point2D p,q,r,n;
		for (;ts-->0;) {
			for ( i = 0; i < 3; ++i ) 
				scanf("%lf %lf",&xx[i],&yy[i]);
			p = Point2D(xx[0],yy[0]);
			q = Point2D(xx[1],yy[1]);
			r = Point2D(xx[2],yy[2]);
			for ( i = 1; i <= 6; scanf("%lf",&m[i++]) );
			P = Cell(m[1]*m[3],m[2]*m[4],m[1]*m[4]);
			Q = Cell(m[3]*m[6],m[3]*m[5],m[4]*m[6]);
			R = Cell(m[2]*m[6],m[2]*m[5],m[1]*m[5]);
			A = Cell(1,0,0);
			B = Cell(0,1,0);
			C = Cell(0,0,1);
			D = Cell(0,m[2],m[1]);
			E = Cell(m[3],0,m[4]);
			F = Cell(m[6],m[5],0);
			Point2D pq = q.sub(p), qr = r.sub(q), rp = p.sub(r);
			Cell PQ = Q.sub(P), QR = R.sub(Q), RP = P.sub(R);
			a[0][0] = -PQ.y*PQ.z; a[0][1] = -PQ.z*PQ.x; a[0][2] = -PQ.x*PQ.y;
			a[1][0] = -QR.y*QR.z; a[1][1] = -QR.z*QR.x; a[1][2] = -QR.x*QR.y;
			a[2][0] = -RP.y*RP.z; a[2][1] = -RP.z*RP.x; a[2][2] = -RP.x*RP.y;
			b[0] = pq.getLen(); b[1] = qr.getLen(); b[2] = rp.getLen();
			double det = a[0][0]*(a[1][1]*a[2][2]-a[1][2]*a[2][1])-a[0][1]*(a[1][0]*a[2][2]-a[2][0]*a[1][2])+a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);
			double da = b[0]*(a[1][1]*a[2][2]-a[1][2]*a[2][1])-b[1]*(a[0][1]*a[2][2]-a[2][1]*a[0][2])+b[2]*(a[0][1]*a[1][2]-a[1][1]*a[0][2]);
			sa = da/det;
			double db = -b[0]*(a[1][0]*a[2][2]-a[2][0]*a[1][2])+b[1]*(a[0][0]*a[2][2]-a[0][2]*a[2][0])-b[2]*(a[0][0]*a[1][2]-a[0][2]*a[1][0]);
			sb = db/det;
			double dc = b[0]*(a[1][0]*a[2][1]-a[1][1]*a[2][0])-b[1]*(a[0][0]*a[2][1]-a[0][1]*a[2][0])+b[2]*(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
			sc = dc/det;
			AR = (A.distTo(R)); n = r.sub(p); ;
			Point2D _a = r.add(n.mult(sqrt(AR/n.getLen())));
			BP = (B.distTo(P)); n = p.sub(q); ;
			Point2D _b = p.add(n.mult(sqrt(BP/n.getLen())));
			CQ = (C.distTo(Q)); n = q.sub(r); ;
			Point2D _c = q.add(n.mult(sqrt(CQ/n.getLen())));
			printf("%.8f %.8f %.8f %.8f %.8f %.8f\n",_a.x[0],_a.x[1],_b.x[0],_b.x[1],_c.x[0],_c.x[1]);
		}
	};
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("12165.in","r",stdin);
#endif
	Main *m = new Main();
	m->go();
	return 0;
}

