/*
 * 1110. Pyramids
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<20), oo = (1<<29), M = 0x200, MAXK = 330, OO = 126;
	final double tol = 1e-12;
	Scanner scan = new Scanner(System.in);
	int F( int m ) { return (m*(2*m+1)*(m+1))/6; }
	List<Pyramid> L = new LinkedList<Pyramid>();
	Pyramid []p;
	int K,n;
	char[][]z = new char[MAXK][N];
	class Pyramid implements Comparable<Pyramid> {
		int m,weight;
		boolean is_high;
		Pyramid() {this.m=0; this.is_high=false;};
		Pyramid( int m, boolean f ) { this.m = m; this.is_high = f; this.weight = weight(); };
		public int weight() {
			if ( is_high )
				return weight = F(m);
			else {
				if ( (m&1) == 1 ) 
					return weight = F(m)-(F((m-1)>>1)<<2);
				else 
					return weight = F(m>>1)<<2;
			}
		};
		public int compareTo( Pyramid other ) {
			if ( weight== other.weight ) {
				if ( is_high == other.is_high ) return 0;
				if ( is_high && !other.is_high )
					return 1;
				if ( !is_high && other.is_high ) return -1;
				return 0;
			}
			return weight<other.weight?-1:1;
		};
		public String toString() {
			StringBuilder sb = new StringBuilder();
			sb.append(m+(is_high?"H":"L"));
			return sb.toString();
		}
	};
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	int f( int k, int n ) {
		if ( p[k-1].weight() <= n ) 
			return k;
		if ( p[0].weight() > n ) 
			return -1;
		int low = 0, high = k-1, mid;
		for (;low+1<high;)
			if ( p[mid=(low+high)/2].weight<=n )
				 low=mid;
			else high=mid;
		assert( p[low].weight <= n && p[high].weight > n );
		return high;
	}
	void go() throws Exception {
		int cs=0, i,j,k;
		L.add(new Pyramid(2,true));
		for ( n = 3; n < M; ++n ) {
			Pyramid t = new Pyramid(n,true);
			if ( t.weight() < N ) L.add(t);
			t = new Pyramid(n,false);
			if ( t.weight() < N ) L.add(t);
		}
		for ( p = new Pyramid[L.size()], i = 0; i < L.size(); p[i] = L.get(i), ++i );
		Arrays.sort(p); K = p.length;
		for ( k = 0; k <= K; ++k )
			for ( n = 0; n < N; ++n )
				z[k][n] = +OO;
		for ( z[0][0] = 0, k = 1; k <= K; ++k )
			for ( n = 0; n < N; ++n ) {
				z[k][n] = z[k-1][n];
				if ( p[k-1].weight <= n && z[k-1][n-p[k-1].weight] < +OO )
					if ( z[k-1][n-p[k-1].weight]+1 < z[k][n] )
						z[k][n] = (char)(z[k-1][n-p[k-1].weight]+1);
			}

		for (;(n=scan.nextInt())!=0;) {
			System.out.print("Case "+(++cs)+":");
			if ( z[K][n] == +OO ) 
				System.out.println(" impossible");
			// else System.out.println(dump(K,n,new StringBuilder()).toString());
			else {
				StringBuilder sb = new StringBuilder();
				for ( k = K; k >= 1; --k ) {
					if ( n >= p[k-1].weight && z[k-1][n-p[k-1].weight] == z[k][n]-1 ) {
						sb.append(" "+p[k-1].toString());
						n -= p[k-1].weight;
					}
				}
				System.out.println(sb.toString());
			}
		}
	}
};

