/*
 * 1246. Find Terrorists
 * TOPIC: primes, sieve
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = (1<<16);
	Scanner scan = new Scanner(System.in);
	boolean []isprime = new boolean[N];
	int []p = new int[N],z = new int[N],pref = new int[N];
	int n,m;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int ts = scan.nextInt(),ax,a,b,i,j,k;
		for ( isprime[2]=true, i = 3; i < N; i += 2 )
			isprime[i] = true;
		for ( i = 3; i < N; i += 2 )
			if ( isprime[i] )
				for ( j = i+i; j < N; isprime[j] = false, j += i );
		for ( m = 0, i = 2; i < N; ++i )
			if (isprime[i])
				p[m++] = i;
		for ( i = 0; i < N; ++i ) z[i] = 1;
		for ( z[1] = 1, i = 2; i < N; ++i )
			if ( isprime[i] )
				for ( z[i] = 2, j = i+i; j < N; z[j] *= (ax+1), j += i )
					for ( ax = 0, k = j; 0 == (k%i); k /= i, ++ax );
		for ( i = 2; i < N; ++i )
			if ( isprime[z[i]] )
				pref[i] = pref[i-1]+1;
			else pref[i] = pref[i-1];
		while ( ts-- > 0 ) {
			a = scan.nextInt();
			b = scan.nextInt();
			if ( (k=pref[b]-pref[a-1]) == 0 ) {
				System.out.println("-1");
				continue ;
			}
			for ( i = a; i <= b; ++i )
				if ( isprime[z[i]] ) {
					if ( --k >= 1 )
						System.out.print(i+" ");
					else System.out.println(i);
				}
		}
	}
};

