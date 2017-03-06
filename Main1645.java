/*
 * 1645. Count
 * TOPIC: recursion
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int cs,n;
	final long MOD = 1000000000L+7L;
	final int N = 0x400;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long []z = new long[N];
	long f( int n ) {
		long s = 0;
		if ( n <= 2 ) return 1L;
		if ( z[n] != -1 ) return z[n];
		for ( int k = 1; k <= n-1; ++k )
			if ( 0 == ((n-1)%k) ) {
				s += f((n-1)/k);
				s %= MOD;
			}
		return z[n] = s;
	}
	void go() throws Exception {
		for ( int i = 0; i < N; ++i ) 
			z[i] = -1;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			System.out.println("Case "+(++cs)+": "+f(n));
		}
	}
};

