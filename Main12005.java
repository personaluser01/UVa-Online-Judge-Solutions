/*
 * 12005. Find Solutions
 * TOPIC: maths, number theory, primes
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 2*10000008;
	Scanner scan = new Scanner(System.in);
	boolean []isprime = new boolean[N];
	long []p;
	int n,m;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		long a,b,c,ans;
		int i,j,k;
		for ( i = 3; i < N; i += 2 )
			isprime[i] = true;
		for ( isprime[2] = true, i = 3; i < N; i += 2 )
			for ( j = i+i; j < N && isprime[i]; j += i )
				isprime[j] = false;
		for ( m = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) ++m;
		p = new long[m+1];
		for ( k = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) p[k++] = i;
		for ( ;(c=scan.nextLong()) != 0; ) {
			for ( a = c, c = 4*c-3, ans = 1, i = 0; i < m && p[i]*p[i] <= c; ++i, ans *= k ) 
				for ( k = 1; 0 == (c%p[i]); ++k, c /= p[i] );
			if ( c > 1 ) ans *= 2;
			System.out.println(a+" "+ans);
		}
	}
};

