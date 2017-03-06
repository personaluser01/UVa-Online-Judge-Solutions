/*
 * 12165. Triangle Hazard
 * TOPIC: barycentric coordinates, triangles, geometry, swerc
 * status: in progress
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	double []m = new double[8];
	final double tol = 1e-9;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	double sa,sb,sc;
	class Cell {
		double x,y,z;
		Cell( double x, double y, double z ) {
			double t = x+y+z;
			this.x = x/t; this.y = y/t; this.z = z/t;
		};
		Cell() { x = y = 0; z = 1; };
		double distTo( Cell other ) {
			Cell c = this.sub(other);
			return -sa*c.y*c.z-sb*c.z*c.x-sc*c.x*c.y;
		};
		Cell sub( Cell other ) {
			Cell c = new Cell();
			c.x = this.x-other.x;
			c.y = this.y-other.y;
			c.z = this.z-other.z;
			return c;
		}
	};
	class Point2D {
		double []x;
		Point2D( double a, double b ) {
			x = new double[2];
			x[0] = a; x[1] = b;
		};
		Point2D() { x = new double[2]; };
		Point2D sub( Point2D other ) { return new Point2D(x[0]-other.x[0],x[1]-other.x[1]); };
		Point2D add( Point2D other ) { return new Point2D(x[0]+other.x[0],x[1]+other.x[1]);	};
		Point2D mult( double t ) { return new Point2D(x[0]*t,x[1]*t); };
		Point2D div( double t ) { return new Point2D(x[0]/t,x[1]/t); };
		double getLen() { return (x[0]*x[0]+x[1]*x[1]); };
	};
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt();
		Cell A,B,C,P,Q,R,D,E,F;
		double BP,_PQ,QE,CQ,_QR,RF,AR,_RP,PD;
		double [][]a;
		double []b = new double[3];
		Point2D p,q,r,n;
		for (;ts-->0;) {
			double []xx = new double[3], yy = new double[3];
			for ( i = 0; i < 3; ++i ) {
				xx[i] = scan.nextDouble();
				yy[i] = scan.nextDouble();
			}
			p = new Point2D(xx[0],yy[0]);
			q = new Point2D(xx[1],yy[1]);
			r = new Point2D(xx[2],yy[2]);
			for ( i = 1; i <= 6; m[i++] = scan.nextDouble() );
			P = new Cell(m[2]*m[4],m[1]*m[3],m[2]*m[3]);
			Q = new Cell(m[4]*m[5],m[4]*m[6],m[3]*m[5]);
			R = new Cell(m[1]*m[5],m[1]*m[6],m[2]*m[6]);
			A = new Cell(1,0,0);
			B = new Cell(0,1,0);
			C = new Cell(0,0,1);
			D = new Cell(0,m[2],m[1]);
			E = new Cell(m[3],0,m[4]);
			F = new Cell(m[6],m[5],0);
			a = new double[3][3];
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
			System.out.println(Math.sqrt(sa));
			BP = Math.sqrt(B.distTo(P)); n = p.sub(q); n = n.div(Math.sqrt(n.getLen()));
			Point2D _b = p.add(n.mult(BP));
			System.out.println(_b.x[0]+" "+_b.x[1]);
		}
	};
};

