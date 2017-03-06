/*
 * 1638. Pole Arrangement
 * TOPIC: combinatorics, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	Scanner scan = new Scanner(System.in);
	int n,l,r;
	private static final int N = 21;

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	long [][][]z = new long[N][N][N];
	long [][]c = new long[N][N], Z = new long[N][N];

	void go() throws Exception {
		int i,j,k,t;
		for ( i = 0; i < N; ++i )
			c[i][0] = 1;
		for ( i = 1; i < N; ++i )
			for ( j = 1; j <= i; ++j )
				c[i][j] = c[i-1][j]+c[i-1][j-1];
		z[0][0][0] = Z[0][0] = 1L;
		for ( n = 1; n < N; ++n ) 
			for ( l = 1; l <= n; ++l ) {
				for ( r = 1; r <= n; ++r )
					for ( t = 1; t <= n; ++t )
						z[n][l][r] += c[n-1][t-1]*Z[t-1][l-1]*Z[n-t][r-1];
				for ( i = 1; i <= n; ++i )
					Z[n][l] += z[n][l][i];
			}
		for ( int ts = scan.nextInt(); ts-->0; ) {
			n = scan.nextInt();
			l = scan.nextInt();
			r = scan.nextInt();
			bw.write(z[n][l][r]+"\n");
		}
		bw.flush();
	}

}
