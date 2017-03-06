/*
 * 1210. Sum of Consecutive Primes
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	int m,N = (10001);
	boolean []is_prime = new boolean[N];
	long []z = new long[N];
	int []p;
	int []prefix = new int[N];
	int []cnt = new int[N];

	public static void main( String [] args ) throws Exception { new Main().go(); }

	void go() throws Exception {
		int i,j,k,l,t,n;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		is_prime[2] = true;
		for ( i = 3; i < N; i += 2 )
			is_prime[i] = true;
		for ( i = 3; i < N; i += 2 )
			if ( is_prime[i] )
				for ( j = i+i; j < N; j += i )
					is_prime[j] = false;
		p = new int[N];
		m = 0; p[++m] = 2;
		for ( i = 3; i < N; i += 2 )
			if ( is_prime[i] )
				p[++m] = i;
		for ( i = 1; i <= m; ++i )
			prefix[i] = prefix[i-1]+p[i];
		for ( k = 1; k <= m; ++k )
			for ( i = 1; (j = i+k-1) <= m; ++i ) {
				t = prefix[j]-prefix[i-1];
				if ( t >= N ) break ;
				++cnt[t];
			}
		while ( (s=br.readLine())!=null ) {
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			if ( n == 0 ) break ;
			System.out.println(cnt[n]);
		}
	}
};

