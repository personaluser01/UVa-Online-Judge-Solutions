/*
 * 12694. Meeting Room Arrangement
 * TOPIC: longest paths in dag, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 32, oo = (1<<29);
	int m,n;
	Scanner scan = new Scanner(System.in);
	boolean [][]g = new boolean[N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Foo implements Comparable<Foo> {
		int a,b;
		Foo( int x, int y ) { this.a = x; this.b = y; }
		public int compareTo( Foo other ) {
			if ( this.a == other.a ) {
				if ( this.b == other.b ) return 0;
				return this.b<other.b?-1:1;
			}
			return this.a<other.a?-1:1;
		}
		boolean precedes( Foo other ) { return this.b <= other.a; }
	}
	Foo []c = new Foo[N];
	int []z = new int[N];
	int calc_z( int x ) {
		int y;
		if ( z[x] < +oo )
			return z[x];
		for ( z[x] = 1, y = x+1; y < n; ++y )
			if ( g[x][y] )
				z[x] = Math.max(z[x],1+calc_z(y));
		return z[x];
	}
	void go() throws Exception {
		int i,j,k,w,ts = scan.nextInt();
		for (;ts-->0;) {
			for ( n = 0; ; ) {
				i = scan.nextInt();
				j = scan.nextInt();
				if ( i == 0 && j == 0 ) break ;
				c[n++] = new Foo(i,j);
			}
			for ( j = 1; j >= 1; )
				for ( j = 0, i = 0; i < n-1; ++i )
					if ( c[i].compareTo(c[i+1]) > 0 ) {
						Foo t = c[i];
						c[i] = c[i+1];
						c[i+1] = t; ++j;
					}
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					g[i][j] = false;
			for ( i = 0; i < n; z[i++] = +oo );
			for ( i = 0; i < n; ++i )
				for ( j = i+1; j < n; ++j )
					if ( c[i].precedes(c[j]) )
						g[i][j] = true;
			for ( w = 0, i = 0; i < n; ++i )
				w = Math.max(w,calc_z(i));
			System.out.println(w);
		}
	}
};

