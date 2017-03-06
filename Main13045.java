/*
 * 13045. Drawing Polygon
 * TOPIC: vectors, rotation
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int DIM = 3, N = 0x400;
	int n;
	double L;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	class Point {
		double []x;
		Point() { x = new double[DIM]; };
		Point( double a, double b, double c ) {
			x = new double[DIM];
			x[0] = a; x[1] = b; x[2] = c;
		};
		Point( double a, double b ) {
			x = new double[DIM];
			x[0] = a; x[1] = b; x[2] = 0;
		};
		Point rot( double t ) {
			double co = Math.cos(t), si = Math.sin(t);
			return new Point(this.x[0]*co-this.x[1]*si,this.x[0]*si+this.x[1]*co);
		};
		Point add( Point other ) {
			return new Point(this.x[0]+other.x[0],this.x[1]+other.x[1],this.x[2]+other.x[2]);
		}
		Point sub( Point other ) {
			return new Point(this.x[0]-other.x[0],this.x[1]-other.x[1],this.x[2]-other.x[2]);
		}
	};
	Point []p;
	void go() throws Exception {
		int ts,cs = 0,i,j,k;
		double phi;
		for ( ts=scan.nextInt(); ts-->0; ) {
			n = scan.nextInt(); phi = (Math.PI*(n-2))/n;
			p = new Point[n];
			L = scan.nextDouble();
			double xx = scan.nextDouble(), yy = scan.nextDouble();
			p[0] = new Point(xx,yy);
			p[1] = new Point(xx+L,yy);
			for ( i = 2; i < n; ++i ) 
				p[i] = p[i-1].sub(p[i-2]).rot(Math.PI-phi).add(p[i-1]);
			System.out.println("Case #"+(++cs)+":");
			for ( i = 0; i < n; ++i ) {
				System.out.printf("%f %f\n",p[i].x[0],p[i].x[1]);
			}
			if ( ts > 0 ) System.out.println("");
		};
	};
};

