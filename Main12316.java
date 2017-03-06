/*
 * 12316. Sewing Buttons with Grandma
 * TOPIC: dp, combinatorics
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	final int N = 0x40;
	int m,K;
	int []n = new int[N];
	BigInteger [][]c = new BigInteger[N][N], z = new BigInteger[N][N];
	boolean [][]seen;
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	BigInteger calcZ( int idx, int placesLeft ) {
		if ( seen[idx][placesLeft] )
			return z[idx][placesLeft];
		assert idx <= K-1;
		z[idx][placesLeft] = BigInteger.ZERO;
		seen[idx][placesLeft] = true;
		if ( idx == K-1 ) {
			if ( placesLeft > n[idx] )
				return z[idx][placesLeft] = BigInteger.ZERO;
			return z[idx][placesLeft] = BigInteger.ONE;
		}
		for ( int k = 0; k<=n[idx] && k<=placesLeft; ++k ) 
			z[idx][placesLeft] = z[idx][placesLeft].add(c[placesLeft][k].multiply(calcZ(idx+1,placesLeft-k)));
		return z[idx][placesLeft];
	}
	void go() throws Exception {
		int i,j,k;
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				c[i][j] = BigInteger.ZERO;
		for ( i = 0; i < N; ++i )
			c[i][0] = BigInteger.ONE;
		for ( i = 1; i < N; ++i )
			for ( j = 1; j <= i; ++j )
				c[i][j] = c[i-1][j].add(c[i-1][j-1]);
		for (;;) {
			m = scan.nextInt();
			K = scan.nextInt();
			if ( m == 0 && K == 0 )
				break ;
			for ( i = 0; i < K; n[i++] = scan.nextInt() );
			seen = new boolean[K+1][m+1];
			System.out.println(calcZ(0,m));
		}
	}
};

