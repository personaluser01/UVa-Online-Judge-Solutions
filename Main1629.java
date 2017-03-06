/*
 * 1629. Cake Slicing
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x20, oo = (1<<29);
	int m,n,K,yes;
	int []xx,yy;
	int [][][][]z = new int[N][N][N][N],seen = new int[N][N][N][N];
	int [][]c = new int[N][N];
	boolean [][]cherry = new boolean[N][N];
	int cnt( int i, int j, int k, int l ) {
		return c[k][l]-c[i-1][l]-c[k][j-1]+c[i-1][j-1];
	}
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	int calc_z( int i, int j, int k, int l ) {
		assert( i <= k && j <= l );
		if ( seen[i][j][k][l] == yes )
			return z[i][j][k][l];
		if ( 0 == cnt(i,j,k,l) ) {
			seen[i][j][k][l] = yes;
			return z[i][j][k][l] = +oo;
		}
		assert( i < k || j < l );
		seen[i][j][k][l] = yes;
		if ( cnt(i,j,k,l) == 1 ) 
			return z[i][j][k][l] = 0;
		for ( int t = i; t <= k-1; ++t ) 
			if ( calc_z(i,j,t,l) < +oo && calc_z(t+1,j,k,l) < +oo )
				if ( z[i][j][k][l] > (l-j+1)+z[i][j][t][l]+z[t+1][j][k][l] )
					z[i][j][k][l] = (l-j+1)+z[i][j][t][l]+z[t+1][j][k][l];
		for ( int t = j; t <= l-1; ++t )
			if ( calc_z(i,j,k,t) < +oo && calc_z(i,t+1,k,l) < +oo )
				if ( z[i][j][k][l] > (k-i+1)+z[i][j][k][t]+z[i][t+1][k][l] )
					z[i][j][k][l] = (k-i+1)+z[i][j][k][t]+z[i][t+1][k][l];
		return z[i][j][k][l];
	}
	void go() throws Exception {
		int i,j,k,l,t,cs = 0;
		while ( scan.hasNext() ) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 && n == 0 ) break ;
			for ( i = 0; i <= m; ++i )
				for ( j = 0; j <= n; c[i][j++] = 0 )
					for ( k = 0; k <= m; ++k )
						for ( l = 0; l <= n; z[i][j][k][l++] = +oo );
			K = scan.nextInt();
			xx = new int[K];
			yy = new int[K];
			for ( i = 0; i <= m; ++i )
				for ( j = 0; j <= n; cherry[i][j++] = false );
			for ( ++yes, i = 0; i < K; ++i ) {
				xx[i] = scan.nextInt();
				yy[i] = scan.nextInt();
				cherry[xx[i]][yy[i]] = true ;
				seen[xx[i]][yy[i]][xx[i]][yy[i]] = yes;
				z[xx[i]][yy[i]][xx[i]][yy[i]] = 0;
			}
			for ( i = 1; i <= m; ++i )
				for ( j = 1; j <= n; ++j )
					c[i][j] = c[i-1][j]+c[i][j-1]-c[i-1][j-1]+(cherry[i][j]?1:0);
			assert( cnt(1,1,m,n) == K );
			System.out.println("Case "+(++cs)+": "+calc_z(1,1,m,n));
		}
	}
};

