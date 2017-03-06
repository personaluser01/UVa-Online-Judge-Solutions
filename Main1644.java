/*
 * 1644. Prime Gap
 * TOPIC: sieve, binary search
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = (1<<21);
	boolean []isprime = new boolean[N];
	int m,n;
	int []p;
	public static void main( String []args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k;
		for ( i = 3; i < N; isprime[i] = true, i += 2 );
		for ( isprime[2] = true, i = 3; i < N; i += 2 )
			for ( j = i+i; isprime[i] && j < N; isprime[j] = false, j += i );
		for ( m = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) ++m;
		p = new int[m+1];
		for ( k = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) p[k++] = i;
		while ( (n = scan.nextInt()) != 0 ) {
			if ( p[i=0] == n ) {
				System.out.println("0");
				continue ;
			}
			assert p[i] < n;
			assert p[m-1] >= n;
			for ( j = m-1; i+1<j; )
				if ( p[k=(i+j)/2]<n ) i=k; else j=k;
			assert i+1 == j;
			if ( p[j] == n ) { System.out.println("0");
					continue ;
			}
			System.out.println(p[j]-p[i]);
		}
	}
};

