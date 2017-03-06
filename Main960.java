/*
 * 960. Gaussian Primes
 * TOPIC: number theory
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<21);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	int n;
	long []p;
	boolean []isprime = new boolean[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean isPrime( long x ) {
		if ( x < N ) return isprime[(int)x];
		for ( int i = 0; p[i]*p[i] <= x; ++i )
			if ( 0 == (x%p[i]) )
				return false;
		return true;
	}
	void go() throws Exception {
		int i,j,k,cs,ts = Integer.parseInt(br.readLine());
		long a,b;
		for ( i = 3; i < N; i += 2 )
			isprime[i] = true;
		for ( isprime[2] = true, i = 3; i < N; i += 2 )
			for ( j = i+i; j < N && isprime[i]; isprime[j] = false, j += i );
		for ( k = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) ++k;
		p = new long[k+1];
		for ( n = 0, i = 0; i < N; ++i )
			if ( isprime[i] )
				p[n++] = i;
		for(;ts-->0;) {
			st = new StringTokenizer(br.readLine());
			a = Long.parseLong(st.nextToken());
			b = Long.parseLong(st.nextToken());
			if ( a != 0 && b != 0 ) {
				if ( isPrime(a*a+b*b) ) {
					System.out.println("P");
					continue ;
				}
				System.out.println("C");
				continue ;
			}
			if ( a == 0 ) {
				if ( isPrime(Math.abs(b)) && (Math.abs(b)&3) == 3 ) {
					System.out.println("P");
					continue ;
				}
				System.out.println("C");
				continue ;
			}
			if ( b == 0 ) {
				if ( isPrime(Math.abs(a)) && (Math.abs(a)&3) == 3 ) {
					System.out.println("P");
					continue ;
				}
				System.out.println("C");
				continue ;
			}
		}
	}
};

