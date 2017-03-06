/*
 * 11908. Skyscraper
 * TOPIC: DP, binary search, sorting, segments
 * status: status
 */
import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	int N = (1<<15);
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Seg implements Comparable<Seg> {
		int a,b,c;
		Seg( int A, int B, int C ) { a = A; b = B; c = C; }
		public int compareTo( Seg other ) {
			if ( this.b < other.b )
				return -1;
			if ( this.b > other.b )
				return 1;
			if ( this.a < other.a )
				return -1;
			if ( this.a > other.a )
				return 1;
			if ( this.c < other.c )
				return 1;
			if ( this.c > other.c )
				return -1;
			return 0;
		}
	}
	void go() throws Exception {
		int ts,cs = 0,i,j,k,l,n,low,high,mid;
		long []z;
		ts = scan.nextInt();
		Seg []d;
		while ( ts-- > 0 ) {
			n = scan.nextInt();
			d = new Seg[n+1];
			d[0] = new Seg(-13,-1,0);
			for ( i = 1; i <= n; ++i ) {
				j = scan.nextInt();
				k = scan.nextInt();
				l = scan.nextInt();
				d[i] = new Seg(j,j+k-1,l);
			}
			Arrays.sort(d);
			z = new long[n+1];
			z[0] = 0;
			for ( i = 1; i <= n; ++i ) {
				if ( d[i-1].b < d[i].a ) {
					z[i] = z[i-1]+d[i].c;
					continue ;
				}
				low = 0; high = i-1;
				assert( d[low].b < d[i].a );
				assert( d[high].b >= d[i].a );
				while ( low+1 < high ) {
					mid = (low+high)/2;
					if ( d[mid].b < d[i].a )
						low = mid;
					else high = mid;
				}
				z[i] = Math.max(z[i-1],z[low]+d[i].c);
			}
			System.out.printf("Case %d: ",++cs);
			System.out.println(z[n]);
		}
	}
};

