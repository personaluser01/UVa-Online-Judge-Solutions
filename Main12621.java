/*
 * 12621. On a Diet
 * TOPIC: dp, subset sum
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int W = 250*100;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),cal,m,T,t,n;
		int []c;
		boolean [][]is = new boolean[2][W+1];
		while ( ts-- > 0 ) {
			cal = scan.nextInt();
			assert( 0 == (cal%10) );
			cal /= 10;
			n = m = scan.nextInt();
			c = new int[m+1];
			T = 0;
			for ( i = 1; i <= n; ++i ) {
				c[i] = scan.nextInt();
				assert( 0 == (c[i]%10) );
				c[i] /= 10;
				T += c[i];
			}
			for ( i = 0; i <= 1; ++i )
				for ( j = 1; j <= T; ++j )
					is[i][j] = false;
			is[0][0]=is[1][0]=true;
			t = 0;
			for ( i = 1; i <= n; ++i ) {
				t ^= 1;
				for ( j = 0; j <= T; ++j )
					is[t][j] = is[t^1][j];
				for ( j = 0; j+c[i] <= T; ++j )
					if ( is[t^1][j] )
						is[t][j+c[i]] = true;
			}
			for ( j = cal; j <= T && !is[t][j]; ++j );
			if ( j >= T+1 ) {
				System.out.println("NO SOLUTION");
				continue ;
			}
			System.out.println(j*10);
		}
	}
};

