/*
 * 1388. Graveyard
 * TOPIC: geometry, roots of unity, trigonometric circle, trigonometry
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;

class Main {

	Scanner scan = new Scanner(System.in);

	double tol = 1e-9;

	public static void main( String [] args ) throws Exception { new Main().go(); }

	double f( double x, double y ) {
		double a = x-y, b = y-x;
		if ( a < 0 ) a += 2*Math.PI;
		if ( b < 0 ) b += 2*Math.PI;
		return Math.min(a,b);
	}

		class Ponto implements Comparable<Ponto> {
			double ang;
			int idx;
			Ponto( double a, int idx ) { this.ang = a; this.idx = idx; }
			public int compareTo( Ponto other ) {
				if ( Math.abs(this.ang-other.ang) < tol )
					return 0;
				if ( this.ang < other.ang ) return -1;
				return 1;
			}
		}

	void go() throws Exception {
		int m,n,i,j,k;
		Ponto []c;
		double ans,x,y,z;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			m = scan.nextInt();
			m += n;
			c = new Ponto[n+m];
			for ( i = 0; i < n; ++i )
				c[i] = new Ponto((2*Math.PI*i)/n,i);
			for ( i = n; i < n+m; ++i )
				c[i] = new Ponto((2*Math.PI*(i-n))/m,i);
			Arrays.sort(c);
			ans = 0;
			j = -1;
			for ( i = 0; i < n+m; ++i ) {
				if ( c[i].idx >= n ) {
					j = i;
					continue ;
				}
				for ( k = i+1; k < n+m && c[k].idx < n; ++k );
				if ( k == n+m )
					ans += f(c[i].ang,c[j].ang);
				else if ( j != -1 )
					ans += Math.min(f(c[i].ang,c[j].ang),f(c[i].ang,c[k].ang));
				else 
					ans += f(c[i].ang,c[k].ang);
			}
			System.out.printf("%.4f\n",(5000/Math.PI)*ans+tol);
		}
	}
};

