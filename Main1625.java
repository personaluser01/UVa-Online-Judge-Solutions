/*
 * 1625. Color Length
 * TOPIC: dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = (1<<13), A = 26, oo = (1<<29);
	int []m = new int[2];
	char [][]a = new char[2][];
   	int [][][] c = new int[2][N][A];
	int [][]z = new int[N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int is_begin( int i, int j, int t ) {
		return c[0][i][t]+c[1][j][t]==1?i+j:0;
	}
	int is_end( int i, int j, int t ) {
		return c[0][i][t]+c[1][j][t]==c[0][m[0]-1][t]+c[1][m[1]-1][t]?i+j:0;
	}
	void go() throws Exception {
		int i,j,k,ts = scan.nextInt(),t,l;
		for (;ts-->0;) {
			for ( t = 0; t <= 1; ++t ) {
				char []tmp = scan.next().toCharArray();
				m[t] = tmp.length+1;
				a[t] = new char[m[t]];
				for ( i = 1; i <= m[t]-1; ++i ) a[t][i] = tmp[i-1];
			}
			for ( t = 0; t <= 1; ++t )
				for ( i = 0; i < m[t]; ++i )
					for ( l = 0; l < A; c[t][i][l++] = 0 );
			for ( t = 0; t <= 1; ++t )
				for ( i = 1; i < m[t]; ++c[t][i][a[t][i]-'A'], ++i ) 
					for ( l = 0; l < A; c[t][i][l] = c[t][i-1][l], ++l );
			for ( i = 0; i < m[0]; ++i )
				for ( j = 0; j < m[1]; z[i][j++] = +oo );
			for ( z[0][0] = 0, i = 0; i < m[0]; ++i )
				for ( j = 0; j < m[1]; ++j ) 
					if ( z[i][j] < +oo ) {
						if ( i+1 < m[0] )
							z[i+1][j] = Math.min(z[i+1][j],z[i][j]+is_end(i+1,j,a[0][i+1]-'A')-is_begin(i+1,j,a[0][i+1]-'A'));
						if ( j+1 < m[1] )
							z[i][j+1] = Math.min(z[i][j+1],z[i][j]+is_end(i,j+1,a[1][j+1]-'A')-is_begin(i,j+1,a[1][j+1]-'A'));
					}
			System.out.println(z[m[0]-1][m[1]-1]);
		}
	}
};

