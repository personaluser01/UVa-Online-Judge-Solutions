/*
 * 379. Hi-Q
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	int [][]g = new int[7][7];
	int []x = new int[36];
	int y[] = new int[36];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	static boolean validCell( int x, int y ) { return 0 <= x && x <= 6 && 0 <= y && y <= 6;	}
	void go() throws Exception {
		int i,j,k,l,t,ts,n,di,dj,ni,nj,best_src,best_dst;
		int []c = new int[36];

		k = 1;
		for ( j = 2; j <= 4;  ) {
			g[0][j++] = k;
			x[k] = 0; y[k] = j-1; ++k;
		}
		for ( j = 2; j <= 4;  ) {
			g[1][j++] = k;
			x[k] = 1; y[k] = j-1; ++k;
		}
		for ( j = 0; j <= 6;  ) {
			g[2][j++] = k;
			x[k] = 2; y[k] = j-1; ++k;
		}
		for ( j = 0; j <= 6;  ) {
			g[3][j++] = k;
			x[k] = 3; y[k] = j-1; ++k;
		}
		for ( j = 0; j <= 6;  ) {
			g[4][j++] = k;
			x[k] = 4; y[k] = j-1; ++k;
		}
		for ( j = 2; j <= 4;  ) {
			g[5][j++] = k;
			x[k] = 5; y[k] = j-1; ++k;
		}
		for ( j = 2; j <= 4;  ) {
			g[6][j++] = k;
			x[k] = 6; y[k] = j-1; ++k;
		}
		assert k == 34 ;

		String s;
		Scanner scan = new Scanner(System.in);
		ts = scan.nextInt();
		System.out.println("HI Q OUTPUT");
		while ( ts-- > 0 ) {
			for ( n = 0; (c[n]=scan.nextInt()) != 0; ++n );
			boolean [][]peg = new boolean[7][7];
			for ( i = 0; i < n; ++i )
				peg[x[c[i]]][y[c[i]]] = true;
			while ( true ) {
				best_dst = -1; best_src = -1;
				for ( i = 0; i < 7; ++i )
					for ( j = 0; j < 7; ++j )
						if ( g[i][j] >= 1 && peg[i][j] ) {
							for ( di = -2; di <= 2; di += 2 )
								for ( dj = -2; dj <= 2; dj += 2 ) {
									if ( (0==di && 0==dj) || (di!=0 && dj!=0) )
										continue ;
									ni = i+di; nj = j+dj;
									if ( !validCell(ni,nj) ) continue ;
									if ( peg[ni][nj] || 0==g[ni][nj] ) continue ;
									if ( !peg[i+di/2][j+dj/2] ) continue ;
									if ( g[ni][nj] > best_dst || g[ni][nj] == best_dst && g[i][j] > best_src ) {
										best_src = g[i][j];
										best_dst = g[ni][nj];
									}
								}
						}
				if ( best_dst == -1 ) break ;
				i = x[best_src]; j = y[best_src];
				ni = x[best_dst]; nj = y[best_dst];
				peg[i+(ni-i)/2][j+(nj-j)/2] = false;
				peg[i][j] = false;
				assert !peg[ni][nj];
				peg[ni][nj] = true;
			}
			k = 0;
			for ( i = 0; i < 7; ++i )
				for ( j = 0; j < 7; ++j )
					if ( peg[i][j] )
						k += g[i][j];
			System.out.println(k);
		}
		System.out.println("END OF OUTPUT");
	}
};

