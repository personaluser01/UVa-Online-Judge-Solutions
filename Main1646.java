/*
 * 1646. Edge Case
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	int n;
	final int N = (1<<15);
	Scanner scan = new Scanner(System.in);
	BigInteger []z = new BigInteger[N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	BigInteger calc_z( int n ) {
		if ( z[n] != null )
			return z[n];
		if ( n <= 1 )
			return z[n] = BigInteger.ONE;
		/*
		z[n] = BigInteger.ONE;
		for ( int i = 0; i <= n-2; ++i )
			z[n] = z[n].add(calc_z(n-2-i));
		return z[n];*/
		z[n] = calc_z(n-1).add(calc_z(n-2));
		return z[n];
	}
	void go() throws Exception {
		for ( n = 0; n < N; z[n++] = null );
		for (;scan.hasNext() && (n=scan.nextInt())>0;) 
			System.out.println((calc_z(n).add(calc_z(n-2))).toString());
	}
};

