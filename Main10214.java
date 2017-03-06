/*
 * 10214. Trees in a Wood
 * TOPIC: euler phi, sieve, gcd, inclusion-exclusion
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x400*2;
	Scanner scan = new Scanner(System.in);
	long n,a,b,K;
	boolean []isPrime = new boolean[N];
	long []phi = new long[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	long gcd( long x, long y ) { return y==0?x:gcd(y,x%y); }
	void go() throws Exception {
		int i,j,k;
		long x,y,l;
		for ( isPrime[2] = true, i = 3; i < N; isPrime[i] = true, i += 2 );
		for ( i = 0; i < N; phi[i] = i, ++i );
		for ( i = 2; i < N; ++i )
			if ( isPrime[i] ) for ( j = i+i, phi[i] = i-1; j < N; isPrime[j] = false, phi[j] /= i, phi[j] *= (i-1), j += i );
		for ( ;; ) {
			a = scan.nextLong(); b = scan.nextLong();
			if ( a == 0 && b == 0 ) break ;
			n = (2*a+1)*(2*b+1)-1;
			if ( a > b ) { long s = a; a = b; b = s; }
			assert a <= b;
			for ( K = 0, x = 1; x <= a; ++x ) {
				K += (b/x)*phi[(int)x];
				for ( l = b%x, i = 1; i <= l; ++i )
					if ( gcd(x,i) == 1 ) ++K;
			}
			System.out.printf("%.7f\n",4*(K+1.00)/n);
		}
	}
};

