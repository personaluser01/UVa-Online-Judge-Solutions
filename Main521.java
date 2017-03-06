/*
 * 521. Gossiping
 * TOPIC: graph theory, diophantine equations
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int oo = (1<<29);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	StringTokenizer st;
	boolean ok;
	int lines,m,n;
	int []len,b,id;
	int [][]g,e,r,c,d;
	int gcd( int x, int y ) { if ( y == 0 ) return x; return gcd(y,x%y); }
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,l,cur;
		while ( true ) {
			st = new StringTokenizer(s = br.readLine());
			lines = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			if ( lines == 0 && m == 0 && n == 0 )
				break ;
			g = new int[m][n];
			d = new int[m][m];
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					g[i][j] = +oo;
			for ( i = 0; i < m; ++i )
				for ( d[i][i] = 0, j = i+1; j < m; ++j )
					d[j][i] = d[i][j] = +oo;
			len = new int[lines];
			id = new int[m];
			e = new int[lines][n+n];
			b = new int[m];
			r = new int[lines][n+n];
			for ( i = 0; i < lines; ++i )
				for ( j = 0; j < n; ++j )
					r[i][j] = -1;
			for ( k = 0; k < lines; ++k ) {
				st = new StringTokenizer(s = br.readLine());
				for ( len[k] = 0; st.hasMoreTokens();) {
					e[k][len[k]++] = Integer.parseInt(st.nextToken());
					r[k][e[k][len[k]-1]] = len[k]-1;
				}
				st = new StringTokenizer(s = br.readLine());
				for(;st.hasMoreTokens();) {
					j = Integer.parseInt(st.nextToken())-1;
					i = Integer.parseInt(st.nextToken())-1;
					id[i]=k; b[i]=j;
				}
			}
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j ) 
					if ( r[id[i]][j] != -1 ) 
						for ( g[i][j] = 0, l = r[id[i]][cur=b[i]]; cur != j; ++g[i][j] ) {
							++l; l %= len[id[i]]; cur = e[id[i]][l];
						}
			for ( i = 0; i < m; ++i )
				for ( j = i+1; j < m; ++j )
					for ( k = 0; k < n && d[i][j] == +oo; ++k )
						if ( g[i][k] < +oo && g[j][k] < +oo ) {
							if ( (g[j][k]-g[i][k])%gcd(len[id[i]],len[id[j]]) == 0 )
								d[i][j] = d[j][i] = 1;
						}
			for ( k = 0; k < m; ++k )
				for ( i = 0; i < m; ++i )
					for ( j = 0; j < m; ++j )
						if ( d[i][k] < +oo && d[k][j] < +oo )
							if ( d[i][j] > d[i][k]+d[k][j] )
								d[i][j] = d[i][k]+d[k][j];
			for ( ok = true, i = 0; i < m && ok; ++i )
				for ( j = 0; j < m && ok; ++j )
					if ( d[i][j] == +oo )
						ok = false;
			if ( ok ) System.out.println("Yes");
			else System.out.println("No");
		}
	}
};

