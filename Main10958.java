/*
 * 10958. How Many Solution
 * TOPIC: number theory
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<22);
	Scanner scan = new Scanner(System.in);
	long m,n,p,cs = 0,M;
	long []pr = new long[N/2];
	boolean []isprime = new boolean[N/2];
	void sieve() {
		long x,y;
		for ( x = 3; x < N/2; x += 2 ) isprime[(int)x] = true;
		isprime[2] = true; M = 0;
		for ( x = 3; x < N/2; x += 2 )
			if ( isprime[(int)x] )
				for ( y = x+x; y < N/2; y += x )
					isprime[(int)y] = false;
		for ( y = 0; y < N/2; ++y )
			if ( isprime[(int)y] )
				pr[(int)M++] = y;
	}
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	long []a = new long[N/2];
	int len;
	void factorize( long n ) {
		len = 0;
		n = Math.abs(n);
		for ( int i = 0; i < M && pr[i]*pr[i] <= n; ++i )
			if ( 0 == (n%pr[i]) ) {
				for ( a[len] = 0; 0 == (n%pr[i]); n /= pr[i], ++a[len] );
				++len;
			}
		if ( Math.abs(n) > 1 ) a[len++] = 1;
	}
	void go() throws Exception {
		long i,ax;
		for ( sieve(); scan.hasNext(); ) {
			m = scan.nextLong();
			n = scan.nextLong();
			p = scan.nextLong();
			if ( m == 0 && n == 0 && p == 0 )
				break ;
			System.out.print("Case "+(++cs)+": ");
			factorize(m*n*p*p);
			ax = 1L;
			for ( i = 0; i < len; ++i )
				ax *= (a[(int)i]+1L);
			System.out.println(2*ax-1);
		}
	}
};

