/*
 * 10997. Medals
 * TOPIC: maths
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int M = 20;
	int n;
	long[][]c = new long[M][3];
	long T,tmp;
	boolean ok,flag;
	long []d = new long[M];
	String s;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean f( int x, int y, int z, int idx ) {
		long []w = new long[M];
		int i,j,k;
		for ( i = 0; i < n; ++i )
			w[i] = c[i][0]*d[x] + c[i][1]*d[y] + c[i][2]*d[z];
		for ( i = 0; i < n; ++i )
			if ( i != idx && w[i] >= w[idx] )
				return false;
		return true;
	}
	void go() throws Exception {
		int i,j,k,x,y,z;
		for(;(n=scan.nextInt())!= 0;) {
			for ( T = 0, k = -1, i = 0; i < n; ++i ) {
				s = scan.next();
				if ( s.equals("Canada") ) k = i;
				for ( j = 0; j < 3; ++j )
					T += (c[i][j] = scan.nextLong());
			}
			for ( d[0] = 1L, i = 1; i < 8; ++i )
				d[i] = d[i-1]*T;
			if ( k == -1 ) {
				System.out.println("Canada cannot win.");
				continue ;
			}
			for ( flag = true; flag; )
				for ( flag = false, j = 0; j < 2; ++j )
					if ( c[k][j] < c[k][j+1] ) 
						for ( flag = true, i = 0; i < n; ++i ) {
							tmp = c[i][j]; c[i][j] = c[i][j+1]; c[i][j+1] = tmp;
						}
			for ( ok = false, x = 0; x <= 2 && !ok; ++x )
				for ( y = 0; y <= 2 && !ok; ++y )
					for ( z = 0; z <= 2 && !ok; ok = ok||f(x,y,z++,k) );
			System.out.println(ok?"Canada wins!":"Canada cannot win.");
		}
	}
};


