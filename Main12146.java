/*
 * 12146. Candy
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int oo = 2000000000;
	int m,n;
	int [][]c,z,r;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	int calc_r( int i, int j ) {
		if ( i <= 0 || j <= 0 ) return 0;
		if ( r[i][j] < +oo )
			return r[i][j];
		return r[i][j] = Math.max(c[i][j]+calc_r(i,j-2),calc_r(i,j-1));
	};
	int calc_z( int i, int j ) {
		if ( i <= 0 || j < 0 ) return 0;
		if ( z[i][j] < +oo )
			return z[i][j];
		if ( j == 0 ) 
			return z[i][j] = calc_z(i-1,n);
		return z[i][j] = Math.max(c[i][j]+calc_z(i-2,n)+calc_r(i,j-2),calc_z(i,j-1));
	};
	void go() throws Exception {
		int i,j,k;
		for(;;) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			c = new int[m+2][n+2];
			for ( i = 1; i <= m; ++i )
				for ( j = 1; j <= n; ++j )
					c[i][j] = scan.nextInt();
			z = new int[m+2][n+2];
			r = new int[m+2][n+2];
			for ( i = 0; i <= m+1; ++i )
				for ( j = 0; j <= n+1; ++j )
					r[i][j] = z[i][j] = +oo;
			System.out.println(calc_z(m,n));
		};
	};
};

