/*
 * 1393. Highways
 * TOPIC: dp, combinatorics, number theory, grids, counting
 * status:
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;
import java.util.Map;

class Main {
	final int N = 0x200;
	final double tol = 1e-13;
	int m,n;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Cell implements Comparable<Cell> {
		int i,j;
		double angle,dist;
		Cell() {};
		Cell( int x, int y ) {
			this.i = x; this.j = y;
			this.dist = Math.sqrt(x*x+y*y);
			this.angle = Math.atan(((double)y)/x);
		};
		public int compareTo( Cell other ) {
			if ( Math.abs(this.angle-other.angle) < tol ) {
				if ( Math.abs(this.dist-other.dist) < tol )
					return 0;
				return this.dist>other.dist?-1:1;
			}
			return this.angle<other.angle?-1:1;
		}
	};
	void go() throws Exception {
		int i,j,k,ans;
		for ( ;; System.out.println(ans<<1) ) {
			m = scan.nextInt(); n = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			Map<Double,Cell> q = new TreeMap<Double,Cell>();
			for ( ans = 0, i = 1; i < m; ++i )
				for ( j = 1; j < n; ++j ) {
					Cell c = new Cell(i,j);
					if ( !q.containsKey(c.angle) || c.compareTo(q.get(c.angle)) < 0 ) {
						q.remove(c.angle);
						q.put(c.angle,c);
					}
				}
			for ( Map.Entry<Double,Cell> e: q.entrySet() ) {
				ans += (m-e.getValue().i)*(n-e.getValue().j);
				System.out.println(e.getKey()*180/Math.PI+" "+e.getValue().i+" "+e.getValue().j);
			}
		}
	}
};

