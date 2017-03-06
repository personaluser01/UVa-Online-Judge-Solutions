/*
 * 1207. AGTC
 * TOPIC: DP
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x400, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int m,n;
	String a,b;
	int [][]c = new int[N][N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k;
		while ( scan.hasNext() ) {
			m = scan.nextInt();
			a = scan.next();
			n = scan.nextInt();
			b = scan.next();
			for ( i = 0; i <= m; ++i )
				for ( j = 0; j <= n; ++j )
					c[i][j] = +oo;
			for ( i = 0; i <= m; ++i ) c[i][0] = i;
			for ( j = 0; j <= n; ++j ) c[0][j] = j;
			for ( i = 1; i <= m; ++i )
				for ( j = 1; j <= n; ++j ) {
					if ( a.charAt(i-1) == b.charAt(j-1) ) 
						c[i][j] = c[i-1][j-1];
					else c[i][j] = c[i-1][j-1]+1;
					c[i][j] = Math.min(c[i][j],c[i-1][j]+1);
					c[i][j] = Math.min(c[i][j],c[i][j-1]+1);
				}
			System.out.println(c[m][n]);
		}
	}
};

