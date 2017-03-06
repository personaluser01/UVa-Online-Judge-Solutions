/*
 * 10483. The Sum Equals the Product
 * TOPIC: ad hoc, maths, brute force
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final double tol = 1e-11;
	final long L = 10000;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Foo implements Comparable<Foo> {
		long X,Y,Z;
		Foo( long x, long y, long z ) {
			this.X = Math.min(x,Math.min(y,z));
			this.Z = Math.max(x,Math.max(y,z));
			this.Y = x+y+z-(this.X+this.Z);
		}
		public int compareTo( Foo other ) {
			if ( this.X == other.X ) {
				if ( this.Y == other.Y ) {
					if ( this.Z == other.Z )
						return 0;
					return this.Z<other.Z?-1:1;
				}
				return this.Y<other.Y?-1:1;
			}
			return this.X<other.X?-1:1;
		}
	}
	class cmp01 implements Comparator<Foo> {
		public int compare( Foo a, Foo b ) {
			long x = a.X+a.Y+a.Z, y = b.X+b.Y+b.Z;
			if ( x == y ) {
				return a.compareTo(b);
			}
			return x<y?-1:1;
		}
	}
	void go() throws Exception {
		long low,high,x,y,z,up,down;
		Foo t;
		while ( scan.hasNext() ) {
			low = (long)(100*(scan.nextDouble()));
			high = (long)(100*(scan.nextDouble()));
			Set<Foo> q = new TreeSet<Foo>();
			for ( x = 1; x*x*x <= 256000000; ++x ) {
				// for ( y = Math.max(x,(long)Math.floor((L+.0)/x+tol)); x*y <= L; ++y );
				for ( y = x; y*x <= L; ++y );
				assert x*y > L;
				assert y >= x;
				for ( ;y <= 256000000/(x*y); ++y ) {
					up = L*(x+y);
					down = (x*y-L);
					if ( (up%down) != 0 ) continue ;
					z = up/down;
					long s = (x+y+z);
					if ( low <= s && s <= high ) {
						q.add(t = new Foo(x,y,z));
						assert Math.abs((x+y+z)/100.0-(x*y*z)/1000000.00) < tol;
					}
				}
			}
			// Foo []c = (Foo [])q.toArray();
			Set<Foo> e = new TreeSet<Foo>(new cmp01());
			for ( Iterator<Foo> it = q.iterator(); it.hasNext(); e.add(it.next()) );
			for ( Iterator<Foo> it = e.iterator(); it.hasNext(); ) {
				Foo tmp = it.next();
				System.out.printf("%.02f = %.02f + %.02f + %.02f = %.02f * %.02f * %.02f\n",(tmp.X+tmp.Y+tmp.Z)/100.00+tol,tmp.X/100.00+tol,tmp.Y/100.00+tol,tmp.Z/100.00+tol,tmp.X/100.00+tol,tmp.Y/100.00+tol,tmp.Z/100.00+tol);
			}
			break ;
		}
	}
};

