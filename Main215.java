/*
 * 215. Spreadsheet Calculator
 * TOPIC: dp, system of linear equations
 * status:
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	final int N = 20, M = 10, Q = M*N;
	int m,n,V,row,col;
	int []len = new int[Q], pi = new int[Q];
	double []B = new double[Q];
	double[][] a = new double[Q][Q];
	String[][] expres = new String[Q][], g = new String[Q][Q], orig = new String[Q][Q];
	Pattern var = Pattern.compile("([-+])([A-Z]?\\d+)");
	Matcher mm;
	Scanner scan = new Scanner(System.in);

	public static void main( String [] args ) throws Exception { new Main().go(); }

	int conv( String s ) { return (int)(s.charAt(0)-'A')*n + (s.charAt(1)-'0');	}

	boolean getPivot( int r, int c ) {
		int i,j;
		double w = 0;
		for ( i = r; i < V; ++i )
			for ( j = c; j < V; ++j ) 
				if ( Math.abs(a[i][j]) > w ) 
					w = Math.abs(a[row=i][col=j]);
		return w > 0.00;
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

	void go() throws Exception {
		int i,j,k,t,l;
		double cf,sx;
		double []X = new double [Q];
		boolean []unknowable = new boolean[Q];
		while ( true ) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			for ( i = 0; i < m*n; ++i )
				for ( B[i] = 0, j = 0; j < m*n; ++j ) 
					a[i][j] = 0;
			for ( i = 0; i < m*n; ++i )
				a[i][i] = -1;
			for ( i = 0; i < m; ++i ) 
				for ( j = 0; j < n; ++j ) {
					g[i][j] = scan.next("[^\\s]+");
					orig[i][j] = new String(g[i][j]);
					if ( g[i][j].charAt(0) != '-' ) 
						g[i][j] = "+"+g[i][j];
					k = i*n+j;
					mm = var.matcher(g[i][j]);
					while ( mm.find() )
						if ( mm.group(1).equals("+") ) {
							if ( '0' <= mm.group(2).charAt(0) && mm.group(2).charAt(0) <= '9' ) 
								B[k] = B[k]-Integer.parseInt(mm.group(2));
							else { t = conv(mm.group(2)); a[k][t] = a[k][t]+1; }
						}
						else {
							if ( '0' <= mm.group(2).charAt(0) && mm.group(2).charAt(0) <= '9' ) 
								B[k] = B[k]+Integer.parseInt(mm.group(2));
							else { t = conv(mm.group(2)); a[k][t] = a[k][t]-1; }
						}
				}
			for ( V = m*n, i = 0; i < V; ++i ) pi[i] = i;
			for ( k = 0; k < V && getPivot(k,k); ++k ) {
				swapCols(k,col); swapRows(k,row);
				for ( i = k+1; i < V; ++i ) {
					cf = a[i][k]/a[k][k];
					for ( j = k; j < V; ++j )
						a[i][j] = a[i][j]-cf*a[k][j];
					B[i] = B[i]-cf*B[k];
				}
			}
			if ( k == V ) {
				for ( i = V-1; i >= 0; --i ) {
					for ( sx = 0, j = i+1; j < V; ++j )
						sx = sx+X[pi[j]]*a[i][j];
					X[pi[i]] = (B[i]-sx)/a[i][i];
				}
				for ( j = 0; j < n+1; ++j ) {
					if ( j == 0 ) System.out.printf(" ");
					else System.out.printf("%6d",j-1);
				}
				System.out.println();
				for ( i = 0; i < m; ++i ) {
					System.out.printf("%c",(char)(i+'A'));
					for ( j = 0; j < n; ++j ) {
						System.out.printf("%6d",(int)(X[i*n+j]));
					}
					System.out.println("");
				}
			}
			else {
				for ( i = 0; i < V; ++i ) unknowable[i] = false;
				for ( i = k; i < V; ++i )
					unknowable[pi[i]] = true;
				for ( i = k-1; i >= 0; --i ) 
					for ( j = i+1; j < V; ++j )
						if ( Math.abs(a[i][j]) > 0 && unknowable[pi[j]] )
							unknowable[pi[i]] = true;
				for ( i = 0; i < V; ++i )
					if ( unknowable[i] ) 
						System.out.println(Character.toString((char)('A'+(i/n)))+(i%n)+": "+orig[i/n][i%n]);
			}
			System.out.println("");
		}
	}
};

