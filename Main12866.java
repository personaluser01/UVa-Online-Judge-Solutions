/*
 * 12866. Combination
 * TOPIC: combinatorics, lucas theorem, number bases, modulo, nontrivial
 * status: In progress
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 62;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	BigInteger f( int []d, int n ) {
		if ( n==1 ) 
			return new BigInteger("3").pow(d[n-1]);
		assert n>=2 ;
		BigInteger r=f(d,n-1);
		assert d[n-1]==0 || d[n-1]==1;
		if ( d[n-1]==1 )
			r=r.add(new BigInteger("3").pow(n-1));
		return r;
	}
	BigInteger F( long x ) {
		if ( x < 0 ) return BigInteger.ZERO;
		if ( x == 0 ) 
			return BigInteger.ONE;
		assert x >= 1;
		int []d = new int[N];
		int k;
		long y = x;
		for ( k = 0; y > 0; d[k++] = (int)(y&1), y >>= 1 );
		/*
		System.out.println("n = "+x);
		for ( int i = 0; i < k; ++i )
			System.out.print(d[i]+" ");
		System.out.println("");
		*/
		return f(d,k);
	}
	void go() throws Exception {
		long low,high;
		for (;;) {
			low = scan.nextLong(); high = scan.nextLong();
			if ( low == 0 && high == 0 ) break ;
			BigInteger flow = F(low-1), fhigh = F(high);
			System.out.println((fhigh.subtract(flow)).toString());
			// System.out.println(fhigh);
		}
	}
};

