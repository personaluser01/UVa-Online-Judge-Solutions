/*
 * 12319. Edgetown's Traffic Jams
 * TOPIC: floyd-warshall
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80, oo = (1<<29);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	StringTokenizer st;
	int m,n,A,B;
	boolean flag;
	int [][][]d = new int[2][N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,l,t;
		for ( ;(s = br.readLine()) != null; System.out.println(flag?"Yes":"No") ) {
			if ( 0 == (n = Integer.parseInt(s)) ) break ;
			for ( t = 0; t <= 1; ++t ) {
				for ( i = 0; i < n; ++i )
					for ( j = i+1; j < n; ++j )
						d[t][j][i] = d[t][i][j] = +oo;
				for ( l = 0; l < n; ++l ) {
					st = new StringTokenizer(br.readLine());
					i = Integer.parseInt(st.nextToken())-1;
					for (;st.hasMoreTokens(); ) {
						j = Integer.parseInt(st.nextToken())-1;
						d[t][i][j] = 1;
						// if ( t == 0 ) d[t][j][i] = 1;
					}
				}
				for ( k = 0; k < n; ++k )
					for ( i = 0; i < n; ++i )
						for ( j = 0; j < n; ++j )
							if ( d[t][i][k] < +oo && d[t][k][j] < +oo )
								if ( d[t][i][k]+d[t][k][j] < d[t][i][j] )
									d[t][i][j] = d[t][i][k]+d[t][k][j];
			}
			st = new StringTokenizer(br.readLine());
			A = Integer.parseInt(st.nextToken());
			B = Integer.parseInt(st.nextToken());
			for ( flag = true, i = 0; i < n && flag; ++i )
				for ( j = 0; j < n && flag; ++j )
					if ( i != j && d[0][i][j] < +oo )
						if ( d[1][i][j] > A*d[0][i][j]+B )
							flag = false;
		}
	}
};

