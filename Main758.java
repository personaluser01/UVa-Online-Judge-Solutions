/*
 * 758. Same Game
 * TOPIC: floodfill
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int m = 10, n = 15;
	char [][]g = new char[m+1][n+1],og = new char[m+1][n+1];
	int []dx = {-1,0,1,0}, dy = {0,1,0,-1};
	int yes;
	int [][]seen = new int[m+1][n+1];
	Scanner scan = new Scanner(System.in);
	boolean vc( int x, int y ) { return 0<=x&&x<m&&0<=y&&y<n; };
	int P( int w ) { return (w-2)*(w-2); };
	class Sol implements Comparable<Sol> {
		int x,y,w;
		Sol() {w=0;};
		Sol( int X, int Y, int W ) { this.x=X; this.y=Y; this.w=W; };
		public int compareTo( Sol other ) {
			if ( this.w == other.w ) {
				if ( this.y == other.y )
					return this.x-other.x;
				return this.y-other.y;
			};
			return other.w-this.w;
		};
		public String toString( int k, char ch ) {
			StringBuilder sb = new StringBuilder();
			sb.append("Move "+k+" at ("+(x+1)+","+(y+1)+"): removed "+w+" balls of color "+ch+", got "+P(w)+" points.");
			return sb.toString();
		};
	};
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	int dfs( int x, int y, char ch ) {
		int nx,ny,i,k=0;
		if ( seen[x][y] == yes ) return 0;
		for ( k=1, seen[x][y] = yes, i = 0; i < 4; ++i ) 
			if ( vc(nx=x+dx[i],ny=y+dy[i]) && seen[nx][ny] != yes && g[nx][ny] == ch )
				k += dfs(nx,ny,ch);
		return k;
	};
	void mark( int x, int y, char ch ) {
		int i,nx,ny;
		if ( seen[x][y] == yes )
			return ;
		for ( seen[x][y] = yes, g[x][y] = '*', i = 0; i < 4; ++i ) 
			if ( vc(nx=x+dx[i],ny=y+dy[i]) && seen[nx][ny] != yes && g[nx][ny] == ch )
				mark(nx,ny,ch);
	};
	void cleanUp() {
		int i,j;
		for ( j = 0; j < n; ++j ) 
			for ( boolean flag = true; flag; ) 
				for ( flag = false, i = m-1; i >= 1; --i )
					if ( g[i][j] != '*' && g[i-1][j] == '*' ) {
						char t = g[i][j]; g[i][j] = g[i-1][j]; g[i-1][j] = t;
						flag = true ;
					}
	};
	void compact() {
		int i,j;
		for ( i = 0; i < m; ++i )
			for ( boolean flag = true; flag; )
				for ( flag = false, j = n-1; j >= 1; --j )
					if ( g[i][j-1] == '*' && g[i][j] != '*' ) {
						char t = g[i][j]; g[i][j] = g[i][j-1]; g[i][j-1] = t;
						flag = true ;
					}
	};
	boolean isEmpty( int c ) {
		for ( int i = 0; i < m; ++i )
			if ( g[i][c] != '*' )
				return false ;
		return true ;
	};
	void go() throws Exception {
		int ts = scan.nextInt(),i,j,k,ans,step,cs = 0;
		boolean allRemoved;
		Sol s,t;
		for (;ts-->0;) {
			System.out.println("Game "+(++cs)+":\n");
			for ( allRemoved = false, i = m-1; i >= 0; --i ) {
				g[i] = scan.next().toCharArray();
				for ( j = 0; j < n; ++j )
					og[i][j] = g[i][j];
			}
			for ( step = 0, ans = 0; ++yes > 0;) {
				s = new Sol(0,0,0);
				for ( j = 0; j < n; ++j )
					for ( i = 0; i < m; ++i )
						if ( seen[i][j] != yes && g[i][j] != '*' ) {
							k = dfs(i,j,g[i][j]);
							t = new Sol(i,j,k);
							if ( t.compareTo(s) < 0 )
								s = t;
						}
				if ( s.w == 0 ) allRemoved = true ;
				if ( s.w <= 1 ) break ;
				assert s.w >= 2;
				++yes;
				char ch = g[s.x][s.y];
				mark(s.x,s.y,g[s.x][s.y]);
				ans += P(s.w);
				System.out.println(s.toString(++step,ch));
				cleanUp();
				for ( boolean flag = true; flag; ) {
					for ( j = 0, flag = false; j < n-1; ++j )
						if ( isEmpty(j) && !isEmpty(j+1) ) {
							flag = true ;
							for ( i = 0; i < m; ++i ) {
								char tmp = g[i][j]; g[i][j] = g[i][j+1]; g[i][j+1] = tmp;
								flag = true ;
							}
						}
				}
			};
			for ( k = 0, i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					if ( g[i][j] != '*' )
						++k;
			if ( k == 0 ) ans += 1000;
			System.out.println("Final score: "+ans+", with "+k+" balls remaining.");
			if ( ts > 0 ) System.out.println("");
		};
	};
};

