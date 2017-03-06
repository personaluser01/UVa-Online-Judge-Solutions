/*
 * 215. Spreadsheet Calculator
 * TOPIC: dp, dfs, cycles
 * status: Almost Accepted (WA)
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final int N = 21, M = 11, Q = M*N;
	final double tol = 1e-6;
	int m,n,V,row,col;
	int []len = new int[Q], color = new int[Q], val = new int[Q], parent = new int[Q], pi = new int[Q];
	boolean []unknowable = new boolean[Q];
	double []B = new double[Q];
	double[][] a = new double[Q][Q];

	String[][] expres = new String[Q][], g = new String[Q][Q], orig = new String[Q][Q];
	Pattern var = Pattern.compile("([-+])([A-Z]?\\d+)");
	Matcher mm;
	Scanner scan = new Scanner(System.in);

	public static void main( String [] args ) throws Exception {new Main().go();}

	int conv( String s ) { return (int)(s.charAt(0)-'A')*n + (s.charAt(1)-'0');	}

	boolean getPivot( int r, int c ) {
		double w = 0;
		for ( int i = r; i < V; ++i )
			for ( int j = c; j < V; ++j ) 
				if ( Math.abs(a[i][j]) > w ) 
					w = Math.abs(a[row=i][col=j]);
		return w >= tol;
	}

	void swapRows( int i1, int i2 ) {
		double t;
		for ( int j = 0; j < V; ++j ) {
			t = a[i1][j]; a[i1][j] = a[i2][j]; a[i2][j] = t;
		}
		t = B[i1]; B[i1] = B[i2]; B[i2] = t;
	}

	void swapCols( int j1, int j2 ) {
		double t;
		int tmp;
		for ( int i = 0; i < V; ++i ) {
			t = a[i][j1]; a[i][j1] = a[i][j2]; a[i][j2] = t;
		}
		tmp = pi[j1]; pi[j1] = pi[j2]; pi[j2] = tmp;
	}


	class Summand {
		String var;
		boolean isInt,plus;
		Summand( String p, String s ) {
			this.plus = p.charAt(0)=='+'; this.var = s;
			this.isInt = ('0'<=s.charAt(0)&&s.charAt(0)<='9');
		}
	}

	Summand [][] lst = new Summand[Q][Q];
	int []seen = new int[Q],deg = new int[Q];
	int [][]adj = new int[Q][Q];
	int yes;

	boolean visit( int src, int x, int cost ) {
		if ( color[x] == 1 || unknowable[x] )
			return true;
		if ( color[x] == 2 )
			return false;
		color[x] = 1;
		for ( int i = 0; i < deg[x]; ++i )
			if ( visit(src,adj[x][i],cost+1) )
				return true;
		color[x] = 2;
		return false;
	}

	void go() throws Exception {
		int i,j,k,t,l;
		boolean ok;
		double cf,sx;
		double []X = new double[Q];

		while ( true ) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			for ( V = m*n, i = 0; i < V; ++i ) pi[i] = i;
			for ( i = 0; i < V; ++i )
				for ( a[i][i] = -1, val[i] = len[i] = deg[i] = 0, color[i] = 0, unknowable[i] = false, B[i] = 0, j = i+1; j < V; ++j )
					a[i][j] = a[j][i] = 0;
			for ( i = 0; i < m; ++i ) 
				for ( j = 0; j < n; ++j ) {
					g[i][j] = scan.next();
					orig[i][j] = new String(g[i][j]);
					if ( g[i][j].charAt(0) != '-' ) 
						g[i][j] = "+"+g[i][j];
					k=i*n+j; mm = var.matcher(g[i][j]);
					for(;mm.find();lst[k][len[k]++]=new Summand(mm.group(1),mm.group(2)));
					for ( l = 0; l < len[k]; ++l ) {
						if ( lst[k][l].isInt ) 
							B[k] += (lst[k][l].plus?-Integer.parseInt(lst[k][l].var):Integer.parseInt(lst[k][l].var));
						else {
							t = conv(lst[k][l].var);
							a[k][t] += (lst[k][l].plus?1:-1);
							adj[k][deg[k]++] = t;
						}
					}
				}
			for ( k = 0; k < V && getPivot(k,k); ++k ) {
				swapCols(k,col); 
				swapRows(k,row);
				for ( i = k+1; i < V; ++i ) {
					cf = a[i][k]/a[k][k];
					for ( j = k; j < V; ++j )
						a[i][j] = a[i][j]-cf*a[k][j];
					B[i] = B[i]-cf*B[k];
				}
			}
			for ( i = k; i < V; ++i ) unknowable[pi[i]] = true;

			ok = true; 

			for ( i = k-1; i >= 0; --i ) {
				for ( j = i+1; j < V; ++j )
					if ( Math.abs(a[i][j]) > tol && unknowable[pi[j]] ) {
						unknowable[pi[i]] = true;
						ok = false;
					}
				if ( !unknowable[i] && ok ) {
					for ( sx = 0, j = i+1; j < V; ++j ) {
						if ( !unknowable[pi[j]] )
							sx += a[i][j]*X[pi[j]];
					}
					X[pi[i]] = (B[i]-sx)/a[i][i];
				}
			}

			for ( i = 0; i < V; ++i ) {
				for ( j = 0; j < V; ++j ) color[j] = 0;
				if ( unknowable[i] |= visit(i,i,0) )
					ok = false;
			}

			if ( ok ) {
				for ( j = 0; j < n+1; ++j ) {
					if ( j == 0 ) System.out.printf(" ");
					else System.out.printf("%6d",j-1);
				}
				System.out.println();
				for ( i = 0; i < m; ++i ) {
					System.out.printf("%c",(char)(i+'A'));
					for ( j = 0; j < n; ++j ) 
						System.out.printf("%6d",(int)(X[i*n+j]));
					System.out.println("");
				}
			}
			else {
				for ( i = 0; i < V; ++i )
					if ( unknowable[i] ) 
						System.out.println(Character.toString((char)('A'+(i/n)))+(i%n)+": "+orig[i/n][i%n]);
			}
			System.out.println("");
		}
	}
};


