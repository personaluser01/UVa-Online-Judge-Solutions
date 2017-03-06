/*
 * 13067. Prime Kebab Menu
 * TOPIC: sieve, number theory, trivial, maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	long n;
	long []p;
	int m;
	final int N = 10000008;
	boolean []isprime = new boolean[N];
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		int i,j,k;
		long x;
		for ( isprime[2] = true, i = 3; i < N; isprime[i] = true, i += 2 );
		for ( i = 3; i < N; i += 2 )
			if ( isprime[i] )
				for ( j = i+i; j < N; isprime[j] = false, j += i );
		for ( m = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) ++m;
		p = new long [m];
		for ( k = 0, i = 0; i < N; ++i )
			if ( isprime[i] )
				p[k++] = i;
		for(;scan.hasNext();) {
			n = scan.nextLong();
			if ( n == 1L ) break ;
			for ( k = 0, x = n, i = 0; i < m; ++i )
				for ( ;0 == (x%p[i]); x /= p[i], ++k );
			if ( x > 1 ) ++k;
			System.out.println(k);
		}
	};
};

