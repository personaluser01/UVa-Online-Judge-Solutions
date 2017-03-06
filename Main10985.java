/*
 * 10985. Rings'n'Ropes
 * TOPIC: floyd-warshall, dp, cubic
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int n,m,ts;
	int [][]d = new int[N][N], f = new int[N][N], z = new int[N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,l,t,ts = scan.nextInt(),cs = 0,ans = 0,w;
		for ( ;ts-- > 0; ) {
			n = scan.nextInt();
			m = scan.nextInt();
			for ( i = 0; i < n; ++i )
				for ( d[i][i] = 0, j = i+1; j < n; ++j ) {
					d[i][j] = d[j][i] = +oo;
					f[i][j] = f[j][i] = 0;
					z[i][j] = z[j][i] = 0;
				}
			for ( k = 0; k < m; ++k ) {
				i = scan.nextInt();
				j = scan.nextInt();
				d[j][i] = d[i][j] = 1;
			}
			for ( k = 0; k < n; ++k )
				for ( i = 0; i < n; ++i )
					for ( j = 0; j < n; ++j )
						if ( d[i][k] < +oo && d[k][j] < +oo )
							if ( d[i][k]+d[k][j] < d[i][j] )
								d[i][j] = d[i][k]+d[k][j];
			for ( i = 0; i < n; ++i )
				for ( k = 0; k < n; ++k )
					if ( d[i][k] == 1 )
						for ( j = 0; j < n; ++j )
							if ( d[i][j] < +oo && d[k][j] < +oo )
								if ( d[i][j] == d[i][k] + d[k][j] )
									++f[i][j];
			for ( ans = 0, i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j, ans = Math.max(ans,w) )
					for ( w = 0, k = 0; k < n; ++k )
						if ( d[i][k] < +oo && d[k][j] < +oo )
							if ( d[i][j] == d[i][k] + d[k][j] )
								w += f[k][j];
			System.out.println("Case #"+(++cs)+": "+ans);
		}
	}
};

