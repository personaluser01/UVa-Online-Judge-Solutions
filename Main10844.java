/*
 * 10844. Bloques
 * TOPIC: combinatorics, counting, recurrence, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x400;
	BigInteger [][]z = new BigInteger[N][N];
	BigInteger MINUS_ONE = new BigInteger("-1");
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	BigInteger calcZ( int n, int k ) {
		if ( !z[n][k].equals(MINUS_ONE) )
			return z[n][k];
		if ( k > n ) return z[n][k] = BigInteger.ZERO;
		if ( k == 1 ) return z[n][k] = BigInteger.ONE;
		z[n][k] = BigInteger.ZERO;
		z[n][k] = z[n][k].add(calcZ(n-1,k-1));
		z[n][k] = z[n][k].add(calcZ(n-1,k).multiply(BigInteger.valueOf(k)));
		return z[n][k];
	}
	void go() throws Exception {
		int i,j,k,l,t,n;
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				z[i][j] = MINUS_ONE;
		z[0][0] = BigInteger.ONE;
		for (;(n=scan.nextInt())!=0;) {
			BigInteger w = BigInteger.ZERO;
			for ( k = 1; k <= n; ++k )
				w = w.add(calcZ(n,k));
			System.out.println(n+", "+w.toString());
		}
	}
};

