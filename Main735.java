/*
 * 735. Dart-a-Mania
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	int N = 1000, M = 70, m = 0;
	BigInteger [][]z = new BigInteger[4][N];
	BigInteger [][][]c = new BigInteger[4][N][M];
	int []t;
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,n;
		Set<Integer> s = new HashSet<Integer>();
		for ( i = 1; i <= 3; ++i )
			for ( k = 0; k <= 20; ++k )
				s.add(i*k);
		s.add(50);
		t = new int[m = s.size()];
		Iterator it = s.iterator();
		for ( i = 0; it.hasNext(); t[i++] = (int)it.next() );
		assert i == m;
		Arrays.sort(t);
		for ( n = 1; n < N; z[0][n++] = BigInteger.ZERO );
		z[0][0] = BigInteger.ONE;
		for ( j = 1; j <= 3; ++j )
			for ( n = 0; n < N; ++n ) 
				for ( z[j][n] = BigInteger.valueOf(i = 0); i < m && t[i] <= n; ++i )
					z[j][n] = z[j][n].add(z[j-1][n-t[i]]);
		for ( j = 0; j <= 3; ++j )
			for ( n = 0; n < N; ++n )
				for ( i = 0; i < m; ++i )
					c[j][n][t[i]] = BigInteger.ZERO;
		for ( i = 0; i < m; ++i )
			c[1][t[i]][t[i]] = BigInteger.ONE;
		for ( j = 1; j <= 3; ++j )
			for ( n = 0; n < N; ++n )
				for ( i = 0; i < m; ++i ) {
					if ( t[i] > n ) continue ;
					for ( k = i; k < m; ++k )
						c[j][n][t[i]] = c[j][n][t[i]].add(c[j-1][n-t[i]][t[k]]);
				}
		Scanner scan = new Scanner(System.in);
		while ( (n = scan.nextInt()) > 0 ) {
			if ( z[3][n].equals(BigInteger.ZERO) ) {
				System.out.println("THE SCORE OF "+n+" CANNOT BE MADE WITH THREE DARTS.");
				System.out.println("**********************************************************************");
				continue ;
			}
			BigInteger res = new BigInteger("0");
			for ( i = 0; i < m; ++i )
				res = res.add(c[3][n][t[i]]);
			System.out.println("NUMBER OF COMBINATIONS THAT SCORES "+n+" IS "+res.toString()+".");
			System.out.println("NUMBER OF PERMUTATIONS THAT SCORES "+n+" IS "+z[3][n].toString()+".");
			System.out.println("**********************************************************************");
		}
		System.out.println("END OF OUTPUT");
	}
};

