/*
 * 12337. Bob's Beautiful Balls
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	int []dx = {0,1,0,-1}, dy = {1,0,-1,0};
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean vc( int m, int n, int x, int y ) { return 0<=x && x<m && 0<=y && y<n; }

	boolean f( int m, int n, String s ) {
		char [][]a = new char[m+1][n+1];
		int i,j,k,len = m*n,dir = 0;
		for ( i = 0; i < m; ++i )
			for ( j = 0; j < n; ++j )
				a[i][j] = '#';
		for ( i = 0, j = 0, dir = 0, k = 0; k < len; ) {
			for ( ;vc(m,n,i,j) && k < len && a[i][j] == '#'; a[i][j] = s.charAt(k++), i += dx[dir], j += dy[dir] );
			if ( k < len ) {
				i -= dx[dir];
				j -= dy[dir];
				dir = (dir+1)&3;
				i += dx[dir];
				j += dy[dir];
			}
		}
		for ( j = 0; j < n; ++j ) {
			char ch = a[0][j];
			for ( i = 1; i < m; ++i )
				if ( a[i][j] != ch )
					return false;
		}
		return true;
	}

	void go() throws Exception {
		int i,j,k,ts=Integer.parseInt(br.readLine()),cs=0,m,n,len,w;
		String s;
		for(;ts-->0;System.out.println(w==(1<<29)?-1:w)) {
			s = br.readLine();
			len = s.length();
			System.out.print("Case "+(++cs)+": ");
			for ( w = (1<<29), m = 2; m <= len-1; ++m )
				if ( 0 == (len%m) ) {
					n = len/m;
					if ( (m+n) < w && f(m,n,s) )
						w = (m+n);
				}
		}
	}
};

