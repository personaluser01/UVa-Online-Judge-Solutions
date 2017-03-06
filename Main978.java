/*
 *
 * status: Accepted
 * TOPIC: priority queue, simulation
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,ts,m;
		int []n = new int[2];
		int [][]c;
		int []len;
		int []L;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s;
		StringTokenizer st;

		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		while ( ts-- > 0 ) {
			st = new StringTokenizer(br.readLine());
			m = Integer.parseInt(st.nextToken());
			c = new int[2][];
			len = new int[2];
			L = new int[2];
			for ( i = 0; i <= 1; ++i ) {
				n[i] = Integer.parseInt(st.nextToken());
				c[i] = new int[n[i]];
			}
			PriorityQueue []q = new PriorityQueue[2];
			for ( i = 0; i <= 1; ++i ) {
				q[i] = new PriorityQueue(n[i]);
				for ( j = 0; j < n[i]; ++j ) {
					c[i][j] = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
					q[i].add(-c[i][j]);
				}
			}
			while ( !q[0].isEmpty() && !q[1].isEmpty() ) {
				for ( i = 0; i <= 1; ++i ) {
					len[i] = 0;
					for ( k = 0; k < m && !q[i].isEmpty(); ++k ) {
						j = (int)q[i].peek();
						q[i].remove((Object)j);
						c[i][k] = -j; ++len[i];
					}
				}
				for ( j = 0; j < len[0] && j < len[1]; ++j ) {
					for ( i = 0; i <= 1; ++i ) 
						L[i] = c[i][j];
					if ( L[0] == L[1] ) continue ;
					if ( L[0] > L[1] ) {
						L[0] -= L[1];
						q[0].add(-L[0]);
					}
					else {
						L[1] -= L[0];
						q[1].add(-L[1]);
					}
				}
				for ( i = 0; i <= 1; ++i )
					for ( ;j < len[i]; ++j )
						q[i].add(-c[i][j]);
			}
			if ( q[0].size() == 0 && q[1].size() == 0 ) {
				System.out.println("green and blue died");
			}
			else if ( q[0].size() > 0 ) {
				System.out.println("green wins");
			}
			else {
				System.out.println("blue wins");
			}
			for ( i = 0; i <= 1; ++i ) {
				while ( !q[i].isEmpty() ) {
					j = (int)q[i].peek();
					q[i].remove((Object)j);
					System.out.println(-j);
				}
			}
			if ( ts > 0 ) System.out.println("");
		}
	}
};

