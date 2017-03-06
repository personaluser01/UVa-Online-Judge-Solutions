/*
 * 12187. Brothers
 * TOPIC: ad hoc, wave algorithm
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x80;
	int m,n,b,battles;
	int [][][]c = new int[2][N][N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	boolean vc( int x, int y ) { return 0<=x && x<=m-1 && 0<=y && y <=n-1; }
	boolean hates ( int x, int y ) {
		int z = (x+1)%b;
		return z == y;
	}
	void go() throws Exception {
		int i,j,k,l,t,ni,nj;
		while ( true ) {
			b = scan.nextInt();
			m = scan.nextInt();
			n = scan.nextInt();
			battles = scan.nextInt();
			if ( m == 0 && n == 0 && b == 0 && battles == 0 )
				break ;
			for ( t = 0, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					c[t][i][j] = scan.nextInt();
			for (;battles-->0;) {
				for ( t ^= 1, i = 0; i < m; ++i )
					for ( j = 0; j < n; ++j )
						c[t][i][j] = c[t^1][i][j];
				for ( i = 0; i < m; ++i )
					for ( j = 0; j < n; ++j ) 
						for ( ni = i-1; ni <= i+1; ++ni )
							for ( nj = j-1; nj <= j+1; ++nj )
								if ( vc(ni,nj) && Math.abs(ni-i)+Math.abs(nj-j)==1 )
									if ( hates(c[t^1][i][j],c[t^1][ni][nj]) )
										c[t][ni][nj] = c[t^1][i][j];
			}
			for ( i = 0; i < m; ++i, System.out.println() )
				for ( j = 0; j < n; ++j ) {
					if ( j > 0 ) System.out.print(" ");
					System.out.print(c[t][i][j]);
				}
		}
	}
};

