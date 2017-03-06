/*
 * 10386. Circles in Triangles
 * TOPIC: binary search, maths, coordinates, neat
 * status: Accepted
 * HC59.72.P6 .E17, HC59.7 .E22 2006, HD87 .E237 2013
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	double r;
	final double tol = 1e-10, t = Math.sqrt(3);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	double S( double x ) { return x*x; }
	class Foo {
		double x,y;
		Foo( double x, double y ) { this.x = x; this.y = y; }
		double distTo( Foo other ) {
			return Math.sqrt(S(this.x-other.x)+S(this.y-other.y));
		}
		double area( Foo a, Foo b ) {
			double ux = a.x-this.x, uy = a.y-this.y;
			double vx = b.x-this.x, vy = b.y-this.y;
			return Math.abs(ux*vy-uy*vx)/2;
		}
	}
	void go() throws Exception {
		int i,j,k,l;
		double low,high,mid;
		for ( int ts = scan.nextInt(); ts-- > 0; ) {
			r = scan.nextDouble();
			for ( low = 0, high = (1<<29); Math.abs(high-low) >= tol; ) {
				mid = (low+high)/2;
				Foo A = new Foo(0,t*mid/2-r), B = new Foo(r,2*r+t*r), C = new Foo(mid/2-t*r,t*mid/2-r);
				double a = B.distTo(C), b = A.distTo(C), c = A.distTo(B);
				if ( a*b*c/4/A.area(B,C) < 2*r ) 
					low = mid;
				else high = mid;
			}
			System.out.printf("%.10f ",high);
			for ( low = 0, high = (1<<29); Math.abs(high-low) >= tol; ) {
				mid = (low+high)/2;
				Foo A = new Foo(0,t*mid/2-r), B = new Foo(2*r,2*r+2*t*r), C = new Foo(mid/2-t*r,t*mid/2-r);
				double a = B.distTo(C), b = A.distTo(C), c = A.distTo(B);
				if ( a*b*c/4/A.area(B,C) < 2*r ) 
					low = mid;
				else high = mid;
			}
			System.out.printf("%.10f\n",high);
		}
	}
};

