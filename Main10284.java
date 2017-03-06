/*
 * 10284. Chessboard in FEN
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.lang.Math.*;

class Main {
	static boolean validCell( int x, int y ) { return 0 <= x && x < 8 && 0 <= y && y < 8; }
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,ni,nj,di,dj,l;
		char [][]g;
		String s,t;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ( (s = br.readLine()) != null ) {
			st = new StringTokenizer(s,"/");
			g = new char[8][];
			for ( i = 0; i < 8; ++i ) {
				t = st.nextToken();
				k = 0;
				g[i] = new char[8];
				for ( j = 0; j < 8; ++j )
					g[i][j] = '*';
				for ( j = 0; j < t.length(); ++j ) {
					if ( '0' <= t.charAt(j) && t.charAt(j) <= '9' ) {
						k += (int)(t.charAt(j)-'0');
					}
					else {
						g[i][k] = t.charAt(j);
						++k;
					}
				}
				assert k == 8;
			}
			for ( i = 0; i < 8; ++i ) 
			for ( j = 0; j < 8; ++j ) {
				if ( g[i][j] == '*' || g[i][j] == 'x' )
					continue ;
				if ( g[i][j] == 'k' || g[i][j] == 'K' ) {
					for ( di = -1; di <= 1; ++di )
						for ( dj = -1; dj <= 1; ++dj ) {
							ni = i+di;
							nj = j+dj;
							if ( Main.validCell(ni,nj) && g[ni][nj] == '*' ) 
								g[ni][nj] = 'x';
						}
					continue ;
				}
				if ( g[i][j] == 'q' || g[i][j] == 'Q' ) {
					for ( di = -1; di <= 1; ++di )
						for ( dj = -1; dj <= 1; ++dj ) {
							if ( 0==di && 0==dj ) continue ;
							for ( k = 1; k <= 8; ++k ) {
								ni = i+k*di;
								nj = j+k*dj;
								if ( !Main.validCell(ni,nj) || (g[ni][nj] != '*' && g[ni][nj] != 'x') )
									break ;
								g[ni][nj] = 'x';
							}
						}
					continue ;
				}
				if ( g[i][j] == 'p' ) {
					ni = i+1; nj = j+1;
					if ( Main.validCell(ni,nj) && (g[ni][nj] == '*' || g[ni][nj] == 'x') )
						g[ni][nj] = 'x';
					ni = i+1; nj = j-1;
					if ( Main.validCell(ni,nj) && (g[ni][nj] == '*' || g[ni][nj] == 'x') )
						g[ni][nj] = 'x';
					continue ;
				}
				if ( g[i][j] == 'r' || g[i][j] == 'R' ) {
					for ( di = -1; di <= 1; ++di )
						for ( dj = -1; dj <= 1; ++dj ) {
							if ( di != 0 && dj != 0 )
								continue ;
							if ( 0==di && 0==dj )
								continue ;
							assert 0 == di && dj != 0 || 0 == dj && di != 0;
							for ( k = 1; k <= 8; ++k ) {
								ni = i+k*di; nj = j+k*dj;
								if ( !Main.validCell(ni,nj) || (g[ni][nj] != 'x' && g[ni][nj] != '*') )
									break ;
								g[ni][nj] = 'x';
							}
						}
					continue ;
				}
				if ( g[i][j] == 'b' || g[i][j] == 'B' ) {
					for ( di = -1; di <= 1; ++di )
						for ( dj = -1; dj <= 1; ++dj ) {
							if ( 0==di || 0==dj ) continue ;
							assert di != 0 && dj != 0;
							for ( k = 1; k <= 8; ++k ) {
								ni = i+k*di; nj = j+k*dj;
								if ( !Main.validCell(ni,nj) || (g[ni][nj] != '*' && g[ni][nj] != 'x') )
									break ;
								g[ni][nj] = 'x';
							}
						}
					continue ;
				}
				if ( g[i][j] == 'n' || g[i][j] == 'N' ) {
					for ( di = -2; di <= 2; ++di )
						for ( dj = -2; dj <= 2; ++dj ) {
							if ( 0==di || 0==dj ) continue ;
							if ( Math.abs(di)+Math.abs(dj) == 3 ) {
								ni = i+di; nj = j+dj;
								if ( Main.validCell(ni,nj) && g[ni][nj] == '*' )
									g[ni][nj] = 'x';
							}
						}
					continue ;
				}
				if ( g[i][j] == 'P' ) {
					ni = i-1; nj = j+1;
					if ( Main.validCell(ni,nj) && (g[ni][nj] == '*' || g[ni][nj] == 'x') )
						g[ni][nj] = 'x';
					ni = i-1; nj = j-1;
					if ( Main.validCell(ni,nj) && (g[ni][nj] == '*' || g[ni][nj] == 'x') )
						g[ni][nj] = 'x';
					continue ;
				}
			}
			k = 0;
			for ( i = 0; i < 8; ++i )
				for ( j = 0; j < 8; ++j )
					if ( g[i][j] == '*' )
						++k;
			/*
			for ( i = 0; i < 8; ++i ) {
				for ( j = 0; j < 8; ++j )
					System.out.printf("%c",g[i][j]);
				System.out.println("");
			}
			*/
			System.out.println(k);
		}
	}
};

