/*
 * 339. SameGame Simulation
 * TOPIC: floodfill
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int []dx = {-1,0,1,0}, dy = {0,1,0,-1};
	int [][]seen;
	int m,n,cs,yes,removed;
	boolean is_won;
	char [][]g;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	boolean vc( int x, int y ) { return  0<=x&&x<m&&0<=y&&y<n; };
	boolean emptyColumn( int c ) {
		for ( int i = 0; i < m; ++i )
			if ( g[i][c] != '*' )
				return false ;
		return true ;
	};
	boolean emptyDesk() {
		for ( int j = 0; j < n; ++j )
			if ( !emptyColumn(j) )
				return false ;
		return true ;
	};
	boolean isdigit( char ch ) { return '0'<=ch&&ch<='9'; };
	int dfs( int x, int y, char ch ) {
		int nx,ny,i,k=1;
		if ( seen[x][y] == yes || g[x][y] != ch ) return 0;
		for ( seen[x][y] = yes, g[x][y] = '*', i = 0; i < 4; ++i )
			if ( vc(nx=x+dx[i],ny=y+dy[i]) && g[nx][ny] == ch && seen[nx][ny] != yes )
				k += dfs(nx,ny,ch);
		return k;
	};
	void cleanUp() {
		int i,j;
		for ( j = 0; j < n; ++j )
			for ( boolean flag = true; flag; )
				for ( flag = false, i = m-1; i >= 1; --i )
					if ( g[i][j] != '*' && g[i-1][j] == '*' ) {
						char t = g[i][j]; g[i][j] = g[i-1][j]; g[i-1][j] = t; 
						flag = true ;
					};
	};
	void shift() {
		int i,j,k=0;
		for ( boolean flag = true; flag; )
			for ( flag = false, j = 0; j < n-1; ++j )
				if ( emptyColumn(j) && !emptyColumn(j+1) ) 
					for ( flag = true, i = 0; i < m; ++i ) {
						char t = g[i][j]; g[i][j] = g[i][j+1]; g[i][j+1] = t;
					}
		for ( j = n-1; j >= 0 && emptyColumn(j); --j, ++k );
		removed += m*k;
		n = ++j;
	};
	void go() throws Exception {
		int i,j,k,t,O,nn;
		char old;
		while ( true ) {
			m = scan.nextInt();
			n = scan.nextInt();
			if ( m == 0 || n == 0 ) break ;
			if ( cs >= 1 ) System.out.println("");
			System.out.println("Grid "+(++cs)+".");
			g = new char[m][n];
			seen = new int[m][n]; yes = 0;
			for ( nn=n, O = m*n, i = 0; i < m; ++i ) 
				for ( j = 0; j < n; g[i][j++] = (char)(scan.nextInt()+'0') );
			removed = 0;
			for ( is_won = false; true; ) {
				i = scan.nextInt();
				j = scan.nextInt();
				if ( i == 0 && j == 0 ) break ;
				--i; --j;
				if ( is_won || !vc(i,j) || !isdigit(g[i][j]) ) continue ;
				++yes; old = g[i][j];
				if ( (t=dfs(i,j,g[i][j])) <= 1 ) { g[i][j] = old; continue ; }
				removed += t; cleanUp(); shift();
				is_won |= 0==n;
			};
			if ( is_won )
				System.out.println("    Game Won");
			else {
				StringBuilder sb = new StringBuilder();
				for ( i = m-1; i >= 0; --i, sb.append("\n") ) {
					sb.append("   ");
					for ( j = 0; j < nn; ++j ) {
						sb.append(" ");
						if ( g[i][j] == '*' ) 
							sb.append(" ");
						else sb.append(g[i][j]);
					}
				}
				System.out.print(sb.toString());
			};
		};
	};
};

