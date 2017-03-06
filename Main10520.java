/*
 * 10520. Determine It
 * TOPIC: ad hoc, recursion, straightforward
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	int N = 22,n;
	BigInteger [][]a = new BigInteger[N][N];
	boolean [][]seen = new boolean[N][N];
	BigInteger TWO = new BigInteger("2");
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	BigInteger calc( int i, int j ) {
		int k;
		if ( seen[i][j] )
			return a[i][j];
		if ( i >= j ) {
			BigInteger A = new BigInteger("0"), B = new BigInteger("0"), Part1 = new BigInteger("0"), Part2 = new BigInteger("0");
			for ( k = i+1; k <= n; ++k ) {
				calc(k,1); calc(k,j);
				BigInteger r = a[k][1].add(a[k][j]);
				if ( r.compareTo(Part1) > 0 )
					Part1 = r;
			}
			a[i][j] = a[i][j].add(Part1);
			for ( k = 1; k <= j-1; ++k ) {
				calc(i,k); calc(n,k);
				BigInteger r = a[i][k].add(a[n][k]);
				if ( r.compareTo(Part2) > 0 )
					Part2 = r;
			}
			a[i][j] = a[i][j].add(Part2);
			seen[i][j] = true;
			return a[i][j];
		}
		else {
			BigInteger Part1 = new BigInteger("0");
			for ( k = i; k <= j-1; ++k ) {
				calc(i,k); calc(k+1,j);
				BigInteger r = a[i][k].add(a[k+1][j]);
				if ( r.compareTo(Part1) > 0 )
					Part1 = r;
			}
			a[i][j] = Part1;
			seen[i][j] = true;
			return a[i][j];
		}
	}
	void go() throws Exception {
		int i,j,k,l,t;
		Scanner scan = new Scanner(System.in);
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			for ( i = 1; i <= n; ++i )
				for ( j = 1; j <= n; ++j ) {
					seen[i][j] = false;
					a[i][j] = new BigInteger("0");
				}
			a[n][1] = BigInteger.valueOf(scan.nextInt());
			seen[n][1] = true;
			for ( j = 2; j <= n; ++j ) {
				a[n][j] = a[n][j-1].add(a[n][j-1]);
				seen[n][j] = true;
			}
			System.out.println(calc(1,n).toString());
		}
	}
};

