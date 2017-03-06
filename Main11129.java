/*
 * 11129. An Antiarithmetic Permutation
 * TOPIC: recursion, elegant, divide and conquer
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Seq {
		public int n;
		public int []c;
		Seq( int n, int []c ) {
			this.n = n;
			this.c = new int[n];
			for ( int i = 0; i < n; ++i )
				this.c[i] = c[i];
		}
		Seq( int n ) {
			this.n = n;
			this.c = new int[n];
		}
		Seq concat( Seq other ) {
			Seq res = new Seq(this.n+other.n);
			int k = 0;
			for ( int i = 0; i < this.n; res.c[k++] = this.c[i++] );
			for ( int i = 0; i < other.n; res.c[k++] = other.c[i++] );
			return res;
		}
		Seq extractR( int r ) {
			int i,j,k = 0;
			for ( i = 0; i < this.n; ++i )
				if ( r == (this.c[i]&1) )
					++k;
			Seq res = new Seq(k);
			k = 0;
			for ( i = 0; i < this.n; ++i )
				if ( r == (this.c[i]&1) )
					res.c[k++] = (this.c[i]-r)>>1;
			return res;
		}
	}
	Seq solve( Seq s ) {
		if ( s.n <= 2 ) return s;
		Seq e = s.extractR(0), o = s.extractR(1);
		Seq E = solve(e), O = solve(o);
		Seq r = new Seq(s.n);
		int i,k = 0;
		for ( i = 0; i < E.n; r.c[k++] = (E.c[i++]<<1) );
		for ( i = 0; i < O.n; r.c[k++] = (O.c[i++]<<1)+1 );
		return r;
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int n;
		while ( (n = scan.nextInt()) != 0 ) {
			Seq s = new Seq(n);
			for ( int i = 0; i < n; ++i )
				s.c[i] = i;
			Seq r = solve(s);
			System.out.print(n+":");
			for ( int i = 0; i < r.n; ++i )
				System.out.print(" "+r.c[i]);
			System.out.println("");
		}
	}
};

