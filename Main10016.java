/*
 * Flip-Flop
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,l,t,ts,n,m,r1,r2,tmp,ii,jj,c1,c2;
		int [][]c;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		while ( ts-- > 0 ) {
			n = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
			c = new int[n][n]; m = (n>>1)+(n&1);
			for ( i = 0; i < n; ++i ) {
				st = new StringTokenizer(br.readLine());
				for ( j = 0; j < n; ++j ) 
					c[i][j] = Integer.parseInt(st.nextToken());
			}
			for ( k = 0; k < m; ++k ) {
				st = new StringTokenizer(br.readLine());
				for ( l = Integer.parseInt(st.nextToken()); l-- > 0; ) {
					j = Integer.parseInt(st.nextToken());
					if ( j == 1 ) {
						r1 = k; r2 = n-1-k;
						for ( t = k; t <= n-1-k; ++t ) {
							tmp = c[r1][t]; c[r1][t] = c[r2][t]; c[r2][t] = tmp;
						}
						ii = k+1; jj = n-1-k-1;
						while ( ii < jj ) {
							tmp = c[ii][k]; c[ii][k] = c[jj][k]; c[jj][k] = tmp;
							tmp = c[ii][n-1-k]; c[ii][n-1-k] = c[jj][n-1-k]; c[jj][n-1-k] = tmp;
							++ii; --jj;
						}
						continue ;
					}
					if ( j == 2 ) {
						c1 = k; c2 = n-1-k;
						for ( t = k; t <= n-1-k; ++t ) {
							tmp = c[t][c1]; c[t][c1] = c[t][c2]; c[t][c2] = tmp;
						}
						ii = k+1; jj = n-1-k-1;
						while ( ii < jj ) {
							tmp = c[k][ii]; c[k][ii] = c[k][jj]; c[k][jj] = tmp;
							tmp = c[n-k-1][ii]; c[n-1-k][ii] = c[n-1-k][jj]; c[n-1-k][jj] = tmp;
							++ii; --jj;
						}
						continue ;
					}
					if ( j == 3 ) {
						ii = k+1; jj = k+1;
						while ( ii <= n-k-1 ) {
							tmp = c[ii][k]; c[ii][k] = c[k][jj]; c[k][jj] = tmp;
							++ii; ++jj;
						}
						ii = k+1; jj = k+1;
						while ( ii < n-k-1 ) {
							tmp = c[n-1-k][jj]; c[n-1-k][jj] = c[ii][n-1-k]; c[ii][n-1-k] = tmp;
							++ii; ++jj;
						}
						continue ;
					}
					if ( j == 4 ) {
						jj = k; ii = n-1-k;
						while ( jj <= n-1-k ) {
							//System.out.printf("c[%d][%d] = %d, c[%d][%d] = %d\n",k,jj,c[k][jj],ii,n-1-k,c[ii][n-1-k]);
							//System.out.println("Exchanging "+c[k][jj]+" "+c[ii][n-1-k]);
							tmp = c[k][jj]; c[k][jj] = c[ii][n-1-k]; c[ii][n-1-k] = tmp;
							--ii; ++jj;
						}
						ii = k+1; jj = n-k-1-1;
						while ( ii <= n-1-k ) {
							//System.out.println("Exchanging "+c[ii][k]+" "+c[n-1-k][jj]);
							tmp = c[ii][k]; c[ii][k] = c[n-1-k][jj]; c[n-1-k][jj] = tmp;
							++ii; --jj;
						}
						continue ;
					}
				}
			}
			for ( i = 0; i < n; ++i ) {
				for ( j = 0; j < n; ++j )
					if ( j > 0 )
						System.out.printf(" %d",c[i][j]);
					else System.out.printf("%d",c[i][j]);
				System.out.println("");
			}
		}
	}
};

