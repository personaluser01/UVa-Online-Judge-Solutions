/*
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public static void main( String [] args ) throws Exception { new Main().go(); }

	class Mat {
		char [][]g;
		public int m;
		Mat ( int m ) {
			this.g = new char[10][m+3];
			for ( int i = 0; i <= 9; ++i )
				for ( int j = 0; j <= m+1; ++j )
					this.g[i][j] = '*';
			this.m = m;
		}
		void setItem( int i, int j, char ch ) { this.g[i][j] = ch; }
		char getItem( int i, int j ) { return this.g[i][j]; }
	}

	Mat readMat() throws Exception {
		char [][]g = new char[10][80];
		int m = 0;
		for ( int i = 0; i <= 9; ++i ) {
			String s = br.readLine();
			m = s.length();
			for ( int j = 0; j < m; ++j )
				g[i][j] = s.charAt(j);
		}
		Mat e = new Mat(m-2);
		for ( int i = 0; i <= 9; ++i )
			for ( int j = 0; j < m; ++j )
				e.setItem(i,j,g[i][j]);
		return e;
	}

	String conv( Mat e ) {
		byte []ch = new byte[e.m+1];
		int i,j,k,len = 0;
		for ( i = 1; i <= 8; ++i ) {
			for ( j = 1; j <= e.m; ++j ) {
				if ( e.getItem(i,j) == '/' ) {
				}
				else {
					assert e.getItem(i,j) == '\\' ;
					ch[j-1] |= (1<<(i-1));
				}
			}
		}
		return new String(ch,0,e.m);
	}

	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		Mat e;
		while ( ts-- > 0 ) {
			e = readMat();
			if ( ts > 0 )
				br.readLine();
			System.out.println(conv(e));
		}
	}
};

