/*
 * 11004. Changing Roadmap
 * TOPIC: dp, combinatorics, prefix sums, geometry
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int M = 0x80, N = 3001;
	final double tol = 1e-9;
	int m,n;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Line {
		long a,b,c;
		Line( long a, long b, long c ) { this.a = a; this.b = b; this.c = c; }
	}
	class Foo implements Comparable<Foo> {
		double x,y;
		Foo( double x, double y ) { this.x = x; this.y = y; }
		public int compareTo( Foo other ) {
			if ( Math.abs(this.x-other.x) < tol ) {
				if ( Math.abs(this.y-other.y) < tol )
					return 0;
				return this.y<other.y?-1:1;
			}
			return this.x<other.x?-1:1;
		}
	}
	Line []c;
	Foo []p;
	Foo intersect( Line p, Line q ) {
		double det = p.a*q.b-p.b*q.a, dx = -p.c*q.b+q.c*p.b, dy = -q.c*p.a+p.c*q.a;
		return new Foo(dx/det,dy/det);
	}
	Set<Foo> s;
	int [][]sg = new int[N][0x80];
	int signum( double x ) {
		if ( Math.abs(x) < tol )
			return 0;
		return x<0?-1:1;
	}
	int [][][]pref = new int[2][M][N];
	void go() throws Exception {
		int i,j,k,l,t,cs = 0,ans = 0;
		Iterator<Foo> it;
		long spos,sneg,pos,neg;
		for (;(n=scan.nextInt())!=0;) {
			c = new Line[n];
			for( i = 0; i < n; ++i ) {
				k = scan.nextInt();
				l = scan.nextInt();
				t = scan.nextInt();
				c[i] = new Line(k,l,t);
			}
			m = scan.nextInt();
			p = new Foo[m];
			for ( i = 0; i < m; ++i ) {
				k = scan.nextInt();
				l = scan.nextInt();
				p[i] = new Foo(k,l);
			}
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < m; ++j )
					sg[i][j] = signum(c[i].a*p[j].x + c[i].b*p[j].y + c[i].c);
			for ( t = 0; t <= 1; ++t )
				for ( j = 0; j < m; ++j )
					for ( i = 0; i <= n; ++i )
						pref[t][j][i] = 0;
			for ( j = 0; j < m; ++j )
				for ( i = 1; i <= n; ++i ) {
					pref[0][j][i] = pref[0][j][i-1];
					pref[1][j][i] = pref[1][j][i-1];
					if ( sg[i-1][j] < 0 )
						++pref[0][j][i];
					else if ( sg[i-1][j] > 0 )
						++pref[1][j][i];
				}
			for ( sneg = 0, j = 0; j < m; ++j )
				for ( i = 1; i <= n; ++i )
					if ( sg[i-1][j] < 0 ) {
						sneg += pref[0][j][i-1];
					}
					else if ( sg[i-1][j] > 0 ) {
						sneg += pref[1][j][i-1];
					}
			System.out.print("Roadmap "+(++cs)+":\nNegative Builders Ltd. will build ");
			System.out.println(sneg+" New Roads.");
		}
	}
};

